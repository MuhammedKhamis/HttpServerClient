/* import libraries */
/*************************************/
#include <stdio.h>
#include <string>
#include <Request.h>
#include "HttpClient.h"
#include <Parser.h>


/* main function */
/*************************************/
int main(int argc, char *argv[])
{


    // where to store data on client module
    string dataDirectory = ".";

    HttpClient client(dataDirectory);

    // reading args
    int port = atoi(argv[2]);
    char *serverAddress = argv[1];

    int initFlag = client.connectionInit(serverAddress, port);
    while(initFlag == 0)
    {
        // scan user command
        string userCommand;
        printf("Enter Command: ");
        getline(cin,userCommand);

        // parse user command
        Request requestObj = Parser::parseInputCommand(userCommand);

        int status ;
        // GET or POST
        if(requestObj.getMethod() == GET)
        {
            status = client.sendGETRequest(requestObj);
        }else{
            status = client.sendPOSTRequest(requestObj);
        }
        if(status == -1){
            bool ans = -1;
            do{
                char in;
                cout << "Connection Closed now, do you want to reopen it ? [Y/n]";
                cin >> in;
                if(in == 'Y' || in == 'y'){
                    ans = 1;
                }else if(in ==  'N' || in == 'n'){
                    ans = 0;
                }
            }while(ans == -1);
            if(ans == 0){
                initFlag = 1;
            }else {
                initFlag = client.connectionInit(serverAddress, port);
            }
        }
    }
    return 0; 
}
