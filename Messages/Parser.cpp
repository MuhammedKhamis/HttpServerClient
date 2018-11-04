//
// Created by abdelrhman on 11/4/18.
//

#include <sstream>
#include "Parser.h"

Parser::Parser() {}

vector<string> Parser::tokenize(string s) {
  vector <string> tokens;

  stringstream check1(s);

  string intermediate ;

  // Tokenizing w.r.t. space ' '
  while(getline(check1, intermediate))
  {
    tokens.push_back(intermediate);
  }
  return tokens;
}
