//
// Created by abdelrhman on 11/3/18.
//

#include <iterator>
#include <algorithm>
#include <sstream>
#include "Request.h"


Request::Request() {}

Request::Request(HTTP_METHODS method, const string &file_name, const string &host_name)
    : method(method), file_name(file_name), host_name(host_name) {}

void Request::setMethod(HTTP_METHODS method) {
  Request::method = method;
}
void Request::setFile_name(const string &file_name) {
  Request::file_name = file_name;
}
void Request::setHost_name(const string &host_name) {
  Request::host_name = host_name;
}
void Request::setKey_val(string key , string val) {
  Request::key_val[key] = val ;
}
HTTP_METHODS Request::getMethod() const {
  return method;
}
const string &Request::getFile_name() const {
  return file_name;
}
const string &Request::getHost_name() const {
  return host_name;
}
string Request::getKey_val(string key){
  return key_val[key];
}

Request::~Request() {

}
