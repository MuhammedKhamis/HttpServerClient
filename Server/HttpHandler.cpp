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
    bool fl = 1 ;

    while(fl) {

      vector<char> data (MAX_REQ_SZ , 0);
      int read = portHandler->read(&data[0], MAX_REQ_SZ);
      printf("Here is data:\n %s\n",data);


      if(read == -1){
        //Error
        return;
      }
      if(read == 0){
        // nothing to read.
        return;
      }

      string req = "" ;
      for(char i : data){
        req.push_back(i) ;
      }

      Request* request = Parser::createRequest(req.c_str()) ;

      if(request == NULL){
        perror("failed to create request is corrupter or in complete\n") ;
      }

      //if(request->getKey_val("Connection") == "keep_alive")
      cout << request->toString() << endl ;
      cout << "HHH" << request->getBody() << endl;

      if(request->getMethod() == GET){
        handleGet(*request);
      } else if(request->getMethod() == POST){
        handlePost(*request);
      }
      delete request;
      break;
    }

    // Error
}

void HttpHandler::handleGet(Request request) {

     string fileName = request.getFileName();
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

//TODO test2
void HttpHandler::handlePost(Request request) {


  cout << "Hamamda" <<  request.getBody() << endl;


    //TODO
    int sz = request.getBody().size();
    char* data = (char*)request.getBody().c_str();
    string fileName = request.getFileName();


    int status = ioHandler->writeData(fileName,data,sz);

    HttpMessage *res = new Response(status != -1);
    string r = res->toString();

    cout << "---------response----------" << endl ;
    cout << r << endl ;

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
