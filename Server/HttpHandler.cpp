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

    Request* request = Parser::createRequest(data) ;

    if(request == NULL){
      perror("failed to create request is corrupter or in complete\n") ;
    }

    if(request->getMethod() == GET){
        handleGet(*request);
    } else if(request->getMethod() == POST){
        handlePost(*request);
    }
    // Error
}

void HttpHandler::handleGet(Request reuqest) {
    /*
    string data = "<!DOCTYPE HTML>\n<html>\n<head>\n   <title>folaaaa</title>\n</head>\n<body>\n <h1>It's done man</h1>\n <p>The requested URL /t.html was not found on this server.</p>\n</body>\n</html>" ;
    string response = "HTTP/1.1 200 OK\r\nDate: Sun, 10 Oct 2010 23:26:07 GMT\r\nServer: Apache/2.2.8 (Ubuntu) mod_ssl/2.2.8 OpenSSL/0.9.8g\r\nLast-Modified: Sun, 26 Sep 2010 22:04:35 GMT\r\nAccept-Ranges: bytes\r\nContent-Length: " + to_string(data.length() * 8 ) + "\r\nConnection: Keep-Alive\r\nContent-Type: text/html\r\n\r\n";
    portHandler->write((char *)(response+data).c_str() , (response+data).length()) ;
    */
    stringstream ss;

     }

void HttpHandler::handlePost(Request reuqest) {
    //TODO
}

bool HttpHandler::start() {
    time(&startTime);
    return (pthread_create(&handler_id, NULL, startHelper, (void* )this) == 0);
}

bool HttpHandler::isFinished() {
    return this->finished;
}

time_t HttpHandler::getCreateTime() {
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
