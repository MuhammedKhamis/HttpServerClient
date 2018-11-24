#ifndef HTTPSERVERCLIENT_HTTPCLIENT_H
#define HTTPSERVERCLIENT_HTTPCLIENT_H

/* import libraries */
/*************************************/
using namespace std ;
#include <stdio.h> 
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <IOHandler.h>
#include <PortHandler.h>
#include <Request.h>
#include <Response.h>
#include <Parser.h>
#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <sys/types.h>


#define MAX_RES_SZ 512000

using namespace std;
/* Class Definition */
/*************************************/
class HttpClient {

	private:
		// attributes
		string dataDirectory;
		int socketfd;
		int timeInterval;

  public:
  	//
    HttpClient(string dataDirectory);
  	~HttpClient();

    // methods
    int connectionInit(char *server_address, int port_no = 8000);
    int sendGETRequests(vector<Request> requestObj);
    int sendPOSTRequest(Request requestObj);
    int closeConnection();
};

#endif
