//
// Created by muhammed on 05/11/18.
//

#ifndef HTTPSERVERCLIENT_HTTPMESSAGE_H
#define HTTPSERVERCLIENT_HTTPMESSAGE_H

#include <bits/stdc++.h>
using namespace std;

enum HTTP_METHODS { GET , POST } ;

class HttpMessage {

public:
    HttpMessage(string body, HTTP_METHODS method);
    HttpMessage();
    virtual void setMethod(HTTP_METHODS method);
    virtual HTTP_METHODS getMethod() const;
    virtual string toString() = 0;
    virtual void setKeyVal(string key, string val) ;
    virtual void setBody(string body);
    virtual string getKey_val(string key);


protected:

    string fieldsAndBody();
    map<string,string> key_val ;
    string body;
    HTTP_METHODS method ;

};

#endif //HTTPSERVERCLIENT_HTTPMESSAGE_H
