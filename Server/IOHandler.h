//
// Created by muhammed on 02/11/18.
//

#ifndef HTTPSERVERCLIENT_IOHANDLER_H
#define HTTPSERVERCLIENT_IOHANDLER_H

/**
 * Used to handle File read/write Data
 * */

#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

class IOHandler{

public:
    IOHandler();

    int writeData(string fileName, char* data);
    int readData(string fileName, char* data);
    time_t getLastModified(string fileName);
    int getFileSize(string fileName);

private:
    bool fileExist(string fileName);

};
#endif //HTTPSERVERCLIENT_IOHANDLER_H
