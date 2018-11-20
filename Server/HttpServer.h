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
    void haveWorkers();
    static void * workerChecker(void *runner);
    pthread_t workerCheckerId = 0;
    pthread_mutex_t lock;
    pthread_cond_t toProduce;
    pthread_cond_t toConsume;

};

#endif //HTTPSERVERCLIENT_HTTPSERVER_H
