//
// Created by muhammed on 02/11/18.
//

#ifndef HTTPSERVERCLIENT_HTTPSERVER_H
#define HTTPSERVERCLIENT_HTTPSERVER_H
/**
 *  Class for Http Server.
 * */

#include <bits/stdc++.h>
#include "HttpHandler.h"
using namespace std;

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
    unsigned int port;
    unsigned long long timeOut;
    bool haveWorkers();

};

#endif //HTTPSERVERCLIENT_HTTPSERVER_H
