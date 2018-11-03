//
// Created by muhammed on 02/11/18.
//

#include "IOHandler.h"

IOHandler::IOHandler() {}


bool IOHandler::fileExist(string fileName) {
    struct stat buffer;
    return (stat (fileName.c_str(), &buffer) == 0);
}

int IOHandler::getFileSize(string fileName) {
    if(fileExist(fileName)){
        ifstream in(filename.c_str(), ifstream::ate | ifstream::binary);
        int len = in.tellg();
        in.close();
        return len;
    }
    return -1;
}

time_t IOHandler::getLastModified(string fileName) {
    if(fileExist(fileName)){
        struct state info;
        stat(fileName.c_str(), &info);
        return info.st_mtim.tv_sec;
    }
    return -1;
}

int IOHandler::readData(string fileName, char *data, int len) {
    if(fileExist(fileName)){
        FILE* fp = fopen(fileName.c_str(),"rb");
        int read = fread(data, 1, len, fp);
        fclose(fp);
        return read;
    }
    return -1;
}

int IOHandler::writeData(string fileName, char *data, int len) {
    if (fileExist(fileName)){
        FILE* fp = fopen(fileName.c_str(),"wb");
        int written = fwrite(data, 1, len, fp);
        fclose(fp);
        return written;
    }
    return -1;
}

