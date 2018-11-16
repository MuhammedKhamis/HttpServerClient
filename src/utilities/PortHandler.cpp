//
// Created by muhammed on 02/11/18.
//

#include "PortHandler.h"

PortHandler::PortHandler(int socket_fd) {
    this->socked_fd = socket_fd;
}

PortHandler::~PortHandler() {
    closeConnection();
}

int PortHandler::read(char *buffer, int sz) {
    return recv(socked_fd, buffer, sz, 0);
}

int PortHandler::write(char *buffer, int sz) {
    char* ptr = buffer;
    int len = sz;
    while (len){
        int status = send(socked_fd, ptr, len, 0);
        if(status == -1){
            return status;
        }
        ptr+=status;
        len-=status;
    }
    return sz - len;
}

int PortHandler::closeConnection() {
    return close(socked_fd);
}
