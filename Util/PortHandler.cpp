//
// Created by muhammed on 02/11/18.
//

#include "PortHandler.h"


int PortHandler::readExact(int socked_fd, vector<char> &total , int sz ) {

  int valread ;
  while(sz) {
    vector<char> buffer(sz, 0);
    valread = read(socked_fd, buffer, sz) ;
    if(valread < 0){
      return -1;
    }
    sz -= valread;
    string r = string(buffer.begin(), buffer.begin() + ((valread < sz) ? valread : sz));
    total.insert(total.end(), r.begin(), r.end());
  }
  return valread ;
}


int PortHandler::writeExact(int socked_fd, char *buffer, int sz) {
  char* ptr = buffer;
  int len = sz;
  while (len){
    int status = write(socked_fd, ptr, len);
    if(status == -1){
      return status;
    }
    ptr+=status;
    len-=status;
  }
  return sz - len;
}

int PortHandler::read(int socked_fd, vector<char> &total , int sz ) {
  return recv(socked_fd, &total[0] , sz, 0) ;
}


int PortHandler::write(int socked_fd, char *buffer, int sz) {
    return send(socked_fd, buffer, sz, 0);
}

int PortHandler::closeConnection(int socked_fd) {
    return close(socked_fd);
}
