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
HttpClient::sendGETRequest(Request requestObj)
{ 
    // send GET msg
    string r = requestObj.toString();
    int status = PortHandler::write(socketfd , (char* )r.c_str() , r.size());
    if(status == -1){
        return -1;
    }

    // receive reponse
    vector<char> buffer(MAX_RES_SZ, 0);
    int valread;
    valread = PortHandler::read(socketfd , &buffer[0], MAX_RES_SZ);

    r = string(buffer.begin(), buffer.begin() + ((valread < MAX_RES_SZ) ? valread : MAX_RES_SZ));

    // save data to directory
    Response *responseObj = Parser::createResponse(r);
    int ret = 0;
    const char *data = 0;
    if(responseObj->getStatus() == 200) // file found
    {
        string body = responseObj->getBody();
        //IMPORTANT DON't DELETE IT
        data = body.c_str();
        ret = IOHandler::writeData(Client , requestObj.getFileName(), (char*)data, body.size());
    }
    delete responseObj;
    return ret;
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
    PortHandler::write(socketfd , (char* )r.c_str() , r.size());
    printf("message sent\n");

    // receive reponse
    vector<char> retBuffer(MAX_RES_SZ, 0);

    int valread;
    valread = PortHandler::read( socketfd , &retBuffer[0], MAX_RES_SZ);

    r = string(retBuffer.begin(),retBuffer.begin() + ((valread < MAX_RES_SZ) ? valread : MAX_RES_SZ) );

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




