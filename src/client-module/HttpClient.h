#ifndef HTTPSERVERCLIENT_HTTPCLIENT_H
#define HTTPSERVERCLIENT_HTTPCLIENT_H

/* import libraries */
/*************************************/
using namespace std ;
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include "../util/IOHandler.h"
#include "../util/PortHandler.h"
#include "../Messages/Request.h"
#include "../Messages/Response.h"
#include <string>

/* Class Definition */
/*************************************/
class HttpClient {

	private:
		// attributes
		string dataDirectory;
		int socketfd;

  public:
  	// constructor
    HttpClient(string dataDirectory);
  	~HttpClient() = default;
    // methods
    int connectionInit(char *server_address, int port_no = 80);
    int sendGETRequest(Request requestObj);
    int sendPOSTRequest(Request requestObj);
};

#endif
