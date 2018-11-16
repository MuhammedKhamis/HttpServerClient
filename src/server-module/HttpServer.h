#ifndef HTTPSERVER_H
#define HTTPSERVER_H

/**
    this class creates and runs an http server
**/

/* import libraries */
/*************************************/
#include <bits/stdc++.h>
#include <sys/socket.h>
#include "ConnectionHandler.h"
using namespace std;

#define SERVER_NAME "TEST"

class HttpServer{

    public:
    /* interface methods */
    /*************************************/
    HttpServer(string currDir, int workers, int backlog, unsigned int port, unsigned long long timeOut);
    ~HttpServer();
    int init(); // inits server
    void run(); // runs server
    

    private:
    /* private stuff */
    /*************************************/
    vector<ConnectionHandler*> workers; // container for dispatched server threads
    string currDir; // directory where server will store files
    int maxWorkers; // max number of dispatched threads server can support
    int maxBacklog; // max number requested connections
    int server_fd; // server socket id
    unsigned int port; // server port
    time_t timeOut; // connection timeout
    bool haveWorkers(); // 

};

#endif
