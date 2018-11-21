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
    static int write(int socked_fd, char* buffer, int sz);
    static int read(int socked_fd, vector<char>& total , int sz);
    static int closeConnection(int socked_fd);

private:
    PortHandler();
};

#endif //HTTPSERVERCLIENT_PORTHANDLER_H
