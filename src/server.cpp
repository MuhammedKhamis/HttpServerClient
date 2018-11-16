/* import libraries */
/*************************************/
#include <stdio.h> 
#include <string>
#include "./server-module/HttpServer.h"
using namespace std;

/* main function */
/*************************************/
int main(int argc, char const *argv[]) 
{ 
	// init parameters
	string dataDirectory = "../data/server/";
	int maxWaitingQueue = 5;
	int maxWorkerThreads = 5;
	int serverPort = 8000;
	int connectionTimeout = 5000;

	// run server
    HttpServer server(dataDirectory, maxWorkerThreads, maxWaitingQueue, serverPort, connectionTimeout);
    server.init();
    server.run();
    return 0; 
} 
