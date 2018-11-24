/* import libraries */
/*************************************/
#include <stdio.h>
#include <string>
#include <Request.h>
#include "HttpClient.h"
#include <Parser.h>


/* main function */
/*************************************/

static void connectionStatus(int status){
    if(status == -1){
        cout << "Connecting Disconnected\n";
    }
}

static void* runThread(void *p){

    // where to store data on client module
    string dataDirectory = ".";

    HttpClient client(dataDirectory);

    // reading args
    int port = 8000;
    char *serverAddress = "127.0.0.1";
     client.connectionInit(serverAddress, port);

     // scan user command
     vector<string> userCommand = {"GET c.jpg 127.0.0.1"};

     //printf("Enter Command: ");
     //getline(cin,userCommand);
     vector<Request> reqs;
    int status;
    for(string command : userCommand) {
         // parse user command
          Request requestObj = Parser::parseInputCommand(command);
          if(requestObj.getMethod() == GET){
              reqs.push_back(requestObj);
          }else{
              status = client.sendGETRequests(reqs);
              connectionStatus(status);

              status = client.sendPOSTRequest(requestObj);
              connectionStatus(status);
          }
     }
    status = client.sendGETRequests(reqs);
    connectionStatus(status);
    client.closeConnection();
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
