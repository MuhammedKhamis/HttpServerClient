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
#include "HttpHandler.h"
using namespace std;

#define SERVER_NAME "TEST"

class HttpServer{

public:
    HttpServer(string currDir, int workers, int backlog, unsigned int port, unsigned long long timeOut);
    ~HttpServer();
    void run();
    int initServer();

private:
    vector<HttpHandler*> workers;
    string currDir;
    int maxWorkers;
    int maxBacklog;
    int server_fd;
    unsigned int port;
    time_t timeOut;
    bool haveWorkers();

};

#endif //HTTPSERVERCLIENT_HTTPSERVER_H
