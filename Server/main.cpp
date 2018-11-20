//
// Created by muhammed on 17/11/18.
//

#include <bits/stdc++.h>
#include "HttpServer.h"

#define workers 100
#define backlog 90

using namespace std;

int main(int argc, char* argv[]){

    if(argc == 2) {
        int port = atoi(argv[1]);
        HttpServer server(workers, backlog, port);
        int status  = server.initServer();
        if(status == 0){
            // run server.
            server.run();
        }else{
            perror("Error in creating Connection\n");
        }
    }
    cout << "Expected 1 argument\n";
    return -1;
}