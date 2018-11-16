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
    PortHandler::write(socketfd , (char* )requestObj.toString().c_str() , requestObj.toString().size());
    printf("message sent\n"); 

    // receive reponse
    char buffer[1024] = {0};
    int valread;
    valread = PortHandler::read(socketfd , buffer, 1024);

    // save data to directory
    Response responseObj = Parser::createResponse(buffer);
    cout << responseObj.toString() << endl;
    if(responseObj.getStatus() == 200) // file found
    {
        char *data = (char*)responseObj.getBody().c_str();
        return IOHandler::writeData(requestObj.getFileName(), data, strlen(data));
    }
    return -1;
}



int 
HttpClient::sendPOSTRequest(Request requestObj)
{
    // read file
    char buffer[1024] = {0};
    IOHandler::readData(requestObj.getFileName(), buffer, strlen(buffer));
    
    // send POST request;
    PortHandler::write(socketfd , (char* )requestObj.toString().c_str() , requestObj.toString().size());
    printf("message sent\n"); 

    // receive reponse
    char retBuffer[1024] = {0};
    int valread;
    valread = PortHandler::read( socketfd , retBuffer, 1024);

    // make sure its OK to send data
    Response responseObj = Parser::createResponse(retBuffer);
    cout << responseObj.getBody() << endl;
    if(responseObj.getStatus() == 200) // ready to receive file
    {
        return 0;    
    }
    return -1;
}




