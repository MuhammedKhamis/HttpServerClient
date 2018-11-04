//
// Created by abdelrhman on 11/3/18.
//

#ifndef HTTPSERVERCLIENT_REQUEST_H
#define HTTPSERVERCLIENT_REQUEST_H

#include <string>
#include <vector>
#include <map>

using namespace std ;

class Request {

 public:
  Request(vector<string> tokens);
  virtual ~Request();

 private:
  vector<string> tokens ;
  HTTP_METHODS method
  string file_name , host_name ;
  map<string,string> key_val ;

  int parse_first_line() ;
  int parse_key_val(int i) ;


};

#endif //HTTPSERVERCLIENT_REQUEST_H
