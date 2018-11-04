//
// Created by abdelrhman on 11/4/18.
//

#ifndef HTTPSERVERCLIENT_PARSER_H
#define HTTPSERVERCLIENT_PARSER_H

#include <string>
#include <vector>
#include "Request.h"

using namespace std ;

class Parser {

  private:
    Parser() ;

  public :
    static vector<string> tokenize(string s , string delimiter) ;
    static Request* createRequest(string data) ;
    static int parse_first_line(string f_line , Request* request) ;
    static int parse_key_val(string f_line , Request* request) ;
};

#endif //HTTPSERVERCLIENT_PARSER_H
