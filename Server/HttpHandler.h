//
// Created by muhammed on 02/11/18.
//

#ifndef HTTPSERVERCLIENT_HTTPHANDLER_H
#define HTTPSERVERCLIENT_HTTPHANDLER_H
/**
 * Class for Http thread worker.
 * */

#include <bits/stdc++.h>
#include <pthread.h>
#include "../util/IOHandler.h"
#include "../util/PortHandler.h"
#include "../Messages/Request.h"
using namespace std;

#define MAX_REQ_SZ 10240

class HttpHandler{

public:
    HttpHandler(IOHandler* ioHandler, PortHandler* portHandler, string serverName);
    ~HttpHandler();
    bool isFinished();
    time_t getCreateTime();
    bool start();

private:

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

#endif //HTTPSERVERCLIENT_HTTPHANDLER_H
