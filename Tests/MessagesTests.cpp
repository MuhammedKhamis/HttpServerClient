//
// Created by abdelrhman on 11/3/18.
//

#include <boost/test/unit_test.hpp>

#include "../Util/IOHandler.h"
#include <../Server/HttpServer.h>
#include <../Messages/Request.h>
#include <time.h>
#include <stdio.h>
#include "../Util/Parser.h"

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(suite3, * utf::label("Messages"))

  BOOST_AUTO_TEST_CASE( test_message_request_get ){

    string data = "get /server /http/1.1\r\nHost: local\r\n" ;

    Request* request = Parser::createRequest(data) ;
    BOOST_REQUIRE(request->getMethod() == GET) ;
    BOOST_REQUIRE(request->getFileName() == "/server") ;
    BOOST_REQUIRE(request->getHostName() == "/http/1.1") ;
    BOOST_REQUIRE(request->getKey_val("Host") == "local") ;

  }

BOOST_AUTO_TEST_CASE( test_message_request_get_bad ){

  string data1 = "get \r\nHost: local\r\n" ;
  Request* request1 = Parser::createRequest(data1) ;

  string data2 = "get /server\r\nHost: local\r\n" ;
  Request* request2 = Parser::createRequest(data2) ;

  string data3 = "get /server /http/1.1\r\nlocal\r\n" ;
  Request* request3 = Parser::createRequest(data3) ;

  string data4 = "get /server /http/1.1\r\nHost:\r\n" ;
  Request* request4 = Parser::createRequest(data4) ;

  string data5 = "set /server /http/1.1\r\nHost: local\r\n" ;
  Request* request5 = Parser::createRequest(data5) ;


  BOOST_REQUIRE(request1 == NULL) ;
  BOOST_REQUIRE(request2 == NULL) ;
  BOOST_REQUIRE(request3 == NULL) ;
  BOOST_REQUIRE(request4 == NULL) ;
  BOOST_REQUIRE(request5 == NULL) ;

}


BOOST_AUTO_TEST_SUITE_END()

