#include <HttpHandler.h>
#include <poll.h>
#include "HttpClient.h"

/* constructor */
/*************************************/
HttpClient::HttpClient(string dataDirectory)
{
    this->dataDirectory = dataDirectory;
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
    pollFd.events = POLLIN | POLLHUP;

    int waitInterval = 2 * 1000;

    int file_counter = 0 ;
    while(file_counter < requests.size()) {

        int activity = poll(&pollFd, 1, waitInterval );

      if ((activity <= 0) && (errno!=EINTR))
      {
        break ;
      }

      vector<char> total(MAX_RES_SZ, 0) ;

      // receive reponse
      int valread = PortHandler::read(socketfd , total , MAX_RES_SZ);

      if(valread == -1){
        return -1 ;
      }

      string s = string(total.begin(),total.begin() + ((valread < MAX_RES_SZ) ? valread : MAX_RES_SZ));
      // save data to directory
      Response *responseObj = Parser::createResponse(s);
      const char *data = 0;

      //connection is dead
      if(responseObj == NULL){
        return -1 ;
      }

      if(responseObj->getStatus() == 200) // file found
      {
        string body = responseObj->getBody();
        //IMPORTANT DON't DELETE IT
        int len = stoi(responseObj->getKey_val("Content-Length"));
        int currLen = len - body.size();
        while (currLen > 0){
            vector<char> total;
            int read = PortHandler::readExact(socketfd, total, currLen);
            if(read <= 0){
                break;
            }
            currLen -= read;
            body.insert(body.end(), total.begin(), total.end());
        }
          data = body.c_str();
          IOHandler::writeData(Client , requests[file_counter].getFileName(), (char*)data, len);
          responseObj->setBody(body);
          file_counter++;
      }
      cout << responseObj->toString() << endl;
      delete responseObj;

    }

    return 0;
}



int 
HttpClient::sendPOSTRequest(Request requestObj)
{
    // read file
    int sz = IOHandler::getFileSize(Client ,requestObj.getFileName()) + 1;
    vector<char> buffer(sz, 0);
    int status = IOHandler::readData(Client , requestObj.getFileName(), &buffer[0], sz);
    if(status == -1){
        return -1;
    }

    requestObj.setBody(string(buffer.begin(),buffer.end()));

    string r = requestObj.toString();

    // send POST request;
    status = PortHandler::write(socketfd , (char* )r.c_str() , r.size());

    if(status < 0){
        return -1;
    }

    // receive reponse
    vector<char> retBuffer;

    int valread = PortHandler::read( socketfd , retBuffer, MAX_RES_SZ);

    if(valread < 0){
        return -1;
    }

    r = string(retBuffer.begin(),retBuffer.begin());

    // make sure its OK to send data
    Response *responseObj = Parser::createResponse(r);
    cout << responseObj->toString() << endl;
    if(responseObj->getStatus() == 200) // ready to receive file
    {
        delete responseObj;
        return 0;    
    }
    delete responseObj;
    return -1;
}




