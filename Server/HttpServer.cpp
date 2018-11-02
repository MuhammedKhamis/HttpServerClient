//
// Created by muhammed on 02/11/18.
//

#include "HttpServer.h"

HttpServer::HttpServer(string currDir, int workers, int backlog, unsigned int port, unsigned long long timeOut) {
    this->maxBacklog = backlog;
    this->currDir = currDir;
    this->maxWorkers = workers;
    this->port = port;
    this->timeOut = timeOut;
    server_fd = 0;
}

bool HttpServer::haveWorkers() {
    unsigned long long currTime = 0;
    for(auto it = this->workers.begin() ; it != this->workers.end();){
        HttpHandler* curr = *it;
        time(&currTime)
        if(curr->isFinished() || difftime(currTime, curr->createTime()) > timeOut){
            it = workers.erase(it);
            delete curr
        }else{
            it++;
        }
    }
    return workers.size() < maxWorkers;
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
    return 0;
}

void HttpServer::run() {
    while (1){
        while (haveWorkers()) {
            //TODO

            int new_socket;
            struct sockaddr_in address;
            socklen_t addrlen = sizeof(address);
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen))<0)
            {
                perror("accept");
                continue;
            }

            HttpHandler* handler = new HttpHandler(new IOHandler(), new PortHandler(new_socket), SERVER_NAME);

            if (handler->start()){
                workers.emplace_back(handler);
            }else{
                delete handler;
            }
        }
    }
}