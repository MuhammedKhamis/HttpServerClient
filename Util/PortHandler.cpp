//
// Created by muhammed on 02/11/18.
//

#include "PortHandler.h"


int PortHandler::read(int socked_fd, vector<char> &total , int sz ) {

  int valread ;
  while(sz) {
    vector<char> buffer(sz, 0);
    valread = recv(socked_fd, &buffer[0] , sz, 0) ;

    if(valread < 0){
      return -1;
    }
    sz -= valread;
    string r = string(buffer.begin(), buffer.begin() + ((valread < sz) ? valread : sz));
    total.insert(total.end(), r.begin(), r.end());
  }
  return valread ;
}

int PortHandler::write(int socked_fd, char *buffer, int sz) {
    return send(socked_fd, buffer, sz, 0);
}

int PortHandler::closeConnection(int socked_fd) {
    return close(socked_fd);
}
