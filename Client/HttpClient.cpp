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
HttpClient::connectionInit(char *server_address, int port_no = 80)
{
    struct sockaddr_in address; 
    sockfd = 0;
    struct sockaddr_in serv_addr; 
    char *hello = "Hello from client"; 
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
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
   
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
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
    send(sockfd , requestObj.toString() , strlen(requestObj.toString()) , 0 );
    printf("message sent\n"); 

    // receive reponse
    char buffer[1024] = {0};
    int valread;
    valread = read( sockfd , buffer, 1024); 
    printf("%s\n",buffer);

    // save data to directory
    Response responseObj = Parser.parseReponseMessage(buffer);
    if(responseObj.getStatus() == 200) // file found
    {
        char *data = responseObj.getData();
        return IOHandler.writeData(requestObj.getFileName(), data, strlen(data));
    }
    return -1;
}



int 
HttpClient::sendPOSTRequest(Request requestObj)
{
    // read file
    char buffer[1024] = {0};
    IOHandler.readData(requestObj.getFileName(), buffer, strlen(buffer));
    
    // send POST request
    requestObj.setData(buffer);
    send(sockfd , requestObj.toString() , strlen(requestObj.toString()) , 0 );
    printf("message sent\n"); 

    // receive reponse
    char retBuffer[1024] = {0};
    int valread;
    valread = read( sockfd , retBuffer, 1024); 
    printf("%s\n",retBuffer);

    // make sure its OK to send data
    Response responseObj = Parser.parseReponseMessage(retBuffer);
    if(responseObj.getStatus() == 200) // ready to receive file
    {
        return 0;    
    }
    return -1;
}




