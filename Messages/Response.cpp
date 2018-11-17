//
// Created by abdelrhman on 11/3/18.
//

#include "Response.h"

Response::Response() {}

Response::Response(bool status, string serverName)
        : HttpMessage(), status(status){
    // Call coming from Server

    key_val["Date"] = IOHandler::convertCurrentTimeToString(time(nullptr)) ;
    key_val["Server"] = serverName;
    key_val["Accept-Language"] = "en-us";
    key_val["Accept-Encoding"] = "gzip, deflate";
}

string Response::toString() {
    stringstream ss;
    ss << "HTTP/1.1 " << (status ? "200 OK" : "404 Not Found") << "\r\n";
    ss << fieldsAndBody();
    return ss.str();
}

void Response::setStatus(bool status) {
    this->status = status;
}

int Response::getStatus() {
    return this->status ? 200 : 404;
}

Response::~Response() {

}
