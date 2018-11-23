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
#include <semaphore.h>
#include <poll.h>

using namespace std;

#define timeOut 200

#define MAX_REQ_SZ 512000

class HttpHandler{

public:
    HttpHandler(int socket_fd, string serverName);
    ~HttpHandler();
    bool isFinished();
    time_t getCreateTime();
    bool start(sem_t* sema);
    void finish();
    int getSocketfd();
    pthread_t getThreadId();

private:

    //attributes
    time_t startTime;
    bool finished;
    int socket_fd;
    pthread_t handler_id;
    string serverName;
    sem_t* sema;

    // methods
    void run();
    void close();
    void runAndClose();
    static void * startHelper(void * runner);
    static void closeHelper(void* runner);
    void handleGet(Request *request);
    void handlePost(Request *request);
};

#endif //HTTPSERVERCLIENT_HTTPHANDLER_H
