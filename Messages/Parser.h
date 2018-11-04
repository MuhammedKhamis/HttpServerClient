//
// Created by abdelrhman on 11/4/18.
//

#ifndef HTTPSERVERCLIENT_PARSER_H
#define HTTPSERVERCLIENT_PARSER_H

#include <string>
#include <vector>

using namespace std ;

class Parser {

  private:
    Parser() ;

  public :
    static Parser inst ;
    vector<string> tokenize (string data);
};

#endif //HTTPSERVERCLIENT_PARSER_H
