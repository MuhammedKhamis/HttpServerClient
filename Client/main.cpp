/* import libraries */
/*************************************/
#include <stdio.h>
#include <string>
#include <Request.h>
#include "HttpClient.h"
#include <Parser.h>


/* main function */
/*************************************/

void connectionStatus(int status){
    if(status == -1){
        cout << "Connecting Disconnected\n";
    }
}

static void* runThread(void *p){


    return NULL;
}

int testMain(){
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

int applyCommands(vector<string> userCommands, HttpClient client){

    vector<Request> reqs;
    int status;
    for(string command : userCommands) {
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
    return 0;
}

int main(int argc, char *argv[])
{
    // input shape ./client server-ip port-number file-name
    // where to store data on client module
    string dataDirectory = ".";
    HttpClient client(dataDirectory);


    // reading args
    int port = atoi(argv[2]);
    char *serverAddress = argv[1];
    char *fileName = argv[3];
    vector<string> userCommands;

    string command;
    ifstream myfile (fileName);

    if(myfile.is_open()){
        while ( getline (myfile,command) )
        {
            userCommands.push_back(command);
            cout << command << endl;
        }
        myfile.close();
    }

    client.connectionInit(serverAddress, port);
    applyCommands(userCommands, client);
}
