#include <HttpHandler.h>
#include <poll.h>
#include "HttpClient.h"

/* constructor */
/*************************************/
HttpClient::HttpClient(string dataDirectory)
{
    this->dataDirectory = dataDirectory;
    timeInterval = 30 * 1000;
}

HttpClient::~HttpClient()
{
    //PortHandler::closeConnection(socketfd);
}


/* interface methods */
/*************************************/
int
HttpClient::connectionInit(char *server_address, int port_no)
{
    socketfd = 0;
    struct sockaddr_in serv_addr; 

    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr));
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(port_no); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, server_address, &serv_addr.sin_addr)<=0)
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(socketfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1; 
    }
    return 0; // successful
}

int
HttpClient::sendGETRequests(vector<Request> requests)
{

    // send GET msg
    for(Request requestObj : requests) {
        string r = requestObj.toString();
        int status = PortHandler::write(socketfd , (char* )r.c_str() , r.size());
        if(status == -1){
            return -1;
        }
    }

    struct pollfd pollFd;

    pollFd.fd = socketfd;
    pollFd.events = POLLIN;

    int file_counter = 0 ;
    while(file_counter < requests.size()) {
        int activity = poll(&pollFd, 1, timeInterval);
        if ((activity <= 0) && (errno!=EINTR))
        {
            return activity;
        }

          vector<char> total(MAX_RES_SZ, 0);

          // receive reponse
          int valread = PortHandler::tryRead(socketfd, total, MAX_RES_SZ);

          if (valread == -1) {
              return -1;
          }

          if(valread == 0){
              cout << "Stuck at receive\n";
          }

          string s = string(total.begin(), total.begin() + ((valread < MAX_RES_SZ) ? valread : MAX_RES_SZ));
          // save data to directory
          Response *responseObj = Parser::createResponse(s);
          const char *data = 0;

          //connection is dead
          if (responseObj == NULL) {
              return -1;
          }
          int len;
        vector<char> rest;
        string realS;
        if (responseObj->getStatus() == 200) // file found
          {
              //IMPORTANT DON't DELETE IT
              len = stoi(responseObj->getKey_val("Content-Length")) + responseObj->getHeadersSize();

              PortHandler::readExact(socketfd, rest, len);

              realS = string(rest.begin(), rest.end());

              Response *realResponse = Parser::createResponse(realS);

              string body = realResponse->getBody();

              data = body.c_str();

              IOHandler::writeData(Client, requests[file_counter].getFileName(), (char *) data, body.size());

              // for testing....
              cout << realResponse->toString() << endl;

              delete realResponse;
          } else if(responseObj->getStatus() == 404){
            len = responseObj->getHeadersSize();

            PortHandler::readExact(socketfd, rest, len);

            realS = string(rest.begin(), rest.end());

            Response *realResponse = Parser::createResponse(realS);

            cout << realResponse->toString() << endl;

            delete realResponse;
        }

        file_counter++;

        delete responseObj;
    }

    return 0;
}



int 
HttpClient::sendPOSTRequest(Request requestObj)
{
    // read file
    int sz = IOHandler::getFileSize(Client ,requestObj.getFileName());
    vector<char> buffer(sz, 0);
    int status = IOHandler::readData(Client , requestObj.getFileName(), &buffer[0], sz);
    if(status == -1){
        return -1;
    }

    string r = requestObj.toString();

    // send POST request;
    status = PortHandler::writeExact(socketfd , (char* )r.c_str() , r.size());

    if(status < 0){
        return -1;
    }


    struct pollfd pollFd;

    pollFd.fd = socketfd;
    pollFd.events = POLLIN;


    int activity = poll(&pollFd, 1, timeInterval );
    if ((activity <= 0) && (errno!=EINTR))
    {
        return -1 ;
    }


    // receive reponse
    vector<char> retBuffer(MAX_RES_SZ, 0);

    int valread = PortHandler::read(socketfd , retBuffer, MAX_RES_SZ);

    if(valread < 0){
        return -1;
    }

    r = string(retBuffer.begin(),retBuffer.begin() + ((valread < MAX_RES_SZ) ? valread : MAX_RES_SZ));

    // make sure its OK to send data
    Response *responseObj = Parser::createResponse(r);
    cout << responseObj->toString() << endl;
    if(responseObj->getStatus() == 200) // ready to receive file
    {
        PortHandler::writeExact(socketfd, buffer.data(), sz);
        delete responseObj;
        return 0;    
    }
    delete responseObj;
    return -1;
}


int HttpClient::closeConnection() {
    return PortHandler::closeConnection(socketfd);
}

