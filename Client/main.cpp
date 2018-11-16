/* import libraries */
/*************************************/
#include <stdio.h>
#include <string>
#include <Request.h>
#include "HttpClient.h"
#include <Parser.h>


/* main function */
/*************************************/
int main(int argc, char const *argv[]) 
{ 
    // where to store data on client module
    string dataDirectory = ".";

    // non-persistent
    HttpClient client(dataDirectory);
    int port = 8000;
    char serverAddress[] = "127.0.0.1";
    int initFlag = client.connectionInit(serverAddress, port);

    while(initFlag == 0)
    {
        // scan user command
        char userCommand[1024] = {0};
        printf("Enter Command: ");
        scanf("%s", userCommand);

        // parse user command
        Request requestObj = Parser::parseInputCommand(string(userCommand));
        string serverAddress = requestObj.getHostName();
        int portNo = requestObj.getPort();

        // GET or POST
        if(requestObj.getMethod() == GET)
        {
            if(client.sendGETRequest(requestObj)<0)
                perror("something went wrong");
        }else{
            if(client.sendPOSTRequest(requestObj)<0)
                perror("something went wrong");
        }
        
    }
    return 0; 
}
