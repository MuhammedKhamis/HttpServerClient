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
    //TODO
    return 0;
}

void HttpServer::run() {
    while (1){
        while (!haveWorkers()){
            // Do nothing
        }
        //TODO
    }
}