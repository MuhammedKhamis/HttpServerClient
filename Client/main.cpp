/* import libraries */
/*************************************/
#include <stdio.h>
#include <string>
#include <Request.h>
#include "HttpClient.h"
#include <Parser.h>


/* main function */
/*************************************/

static void* runThread(void *p){

    // where to store data on client module
    string dataDirectory = ".";

    HttpClient client(dataDirectory);

    // reading args
    int port = 8000;
    char *serverAddress = "127.0.0.1";

    int initFlag = client.connectionInit(serverAddress, port);
    while(initFlag == 0)
    {
        // scan user command
        string userCommand = "GET read.txt 0.0.0.0";
        //printf("Enter Command: ");
        //getline(cin,userCommand);

        // parse user command
        Request requestObj = Parser::parseInputCommand(userCommand);

        int status;
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
}

int main(int argc, char *argv[])
{
    pthread_t ts[10];
    for(int i = 0 ; i < 10 ; i++){
        pthread_create(&ts[i],NULL, runThread, NULL);
    }
    void *status;
    for(int i = 0 ; i < 10 ; i++){
        pthread_join(ts[i], &status);
        free(status);
    }
    return 0; 
}
