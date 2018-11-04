//
// Created by abdelrhman on 11/3/18.
//

#ifndef HTTPSERVERCLIENT_REQUEST_H
#define HTTPSERVERCLIENT_REQUEST_H

#include <string>
#include <vector>
#include <map>


using namespace std ;

enum HTTP_METHODS { GET , POST } ;

class Request {

 public:
  Request();
  Request(HTTP_METHODS method, const string &file_name, const string &host_name);
  virtual ~Request();
  void setMethod(HTTP_METHODS method);
  void setFile_name(const string &file_name);
  void setHost_name(const string &host_name);
  void setKey_val(string key , string val) ;
  HTTP_METHODS getMethod() const;
  const string &getFile_name() const;
  const string &getHost_name() const;
  string getKey_val(string key) ;

 private:
  HTTP_METHODS method ;
  string file_name , host_name ;
  map<string,string> key_val ;



};

#endif //HTTPSERVERCLIENT_REQUEST_H
