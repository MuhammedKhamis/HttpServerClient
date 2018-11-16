//
// Created by abdelrhman on 11/4/18.
//

#include <sstream>
#include <algorithm>
#include <set>
#include "Parser.h"
#include "../http-messages/Request.h"

Parser::Parser() {}

vector<string> Parser::tokenize(string s , string delimiter) {
  vector<string> tokens ;

  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    tokens.push_back(token);
    s.erase(0, pos + delimiter.length());
  }
  tokens.push_back(s) ;
  return tokens ;
}

Response* Parser::createResponse(string data) {

  Response* response = new Response();
  vector<string> tokens = tokenize(data , "\r\n");

  int err = parse_first_line(tokens[0], response);
  if(err != 0 )
    return NULL;

   err = parseString(tokens, response);
   if(err){
     return NULL;
   }
    return response;
}

int Parser::parseString(vector<string> tokens, HttpMessage* message) {

  int err;

  int i = 1;
  for(; i < tokens.size() && tokens[i] != "" ; i++) {
    err = parse_key_val(tokens[i] , message);
    if(err != 0)
      return err ;
  }
  string requestBody;
  while (i + 1 < tokens.size()){
    i++;
    requestBody += tokens[i];
  }
  message->setBody(requestBody);
  return 0;
}

Request Parser::parseInputCommand(string command) {
    vector<string> tokens = tokenize(command, " ");
    string method = tokens[0];
    string fileName = tokens[1];
    string hostName = tokens[2];
    string port = "80";
    if(tokens.size() == 4){
        port = tokens[3];
    }
    HTTP_METHODS methodType = method == "GET" ? GET : POST;
    Request request(methodType, fileName, hostName, port);
    return request;
}

Request* Parser::createRequest(string data) {

  Request* request = new Request();
  vector<string> tokens = tokenize(data , "\r\n");

  int err = parse_first_line(tokens[0], request);
  if(err != 0 )
    return NULL;

  err = parseString(tokens, request);
  if(!err){
    return request;
  }
  return NULL;

}

int Parser::parse_first_line(string f_line, Response *response) {
    vector<string> vstrings = tokenize(f_line , " ") ;
    if(vstrings.size() < 3){
        return -1 ;
    }
    string httpType = vstrings[0];
    string status = vstrings[1];
    response->setStatus(status == "200");

}

int Parser::parse_first_line(string f_line , Request* request) {

    vector<string> vstrings = tokenize(f_line , " ") ;

  if(vstrings.size() != 3){
    perror("First line in request has wrong format\n Required :\n Method File_name Host_name\n") ;
    return -1 ;
  }

  string method_str = vstrings[0] ;
  transform(method_str.begin(), method_str.end(), method_str.begin(), ::tolower) ;

  if(method_str == "get")
    request->setMethod(GET) ;
  else if(method_str == "post")
    request->setMethod(POST) ;
  else {
    perror("wrong method");
    return -1;
  }
  request->setFileName(vstrings[1]) ;
  request->setHostName(vstrings[2]) ;

  return 0 ;
}


int Parser::parse_key_val(string f_line , HttpMessage* request) {

  set<string> key_set = {"A-IM","Accept","Accept-Charset", "Accept-Encoding", "Accept-Language",
                         "Accept-Datetime","Access-Control-Request-Method","Access-Control-Request-Headers",
                         "Authorization",
                         "Cache-Control","Connection","Content-Length","Content-MD5","Content-Type", "Cookie",
                         "Date",
                         "Expect",
                         "Forwarded", "From",
                         "Host",
                         "If-Match", "If-Modified-Since", "If-None-Match", "If-Range", "If-Unmodified-Since",
                         "Max-Forwards",
                         "Origin",
                         "Pragma","Proxy-Authorization",
                         "Range", "Referer",
                         "TE",
                         "User-Agent","Upgrade",
                         "Via",
                         "Warning"} ;

  size_t pos = 0;
  string key , value ;
  if ((pos = f_line.find(": ")) != std::string::npos) {
    key = f_line.substr(0, pos);
    f_line.erase(0, pos + 2);
  }

  value = f_line ;

  if(key.empty() || value.empty()){
    perror("Header line in request has wrong format\nRequired :\nKey: Value\n") ;
    return -1 ;
  }

  request->setKeyVal(key, value);
  return 0 ;
}

