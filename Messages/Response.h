//
// Created by abdelrhman on 11/3/18.
//

#ifndef HTTPSERVERCLIENT_RESPONSE_H
#define HTTPSERVERCLIENT_RESPONSE_H

#include <stdio.h>
#include <vector>
#include <string>
#include "HttpMessage.h"

using namespace std ;

class Response: public HttpMessage  {

 public:
  Response(bool status);

  virtual ~Response();

  string toString();


    string getBody(){
        HttpMessage::getBody();
    }

    void setMethod(HTTP_METHODS method){
        HttpMessage::setMethod(method);
    }
    HTTP_METHODS getMethod() const{
        return HttpMessage::getMethod();
    }
    void setKeyVal(string key, string val){
        HttpMessage::setKeyVal(key,val);
    }
    void setBody(string body){
        HttpMessage::setBody(body);
    }
    string getKey_val(string key){
        return HttpMessage::getKey_val(key);
    }
 private:
    bool status;
    string convertCurrentTimeToString();

};

#endif //HTTPSERVERCLIENT_RESPONSE_H
