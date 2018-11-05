//
// Created by muhammed on 05/11/18.
//

#include "HttpMessage.h"

HttpMessage::HttpMessage(string body, HTTP_METHODS method) {
    this->body = body;
    this->method = method;
}

HttpMessage::HttpMessage() {}

void HttpMessage::setMethod(HTTP_METHODS method) {
    this->method = method;
}

HTTP_METHODS HttpMessage::getMethod() const {
    return method;
}

void HttpMessage::setBody(string body) {
    this->body = body;
}
string HttpMessage::getKey_val(string key) {
    if(key_val.find(key) == key_val.end()){
        return "";
    }
    return key_val[key];
}

string HttpMessage::fieldsAndBody() {
    stringstream ss;
    for(auto it = key_val.begin(); it != key_val.end() ; it++){
        ss << it->first << ": " << it->second << "\r\n";
    }
    ss << "\r\n";
    ss << body << "\r\n";
    return ss.str();
}

void HttpMessage::setKeyVal(string key, string val) {
    key_val[key] = val;
}