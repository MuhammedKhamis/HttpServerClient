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
    string dataDirectory = "asd";

    while(1)
    {
        // scan user command
        char userCommand[1024] = {0};
        printf("Enter Command: ");
        scanf("%s", userCommand);

        // parse user command
        Request requestObj = Parser::parseInputCommand(string(userCommand));
        string serverAddress = requestObj.getHostName();
        string portNo = requestObj.getPort();

        // non-persistent 
        HttpClient client(dataDirectory);
        int port = atoi(portNo.c_str());
        client.connectionInit((char*)serverAddress.c_str(), port);

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
