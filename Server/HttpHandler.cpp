//
// Created by muhammed on 02/11/18.
//

#include "HttpHandler.h"


HttpHandler::HttpHandler(int socket_fd, string serverName) {
    handler_id = 0;
    finished = false;
    this->socket_fd = socket_fd;
    this->serverName = serverName;
}

HttpHandler::~HttpHandler() {
    PortHandler::closeConnection(socket_fd);
}

void HttpHandler::run() {
    //TODO
    int state  = 0 ;
    do {

      vector<char> data (MAX_REQ_SZ , 0);
      int read = PortHandler::read(socket_fd, &data[0], MAX_REQ_SZ);

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
          continue;
      }
      // re-initialize the time.
      time(&startTime);
      if(request->getKey_val("Connection") == "closed"){
        state = 1;
      }

      if(request->getMethod() == GET){
        handleGet(*request);
      } else if(request->getMethod() == POST){
        handlePost(*request);
      }
      delete request;
    }while (!state);

    // Error
}

void HttpHandler::handleGet(Request request) {

     string fileName = request.getFileName();
     int sz = IOHandler::getFileSize(fileName);
    Response *res = NULL;
    if(sz == -1){
         // Error
         res = new Response(false);
         string r = res->toString();
         PortHandler::write(socket_fd, (char*)r.c_str(), r.size());
         delete res;
         return;
     }
     vector<char> data(sz+1,0);
     IOHandler::readData(fileName, &data[0], sz+1);
     res = new Response(true);
     res->setKeyVal("Content-Length", to_string(sz));
     res->setKeyVal("Content-Type", IOHandler::getContentType(fileName));
     res->setBody(string(data.begin(),data.end()));
     string r = res->toString();
     PortHandler::write(socket_fd, (char*)r.c_str(), r.size());
     delete res;
     }

//TODO test2
void HttpHandler::handlePost(Request request) {


    //TODO
    int sz = request.getBody().size();
    char* data = (char*)request.getBody().c_str();
    string fileName = request.getFileName();


    int status = IOHandler::writeData(fileName,data,sz);

    HttpMessage *res = new Response(status != -1);
    string r = res->toString();

    cout << "---------response----------" << endl ;
    cout << r << endl ;

    PortHandler::write(socket_fd, (char*)r.c_str(), r.size());
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
    PortHandler::closeConnection(socket_fd);
    finished = true;
}
