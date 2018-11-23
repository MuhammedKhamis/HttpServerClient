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

    int counter = 0;
     counter += (client.connectionInit(serverAddress, port) <= 0);
    while(counter < 2)
    {
        // scan user command
        vector<string> userCommand = {"GET smile.jpeg 0.0.0.0"};

        //printf("Enter Command: ");
        //getline(cin,userCommand);
        vector<Request> reqs;
        for(string command : userCommand) {
          // parse user command
          Request requestObj = Parser::parseInputCommand(command);
          reqs.push_back(requestObj);
        }
        int status;
        // GET or POST
        status = client.sendGETRequests(reqs);
        if(status == -1){
            cout << "Connecting again...\n";
            counter += (client.connectionInit(serverAddress, port) <= 0);
        } else{
            counter = 5;
        }
    }
    return NULL;
}

int main(int argc, char *argv[])
{

    int sz = 1;
    pthread_t ts[sz];
    for(int i = 0 ; i < sz ; i++){
        pthread_create(&ts[i],NULL, runThread, NULL);
        usleep(100);
    }
    void *status;
    for(int i = 0 ; i < sz ; i++){
        pthread_join(ts[i], &status);
        free(status);
    }

    return 0; 
}
