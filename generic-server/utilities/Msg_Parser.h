/* header def */
/******************************************/
#ifndef MSG_PARSER_H
#define MSG_PARSER_H

/* import libraries */
/******************************************/
#include "Msg_Parser.h"
using namespace std;

/* constructor */
/******************************************/
class Msg_Parser{

public:
	static Request_Msg parse_request(char *request);
    static Response_Msg parse_request(char *response);

private:
    Msg_Parser(){}

};

#endif 
