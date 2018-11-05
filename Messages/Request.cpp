//
// Created by abdelrhman on 11/3/18.
//

#include <iterator>
#include <algorithm>
#include <sstream>
#include <IOHandler.h>
#include "Request.h"


Request::Request()
      :HttpMessage(){}

Request::Request(HTTP_METHODS method, const string &file_name, const string &host_name, const string &body)
    : HttpMessage(body, method), fileName(file_name), hostName(host_name) {

  // Call coming from Client
  key_val["Host"] = host_name;
  key_val["Connection"] = "Keep-Alive";
  key_val["User-Agent"] = "Client/1.0";
  key_val["Accept-Language"] = "en-us";
  key_val["Accept-Encoding"] = "gzip, deflate";
  if(method == POST){
    key_val["Content-Length"] = to_string(this->body.size());
  }
}

void Request::setFileName(const string &file_name) {
  this->fileName = file_name;
}
void Request::setHostName(const string &host_name) {
  this->hostName = host_name;
}

string Request::toString() {
  stringstream ss;
  ss << method << " " << fileName << " " << "HTTP/1.1\r\n";
  ss << fieldsAndBody();
  return ss.str();

}


const string &Request::getFile_name() const {
  return fileName;
}
const string &Request::getHost_name() const {
  return hostName;
}

Request::~Request() {

}
