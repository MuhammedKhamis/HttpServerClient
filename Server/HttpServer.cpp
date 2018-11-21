//
// Created by muhammed on 02/11/18.
//

#include <thread_db.h>
#include <semaphore.h>
#include "HttpServer.h"

HttpServer::HttpServer(int workers, int backlog, unsigned int port) {
    this->maxBacklog = backlog;
    this->maxWorkers = workers;
    this->port = port;
    server_fd = 0;
    currentWorkers = 0;
    sem_init(&sema, 0, maxWorkers);
    IOHandler::initFileLock();
}

HttpServer::~HttpServer() {

}

int HttpServer::initServer() {

    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);


    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);


    // Forcefully attaching socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0)
    {
        close(server_fd);
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, maxBacklog) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    cout << "Server side started\n";
    return 0;
}
/*
void HttpServer::haveWorkers() {

    pthread_mutex_lock(&lock);
    while(workers.empty()){
        pthread_cond_wait(&toConsume, &lock);
    }

    queue<HttpHandler*> nextQueue;
    time_t currTime = 0;
    unsigned long long timeOut = (2 * maxWorkers) / (workers.size() + 1);
    while(!workers.empty()){

        HttpHandler* curr = workers.front();
        workers.pop();

        time(&currTime);
        if(difftime(currTime, curr->getCreateTime()) > timeOut){
            curr->finish();
        }else{
            nextQueue.push(curr);
        }
    }
    workers = nextQueue;

    pthread_cond_signal(&toProduce);
    pthread_mutex_unlock(&lock);
}
*/
/*
void* HttpServer::workerChecker(void *runner) {
    while (true){
        ((HttpServer*)runner)->haveWorkers();
        usleep(1000);
    }
}

*/
void HttpServer::run() {

    while (1){

            int new_socket;
            struct sockaddr_in address;
            socklen_t addrlen = sizeof(address);
            if ((new_socket = accept(server_fd, (struct sockaddr *) &address, &addrlen)) < 0) {
                perror("accept");
                continue;
            }
            sem_wait(&sema);
            HttpHandler *handler = new HttpHandler(new_socket, SERVER_NAME);
            if (handler->start(&sema)) {
                cout << "Connection opened with server using fd = " << new_socket << endl;
                workers.push(handler);
            } else {
                delete handler;
            }
            usleep(1000);
        }

}
