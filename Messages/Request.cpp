//
// Created by abdelrhman on 11/3/18.
//

#include <iterator>
#include <algorithm>
#include <sstream>
#include "Request.h"

enum HTTP_METHODS { GET , POST } ;

Request::Request(vector<string> tokens) {
    parse_first_line();
    for(int i=1 ; tokens[i] == "" ; i++) {
      parse_key_val(i);
    }
    if(method == POST)
      //Todo parse file
}

Request::~Request() {

}

int Request::parse_first_line() {
  string f_line = tokens[0] ;
  stringstream ss(f_line);
  istream_iterator<string> begin(ss);
  istream_iterator<string> end;
  vector<string> vstrings(begin, end);

  if(vstrings.size() > 2 || vstrings.size() == 0){
    perror("First line in request has wrong format/n Required :/n Method File_name Host_name") ;
    return -1 ;
  }

  string method_str = vstrings[0] ;
  transform(method_str.begin(), method_str.end(), method_str.begin(), ::tolower)

  if(method_str == "get")
    method = GET ;
  else if(method_str == "post")
    method = POST ;
  else
    perror("wrong method");
    return -1 ;

  file_name = vstrings[1] ;
  host_name = vstrings[2] ;

  return 0 ;
}

int Request::parse_key_val(int i) {

  string f_line = tokens[0] ;
  stringstream ss(f_line);
  istream_iterator<string> begin(ss);
  istream_iterator<string> end;
  vector<string> vstrings(begin, end);

  if(vstrings.size() != 2){
    perror("Header line in request has wrong format/n Required : /nKey: Value ") ;
    return -1 ;
  }

  vstrings[0].pop_back() ;

  key_val[vstrings[0]] = vstrings[1] ;

  return 0 ;
}
