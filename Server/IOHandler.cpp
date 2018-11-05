//
// Created by muhammed on 02/11/18.
//

#include "IOHandler.h"

IOHandler::IOHandler() {}


bool IOHandler::fileExist(string fileName) {
    fileName = getWorkingDir() + fileName;
    struct stat buffer;
    return (stat (fileName.c_str(), &buffer) == 0);
}

string IOHandler::getWorkingDir() {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    return string(cwd);
}

int IOHandler::getFileSize(string fileName) {
    if(fileExist(fileName)){
        fileName = getWorkingDir() + fileName;
        ifstream in(fileName.c_str(), ifstream::ate | ifstream::binary);
        int len = in.tellg();
        in.close();
        return len;
    }
    return -1;
}

time_t IOHandler::getLastModified(string fileName) {
    if(fileExist(fileName)){
        fileName = getWorkingDir() + fileName;
        struct stat info;
        stat(fileName.c_str(), &info);
        return info.st_mtim.tv_sec;
    }
    return -1;
}



string IOHandler::getContentType(string &fileName) {

    fileName = getWorkingDir() + fileName;
    string contentType;
    if (fileName.substr(fileName.find_last_of(".") + 1) == "html"){
        contentType = "text/html";
    } else if (fileName.substr(fileName.find_last_of(".") + 1) == "txt") {
        contentType = "text/txt";
    } else if (fileName.substr(fileName.find_last_of(".") + 1) == "css") {
        contentType = "text/css";
    } else if (fileName.substr(fileName.find_last_of(".") + 1) == "js") {
        contentType = "text/javascript";
    }else if  (fileName.substr(fileName.find_last_of(".") + 1) == "png") {
        contentType = "image/png";
    } else if (fileName.substr(fileName.find_last_of(".") + 1) == "jpg") {
        contentType = "image/jpg";
    } else if (fileName.substr(fileName.find_last_of(".") + 1) == "jpeg") {
        contentType = "image/jpg";
    } else if (fileName.substr(fileName.find_last_of(".") + 1) == "gif"){
        contentType = "image/gif";
    } else {
        contentType = "none/none";
    }
    return contentType;
}

int IOHandler::readData(string fileName, char *data, int len) {
    if(fileExist(fileName)){
        fileName = getWorkingDir() + fileName;
        FILE* fp = fopen(fileName.c_str(),"rb");
        int read = fread(data, 1, len, fp);
        data[len] = '\0' ;
        fclose(fp);
        return read;
    }
    return -1;
}

int IOHandler::writeData(string fileName, char *data, int len) {
    if (fileExist(fileName)){
        fileName = getWorkingDir() + fileName;
        FILE* fp = fopen(fileName.c_str(),"wb+");
        int written = fwrite(data, 1, len, fp);
        fclose(fp);
        return written;
    }
    return -1;
}

