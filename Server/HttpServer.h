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
#include <HttpHandler.h>
#include <IOHandler.h>
#include <fcntl.h>
#include <semaphore.h>

using namespace std;

#define SERVER_NAME "Gumball/1.0"

class HttpServer{

public:
    HttpServer(int workers, int backlog, unsigned int port);
    ~HttpServer();
    void run();
    int initServer();

private:
    queue<HttpHandler*> workers;
    int maxWorkers;
    int maxBacklog;
    int server_fd;
    unsigned int port;
    int currentWorkers;
    sem_t sema;

};

#endif //HTTPSERVERCLIENT_HTTPSERVER_H
