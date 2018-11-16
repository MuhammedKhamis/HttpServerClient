#include "ConnectionHandler.h"

/* construtor */
/**************************************/
ConnectionHandler::ConnectionHandler(IOHandler *ioHandler, PortHandler *portHandler, string serverName) {
    this->ioHandler = ioHandler;
    this->portHandler = portHandler;
    handler_id = 0;
    finished = false;
    this->serverName = serverName;
}

/* destrutor */
/**************************************/
ConnectionHandler::~ConnectionHandler() {
    delete portHandler ;
}

/* run handler */
/**************************************/
void ConnectionHandler::run() {
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

/* handle GET requests */
/**************************************/
void ConnectionHandler::handleGet(Request request) {

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

/* handle POST request */
/**************************************/
void ConnectionHandler::handlePost(Request reuqest) {
    //TODO
    int sz = reuqest.getBody().size();
    char* data = (char*)reuqest.getBody().c_str();
    string fileName = reuqest.getFileName();

    int status = ioHandler->writeData(fileName,data,sz);

    HttpMessage *res = new Response(status != -1);
    string r = res->toString();
    portHandler->write((char*)r.c_str(), r.size());
    delete res;
}

/* start thread */
/**************************************/
bool ConnectionHandler::start() {
    time(&startTime);
    return (pthread_create(&handler_id, NULL, startHelper, (void* )this) == 0);
}

bool ConnectionHandler::isFinished() {
    return this->finished;
}

time_t ConnectionHandler::getCreateTime() {
    return this->startTime;
}

void* ConnectionHandler::startHelper(void *runner) {
    ((ConnectionHandler*)runner)->run();
    ((ConnectionHandler*)runner)->close();
    return NULL;
}

void ConnectionHandler::close() {
    this->portHandler->closeConnection();
    this->finished = true;
}
