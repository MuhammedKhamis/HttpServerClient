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
#include <pthread.h>

using namespace std;

enum SERVER_CLIENT { Server , Client };

class IOHandler{

public:
    static int writeData( SERVER_CLIENT type , string fileName, char* data ,int len);
    static int readData( SERVER_CLIENT type , string fileName, char* data , int len);
    static string getLastModified(SERVER_CLIENT type ,string fileName);
    static int getFileSize(SERVER_CLIENT type , string fileName);
    static string getContentType(SERVER_CLIENT type , string fileName);
    static string convertCurrentTimeToString(time_t t);
    static bool fileExist(SERVER_CLIENT type , string fileName);
    static void initFileLock();

 private:
    static string getWorkingDir();
    static pthread_mutex_t fileLock;
    static string getStorageDir(SERVER_CLIENT type);

};
#endif //HTTPSERVERCLIENT_IOHANDLER_H
