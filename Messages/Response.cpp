//
// Created by abdelrhman on 11/3/18.
//

#include "Response.h"

Response::Response(bool status)
        :HttpMessage(), status(status){
    // Call coming from Server

    key_val["Date"] = convertCurrentTimeToString() ;
    key_val["Server"] = "Server/1.0";
    key_val["Accept-Language"] = "en-us";
    key_val["Accept-Encoding"] = "gzip, deflate";
}

string Response::convertCurrentTimeToString() {
    char buf[1000];
    time_t now = time(nullptr);
    struct tm tm = *gmtime(&now);
    strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);
    return string(buf);
}

string Response::toString() {
    stringstream ss;
    ss << "HTTP/1.1 " << (status ? "200 OK" : "404 Not Found") << "\r\n";
    ss << fieldsAndBody();
    return ss.str();
}

Response::~Response() {

}