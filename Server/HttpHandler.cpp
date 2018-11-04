//
// Created by muhammed on 02/11/18.
//

#include "HttpHandler.h"
#include "../Messages/Parser.h"
#include <string.h>

HttpHandler::HttpHandler(IOHandler *ioHandler, PortHandler *portHandler, string serverName) {
    this->ioHandler = ioHandler;
    this->portHandler = portHandler;
    handler_id = 0;
    finished = false;
    this->serverName = serverName;
}

HttpHandler::~HttpHandler() {
    delete portHandler ;
}

void HttpHandler::run() {
    //TODO
    char data[MAX_REQ_SZ];
    memset(data, 0, MAX_REQ_SZ);
    int read = portHandler->read(data, MAX_REQ_SZ);
    if(read == -1){
        //Error
        return;
    }
    if(read == 0){
        // nothing to read.
        return;
    }
    string req(data);
    cout << data ;
    vector<string> tokens = Parser::inst.tokenize(req);
    if(tokens[0] == "GET"){
        handleGet(tokens);
    } else if(tokens[0] == "POST"){
        handlePost(tokens);
    }
    // Error
}

void HttpHandler::handleGet(vector<string> tokens) {
    //TODO
}

void HttpHandler::handlePost(vector<string> tokens) {
    //TODO
}

bool HttpHandler::start() {
    time(&startTime);
    return (pthread_create(&handler_id, NULL, startHelper, (void* )this) == 0);
}

bool HttpHandler::isFinished() {
    return this->finished;
}

unsigned long long HttpHandler::getCreateTime() {
    return this->startTime;
}

void* HttpHandler::startHelper(void *runner) {
    ((HttpHandler*)runner)->run();
    ((HttpHandler*)runner)->close();
    return NULL;
}

void HttpHandler::close() {
    this->portHandler->closeConnection();
    this->finished = true;
}
