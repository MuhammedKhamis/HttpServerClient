//
// Created by muhammed on 02/11/18.
//

#include "HttpHandler.h"


HttpHandler::HttpHandler(int socket_fd, string serverName) {
    finished = false;
    this->socket_fd = socket_fd;
    this->serverName = serverName;
}

HttpHandler::~HttpHandler() {
    close();
    cout << "Thread that use fd =  " << socket_fd << " is Closed" << endl;
}

int HttpHandler::getSocketfd() {
    return socket_fd;
}

pthread_t HttpHandler::getThreadId() {
    return handler_id;
}

void HttpHandler::run() {
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

      string req = string(data.begin(), data.begin() + ((read < MAX_REQ_SZ) ? read : MAX_REQ_SZ));

      Request* request = Parser::createRequest(req) ;

      if(request == NULL){
        perror("failed to create request is corrupter or in complete\n") ;
          continue;
      }
      // re-initialize the time.
      time(&startTime);
      if(request->getKey_val("Connection") == "close"){
        finished = true;
      }

      if(request->getMethod() == GET){
        handleGet(request);
      } else if(request->getMethod() == POST){
        handlePost(request);
      }
      delete request;

    }while (!finished);
    // Error
}

void HttpHandler::handleGet(Request *request) {

     string fileName = request->getFileName();
     int sz = IOHandler::getFileSize(Server , fileName);
    Response *res = NULL;
    if(sz == -1){
         // Error
         res = new Response(false, serverName);
         string r = res->toString();
         PortHandler::write(socket_fd, (char*)r.c_str(), r.size());
         delete res;
         return;
     }
     vector<char> data(sz,0);
     IOHandler::readData( Server , fileName, &data[0], sz);
     res = new Response(true, serverName);

     res->setKeyVal("Last-Modified", IOHandler::getLastModified(Server , fileName));
     res->setKeyVal("Content-Length", to_string(sz));
     res->setKeyVal("Content-Type", IOHandler::getContentType(Server , fileName));

     res->setBody(string(data.begin(),data.end()));
     string r = res->toString();

     PortHandler::write(socket_fd, (char*)r.c_str(), r.size());
     delete res;
     }

void HttpHandler::handlePost(Request *request) {

    string body = request->getBody();
    char* data = (char*)body.c_str();

    string fileName = request->getFileName();


    int status = IOHandler::writeData( Server , fileName, data, body.size());

    HttpMessage *res = new Response(status != -1, serverName);
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

void HttpHandler::finish() {
    finished = true;
}

bool HttpHandler::isFinished() {
    return this->finished;
}

time_t HttpHandler::getCreateTime() {
    return this->startTime;
}

void HttpHandler::runAndClose() {
    pthread_cleanup_push(closeHelper, (void *)this);
    run();
    pthread_cleanup_pop(1);
}

void* HttpHandler::startHelper(void *runner) {
    ((HttpHandler*)runner)->runAndClose();
}

void HttpHandler::closeHelper(void *runner) {
    delete ((HttpHandler*)runner);
}

void HttpHandler::close() {
    PortHandler::closeConnection(socket_fd);
}
