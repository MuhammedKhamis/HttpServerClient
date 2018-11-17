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
#include <time.h>
#include <unistd.h>
using namespace std;

class IOHandler{

public:
    static int writeData(string fileName, char* data ,int len);
    static int readData(string fileName, char* data , int len);
    static string getLastModified(string fileName);
    static int getFileSize(string fileName);
    static string getContentType(string &fileName);
    static string convertCurrentTimeToString(time_t t);

private:
    IOHandler();
    static string getWorkingDir();
    static string getExtendedFileName(string fileName);
    static bool fileExist(string fileName);

};
#endif //HTTPSERVERCLIENT_IOHANDLER_H
