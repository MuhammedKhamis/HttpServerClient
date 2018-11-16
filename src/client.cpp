/* import libraries */
/*************************************/
#include <stdio.h> 
#include "Request.h" 
#include "HttpClient.h"


/* main function */
/*************************************/
/*int main(int argc, char const *argv[]) 
{ 
    char* connectionType = agrv[3];
    char* serverAddress = argv[1];
    char* portNo = argv[2];
    
    return 0; 
} */



void
runPersistentConnection(char* serverAddress, int portNo)
{
    // where to store data on client module
    string dataDirectory = "asd";
    // non-persistent 
    HttpClient client(dataDirectory);
    client.init(serverAddress, portNo);

    while(1)
    {
        // scan user command
        char userCommand[1024] = {0};
        printf("Enter Command: ");
        scanf("%s", userCommand);

        // parse user command
        Request requestObj = ClientParser.parseInputCommand(userCommand);

        // GET or POST
        if(requestObj.getRequestType() == "GET")
        {
            if(client.sendGETRequest(requestObj)<0)
                perror("something went wrong");
        }else{
            if(client.sendPOSTRequest(requestObj)<0)
                perror("something went wrong");
        }
        
    }
}

void
runNonPersistentConnection()
{
    // where to store data on client module
    string dataDirectory = "asd";

    while(1)
    {
        // scan user command
        char userCommand[1024] = {0};
        printf("Enter Command: ");
        scanf("%s", userCommand);

        // parse user command
        Request requestObj = ClientParser.parseInputCommand(userCommand);
        serverAddress = requestObj.getHostName();
        portNo = requestObj.getPort();

        // non-persistent 
        HttpClient client(dataDirectory);
        client.init(serverAddress, portNo);

        // GET or POST
        if(requestObj.getRequestType() == "GET")
        {
            if(client.sendGETRequest(requestObj)<0)
                perror("something went wrong");
        }else{
            if(client.sendPOSTRequest(requestObj)<0)
                perror("something went wrong");
        }
        
    }
}