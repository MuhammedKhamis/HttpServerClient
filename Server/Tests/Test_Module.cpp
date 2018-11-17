//
// Created by abdelrhman on 11/3/18.
//

#define BOOST_TEST_MODULE Tests
#include <IOHandler.h>
#include "HttpServer.h"
#include <Request.h>
#include <time.h>
#include <stdio.h>
#include <boost/test/included/unit_test.hpp>
#include <Parser.h>

namespace utf = boost::unit_test;

//BOOST_AUTO_TEST_SUITE(suite1, * utf::label("IOHandler"))
//
//BOOST_AUTO_TEST_CASE( test_file_exist )
//{
//  IOHandler handler;
//  BOOST_REQUIRE(handler.getFileSize("smile.jpeg") != -1) ;
//}
//
//BOOST_AUTO_TEST_CASE( test_file_dont_exist )
//{
//  IOHandler handler;
//  BOOST_REQUIRE(handler.getFileSize("smile_no.jpeg") == -1) ;
//}
//
//BOOST_AUTO_TEST_CASE( test_file_last_modified )
//{
//  IOHandler handler;
//  ofstream modify ;
//  struct timespec curr ;
//
//
//  modify.open("to_modify.txt" , ios::out ) ;
//
//  timespec_get( &curr , TIME_UTC ) ;
//
//  modify << "now modify ." ;
//
//  modify.close() ;
//
//  BOOST_REQUIRE(handler.getLastModified("to_modify.txt") == curr.tv_sec) ;
//
//}
//
//BOOST_AUTO_TEST_CASE( test_file_last_modified_wrong )
//{
//  IOHandler handler;
//  ofstream modify ;
//  struct timespec curr ;
//
//  modify.open("to_modify.txt" , ios::out ) ;
//
//  timespec_get( &curr , TIME_UTC ) ;
//
//  usleep(1000000);
//
//  modify << "now modify ." ;
//
//  modify.close() ;
//
//  BOOST_REQUIRE(handler.getLastModified("to_modify.txt") != curr.tv_sec) ;
//
//}
//
//BOOST_AUTO_TEST_CASE( test_file_size )
//{
//  IOHandler handler;
//  BOOST_REQUIRE(handler.getFileSize("smile.jpeg") == 6467) ;
//}
//
//BOOST_AUTO_TEST_CASE( test_file_read )
//{
//  IOHandler handler;
//  char data[1024] ;
//  handler.readData("read.txt" , data , 15 * sizeof(char) ) ;
//  BOOST_REQUIRE( strcmp(data , "successful read") == 0 ) ;
//}
//
//BOOST_AUTO_TEST_CASE( test_file_read_overflow )
//{
//  IOHandler handler;
//  char data[1024] ;
//  BOOST_REQUIRE_NO_THROW( handler.readData("read.txt" , data , 16 * sizeof(char) ) ) ;
//}
//
//BOOST_AUTO_TEST_CASE( test_file_write )
//{
//  IOHandler handler;
//  string data_str = "write successful" ;
//  char* data = (char*) data_str.c_str() ;
//  handler.writeData("write.txt" , data , strlen(data) * sizeof(char) ) ;
//
//  string read_str ;
//  ifstream myfile ("write.txt");
//  if (myfile.is_open())
//  {
//    getline (myfile,read_str) ;
//    myfile.close();
//  }
//  BOOST_REQUIRE( data_str == read_str ) ;
//}
//
//BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(suite2, * utf::label("HttpServer"))

BOOST_AUTO_TEST_CASE( test_server_intialization )
{
  //creating server with directory none , 20 workers
  // , 1000 queue size  , on port 8080 , with 5 seconds time out
  HttpServer server("NONE" , 20 , 1000 , 8000 , 5);

  BOOST_REQUIRE_NO_THROW( server.initServer() ) ;
}

BOOST_AUTO_TEST_CASE( test_server_read )
{
  //creating server with directory none , 20 workers
  // , 1000 queue size  , on port 8080 , with 5 seconds time out
  HttpServer server("NONE" , 20 , 50 , 8000 , 20);
  server.initServer() ;
  server.run() ;

  BOOST_REQUIRE_NO_THROW( server.initServer() ) ;
}

BOOST_AUTO_TEST_SUITE_END()

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

