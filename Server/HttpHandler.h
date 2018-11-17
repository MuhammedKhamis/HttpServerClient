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
#include <IOHandler.h>
#include <PortHandler.h>
#include <Request.h>
#include <Parser.h>
#include <Response.h>
#include <string.h>

using namespace std;

#define MAX_REQ_SZ 102400

class HttpHandler{

public:
    HttpHandler(int socket_fd, string serverName);
    ~HttpHandler();
    bool isFinished();
    time_t getCreateTime();
    bool start();
    int getSocketfd();

private:

    //attributes
    time_t startTime;
    bool finished;
    int socket_fd;
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
