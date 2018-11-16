#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H
/**
    whenever a connection is created
    assign new worker thread for requesting client
**/

/* import libraries */
/*************************************/
#include <bits/stdc++.h>
#include <pthread.h>
#include <string.h>
#include "../utilities/IOHandler.h"
#include "../utilities/PortHandler.h"
#include "../http-messages/Request.h"
#include "../utilities/Parser.h"
#include "../http-messages/Response.h"
using namespace std;
#define MAX_REQ_SZ 10240

class ConnectionHandler{

    public:
    /* interface methods */
    /*************************************/
    ConnectionHandler(IOHandler* ioHandler, PortHandler* portHandler, string serverName);
    ~ConnectionHandler();
    bool isFinished();
    time_t getCreateTime();
    bool start();

    private:
    /* interface stuff */
    /*************************************/
    //attributes
    time_t startTime;
    bool finished;
    IOHandler* ioHandler;
    PortHandler* portHandler;
    pthread_t handler_id;
    string serverName;

    // methods
    void run();
    void close();
    static void * startHelper(void * runner);
    void handleGet(Request request);
    void handlePost(Request request);
};

#endif
