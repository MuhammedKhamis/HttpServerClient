//
// Created by abdelrhman on 11/3/18.
//

#ifndef HTTPSERVERCLIENT_RESPONSE_H
#define HTTPSERVERCLIENT_RESPONSE_H

#include <stdio.h>
#include <vector>
#include <string>

using namespace std ;

class Response {

 public:
  Response(vector<string> tokens);
  virtual ~Response();

 private:
    vector<string> tokens ;



};

#endif //HTTPSERVERCLIENT_RESPONSE_H
