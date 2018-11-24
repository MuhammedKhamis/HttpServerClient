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
#include <thread_db.h>

using namespace std;

#define SERVER_NAME "Gumball/1.0"

class HttpServer{

public:
    HttpServer(int workers, int backlog, unsigned int port);
    ~HttpServer();
    void run();
    int initServer();

private:
    static void* workerChecker(void *runner);
    void haveWorkers();
    queue<HttpHandler*> workers;
    int maxWorkers;
    int maxBacklog;
    int server_fd;
    unsigned int port;
    sem_t sema;
    pthread_t workerCheckerId;

};

#endif //HTTPSERVERCLIENT_HTTPSERVER_H
