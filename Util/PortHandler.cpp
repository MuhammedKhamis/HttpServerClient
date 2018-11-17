//
// Created by muhammed on 02/11/18.
//

#include "PortHandler.h"


int PortHandler::read(int socked_fd, char *buffer, int sz ) {
    return recv(socked_fd, buffer, sz, 0);
}

int PortHandler::write(int socked_fd, char *buffer, int sz) {
    return send(socked_fd, buffer, sz, 0);
}

int PortHandler::closeConnection(int socked_fd) {
    return close(socked_fd);
}
