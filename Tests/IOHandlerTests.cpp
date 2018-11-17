//
// Created by abdelrhman on 11/17/18.
//

#include <boost/test/unit_test.hpp>

#include "../Util/IOHandler.h"
#include <../Server/HttpServer.h>
#include <../Messages/Request.h>
#include <time.h>
#include <stdio.h>
#include "../Util/Parser.h"

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(suite1, * utf::label("IOHandler"))

BOOST_AUTO_TEST_CASE( test_file_exist )
    {
        IOHandler handler;
    BOOST_REQUIRE(handler.getFileSize("smile.jpeg") != -1) ;
    }

BOOST_AUTO_TEST_CASE( test_file_dont_exist )
    {
        IOHandler handler;
    BOOST_REQUIRE(handler.getFileSize("smile_no.jpeg") == -1) ;
    }

BOOST_AUTO_TEST_CASE( test_file_last_modified )
    {
      IOHandler handler;
      struct timespec curr ;

      timespec_get( &curr , TIME_UTC ) ;

      handler.writeData("to_modify.txt" , "now modify ." , 12) ;

      BOOST_REQUIRE(handler.getLastModified("to_modify.txt") == IOHandler::convertCurrentTimeToString(curr.tv_sec) ) ;
    }

BOOST_AUTO_TEST_CASE( test_file_last_modified_wrong )
    {

      IOHandler handler;
      struct timespec curr ;

      timespec_get( &curr , TIME_UTC ) ;

      usleep(1000000);

      handler.writeData("to_modify.txt" , "now modify ." , 12) ;

      BOOST_REQUIRE(handler.getLastModified("to_modify.txt") != IOHandler::convertCurrentTimeToString(curr.tv_sec)) ;

    }

BOOST_AUTO_TEST_CASE( test_file_size )
    {
        IOHandler handler;
    BOOST_REQUIRE(handler.getFileSize("smile.jpeg") == 6467) ;
    }

BOOST_AUTO_TEST_CASE( test_file_read )
    {
        IOHandler handler;
    char data[1024] ;
    handler.readData("read.txt" , data , 16 * sizeof(char) ) ;
    BOOST_REQUIRE( strcmp(data , "successful read") == 0 ) ;
    }

BOOST_AUTO_TEST_CASE( test_file_read_overflow )
    {
        IOHandler handler;
    char data[1024] ;
    BOOST_REQUIRE_NO_THROW( handler.readData("read.txt" , data , 17 * sizeof(char) ) ) ;
    }

BOOST_AUTO_TEST_CASE( test_file_write )
    {
      IOHandler handler;
      string data_str = "write successful" ;
      char* data = (char*) data_str.c_str() ;
      handler.writeData("write.txt" , data , strlen(data) + 1 * sizeof(char) ) ;

      char data2[1024] ;
      handler.readData("write.txt" , data2 , strlen(data) + 1 * sizeof(char) ) ;
      BOOST_REQUIRE( strcmp(data,data2) == 0 ) ;
    }

BOOST_AUTO_TEST_SUITE_END()
