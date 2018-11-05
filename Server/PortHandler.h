//
// Created by muhammed on 02/11/18.
//

#ifndef HTTPSERVERCLIENT_PORTHANDLER_H
#define HTTPSERVERCLIENT_PORTHANDLER_H
/**
 * Used to handle data given through socket
 * */

#include <bits/stdc++.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

using namespace std;

class PortHandler{
public:
    PortHandler(int socket_fd);
    virtual ~PortHandler();

    int write( char* buffer, int sz);
    int read( char* buffer, int sz);
    int closeConnection();

private:
    int socked_fd;
};

#endif //HTTPSERVERCLIENT_PORTHANDLER_H
