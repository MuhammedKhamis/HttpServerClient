//
// Created by muhammed on 02/11/18.
//

#include "HttpHandler.h"

HttpHandler::HttpHandler(IOHandler *ioHandler, PortHandler *portHandler) {
    this->ioHandler = ioHandler;
    this->portHandler = portHandler;
    handler_id = 0;
    finished = false;
}

void HttpHandler::run() {
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

static void* HttpHandler::startHelper(void *runner) {
    ((HttpHandler*)runner)->run();
    ((HttpHandler*)runner)->close();
    return NULL;
}

void HttpHandler::close() {
    this->portHandler->closeConnection();
    this->finished = true;
}