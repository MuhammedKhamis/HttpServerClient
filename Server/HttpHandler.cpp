//
// Created by muhammed on 02/11/18.
//

#include "HttpHandler.h"
#include "../Messages/Parser.h"
#include "../Messages/Response.h"
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
    delete request;
    // Error
}

void HttpHandler::handleGet(Request request) {

     string fileName = request.getFile_name();
     int sz = ioHandler->getFileSize(fileName);
    Response *res = NULL;
    if(sz == -1){
         // Error
         res = new Response(false);
         string r = res->toString();
         portHandler->write((char*)r.c_str(), r.size());
         delete res;
         return;
     }
     vector<char> data(sz+1,0);
     ioHandler->readData(fileName, &data[0], sz+1);
     res = new Response(true);
     res->setKeyVal("Content-Length", to_string(sz));
     res->setKeyVal("Content-Type", ioHandler->getContentType(fileName));
     res->setBody(string(data.begin(),data.end()));
     string r = res->toString();
     portHandler->write((char*)r.c_str(), r.size());
     delete res;
     }

void HttpHandler::handlePost(Request reuqest) {
    //TODO
    int sz = reuqest.getBody().size();
    char* data = (char*)reuqest.getBody().c_str();
    string fileName = reuqest.getFile_name();

    int status = ioHandler->writeData(fileName,data,sz);

    HttpMessage *res = new Response(status != -1);
    string r = res->toString();
    portHandler->write((char*)r.c_str(), r.size());
    delete res;
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
