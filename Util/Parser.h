//
// Created by abdelrhman on 11/4/18.
//

#ifndef HTTPSERVERCLIENT_PARSER_H
#define HTTPSERVERCLIENT_PARSER_H

#include <string>
#include <vector>
#include <Request.h>
#include <Response.h>

using namespace std ;

class Parser {

  private:
    Parser() ;
    static int parseString(vector<string> tokens, HttpMessage* message);

  public :
    static vector<string> tokenize(string s , string delimiter) ;
    static Request* createRequest(string data) ;
    static Response* createResponse(string data);
    static Request parseInputCommand(string command);
    static int parse_first_line(string f_line , Request* request) ;
    static int parse_first_line(string f_line , Response* response) ;
    static int parse_key_val(string f_line , HttpMessage* request) ;
};

#endif //HTTPSERVERCLIENT_PARSER_H
