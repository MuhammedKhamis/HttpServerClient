//
// Created by muhammed on 02/11/18.
//

#include <semaphore.h>
#include "HttpHandler.h"


HttpHandler::HttpHandler(int socket_fd, string serverName) {
    finished = false;
    this->socket_fd = socket_fd;
    this->serverName = serverName;
}

HttpHandler::~HttpHandler() {
    close();
    cout << "Thread that use fd =  " << socket_fd << " is Closed" << endl;
    sem_post(sema);
}

int HttpHandler::getSocketfd() {
    return socket_fd;
}

pthread_t HttpHandler::getThreadId() {
    return handler_id;
}

void HttpHandler::run() {

        struct pollfd pollFd;

        pollFd.fd = socket_fd;
        pollFd.events = POLLIN;
        vector<Request *> allRequests;
        string reqs;

        int timeInterval = 8 * 100;

    while (!finished) {
        while (true) {

            int activity = poll(&pollFd, 1, timeInterval);

            if ((activity <= 0) && (errno != EINTR)) {
                break;
            }

            vector<char> data(MAX_REQ_SZ, 0);
            int read = PortHandler::read(socket_fd, data, MAX_REQ_SZ);
            if (read <= 0) {
                //Error
                break;
            }
            time(&startTime);
            reqs += string(data.begin(), data.begin() + ((read < MAX_REQ_SZ) ? read : MAX_REQ_SZ));
        }

        // after taking all the requests, now we process them.
        allRequests = Parser::createRequests(reqs);

        for (Request *request : allRequests) {
            if (request->getMethod() == GET) {
                handleGet(request);
            } else if (request->getMethod() == POST) {
                handlePost(request);
            }
            delete request;
        }
    }

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
         PortHandler::writeExact(socket_fd, (char*)r.c_str(), r.size());
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

     PortHandler::writeExact(socket_fd, (char*)r.c_str(), r.size());
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

    PortHandler::writeExact(socket_fd, (char*)r.c_str(), r.size());
    delete res;
}

bool HttpHandler::start(sem_t* sema) {
    time(&startTime);
    this->sema = sema;
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
