//
// Created by muhammed on 02/11/18.
//

#ifndef HTTPSERVERCLIENT_HTTPSERVER_H
#define HTTPSERVERCLIENT_HTTPSERVER_H
/**
 *  Class for Http Server.
 * */

#include <bits/stdc++.h>
#include <sys/socket.h>
#include <pthread.h>
#include "HttpHandler.h"
#include <IOHandler.h>
using namespace std;

#define SERVER_NAME "Gumball/1.0"

class HttpServer{

public:
    HttpServer(int workers, int backlog, unsigned int port, unsigned long long timeOut);
    ~HttpServer();
    void run();
    int initServer();

private:
    vector<HttpHandler*> workers;
    int maxWorkers;
    int maxBacklog;
    int server_fd;
    unsigned int port;
    time_t timeOut;
    bool haveWorkers();
    static void * workerChecker(void *runner);
    pthread_t workerCheckerId = 0;

};

#endif //HTTPSERVERCLIENT_HTTPSERVER_H
