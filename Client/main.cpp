/* import libraries */
/*************************************/
#include <stdio.h> 
#include "Request.h" 
#include "HttpClient.h"


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
    return 0; 
} 



Request
parseInputCommand(char* userCommand)
{
    vector<string> inputData = Parser::tokenize(string(userCommand), " ");
    string methodType = inputData[0];
    string fileName = inputData[1];
    string hostName = inputData[2];
    string portNumber = "80";
    if(inputData.size() == 4)
    {
        portNumber = inputData[3];
    }
    
    Request requestObj(methodType, fileName, hostName, portNumber);
    return requestObj;
}