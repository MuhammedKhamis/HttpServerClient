//
// Created by muhammed on 02/11/18.
//

#include "IOHandler.h"

IOHandler::IOHandler() {}


bool IOHandler::fileExist(SERVER_CLIENT type , string fileName) {
    fileName = getStorageDir(type) + fileName;
    struct stat buffer;
    return (stat (fileName.c_str(), &buffer) == 0);
}



string IOHandler::getWorkingDir() {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    return string(cwd);
}

int IOHandler::getFileSize(SERVER_CLIENT type , string fileName) {
    if(fileExist(type ,fileName)){
        fileName = getStorageDir(type) + fileName;
        ifstream in(fileName.c_str(), ifstream::ate | ifstream::binary);
        int len = in.tellg();
        in.close();
        return len;
    }
    return -1;
}

string IOHandler::getLastModified(SERVER_CLIENT type , string fileName) {
    if(fileExist(type ,fileName)){
        fileName = getStorageDir(type) + fileName;
        struct stat info;
        stat(fileName.c_str(), &info);
        return convertCurrentTimeToString(info.st_mtim.tv_sec);
    }
    return "";
}

string IOHandler::convertCurrentTimeToString(time_t t) {
    char buf[1000];
    struct tm tm = *gmtime(&t);
    strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);
    return string(buf);
}

string IOHandler::getContentType(SERVER_CLIENT type ,string fileName) {

    fileName = getStorageDir(type) + fileName;
    string contentType;
    string ext = fileName.substr(fileName.find_last_of(".") + 1);
    if ( ext == "html"){
        contentType = "text/html";
    } else if (ext == "txt") {
        contentType = "text/txt";
    } else if (ext == "css") {
        contentType = "text/css";
    } else if (ext == "js") {
        contentType = "text/javascript";
    }else if  (ext == "png") {
        contentType = "image/png";
    } else if (ext == "jpg") {
        contentType = "image/jpg";
    } else if (ext == "jpeg") {
        contentType = "image/jpeg";
    } else if (ext == "svg") {
        contentType = "image/svg";
    }else if (ext == "gif"){
        contentType = "image/gif";
    } else {
        contentType = "none/none";
    }
    return contentType;
}

int IOHandler::readData(SERVER_CLIENT type , string fileName, char *data, int len) {
    if(fileExist(type ,fileName)){
        fileName = getStorageDir(type) + fileName;
        FILE* fp = fopen(fileName.c_str(),"rb");
        int read = fread(data, 1, len, fp);
        fclose(fp);
        return read;
    }
    return -1;
}

int IOHandler::writeData(SERVER_CLIENT type , string fileName, char *data, int len) {
        fileName = getStorageDir(type) + fileName;
        FILE* fp = fopen(fileName.c_str(),"wb+");
        int written = fwrite(data, 1, len, fp);
        fclose(fp);
        return written;
}

string IOHandler::getStorageDir(SERVER_CLIENT type) {
    map<SERVER_CLIENT,string> names = { {Client,"Client"} , {Server,"Server"}} ;
    string dir = getWorkingDir() ;
    while(dir.back() != '/')
        dir.pop_back() ;
        // If you are Yasser remove this comment and continue coding...
    return dir /*+ names[type] */ + "/Files/";
}

