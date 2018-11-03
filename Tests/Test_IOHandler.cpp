//
// Created by abdelrhman on 11/3/18.
//

#define BOOST_TEST_MODULE Test_IOHandler
#include <../Server/IOHandler.h>
#include <time.h>
#include <stdio.h>
#include <boost/test/included/unit_test.hpp>

class my_exception{};

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
  ofstream modify ;
  struct timespec curr ;


  modify.open("to_modify.txt" , ios::out ) ;

  timespec_get( &curr , TIME_UTC ) ;

  modify << "now modify ." ;

  modify.close() ;

  BOOST_REQUIRE(handler.getLastModified("to_modify.txt") == curr.tv_sec) ;

}

BOOST_AUTO_TEST_CASE( test_file_last_modified_wrong )
{
  IOHandler handler;
  ofstream modify ;
  struct timespec curr ;

  modify.open("to_modify.txt" , ios::out ) ;

  timespec_get( &curr , TIME_UTC ) ;

  usleep(1000000);

  modify << "now modify ." ;

  modify.close() ;

  BOOST_REQUIRE(handler.getLastModified("to_modify.txt") != curr.tv_sec) ;

}

BOOST_AUTO_TEST_CASE( test_file_size )
{
  IOHandler handler;
  BOOST_REQUIRE(handler.getFileSize("smile.jpeg") == 6467) ;
}

BOOST_AUTO_TEST_CASE( test_file_read )
{
  IOHandler handler;
  char* data ;
  handler.readData("read.txt" , data , 15 * sizeof(char) ) ;
  BOOST_REQUIRE( strcmp(data , "successful read") == 0 ) ;
}

BOOST_AUTO_TEST_CASE( test_file_read_overflow )
{
  IOHandler handler;
  char* data ;
  BOOST_REQUIRE_NO_THROW( handler.readData("read.txt" , data , 16 * sizeof(char) ) ) ;
}

BOOST_AUTO_TEST_CASE( test_file_write )
{
  IOHandler handler;
  string data_str = "write successful" ;
  char* data = (char*) data_str.c_str() ;
  handler.writeData("write.txt" , data , strlen(data) * sizeof(char) ) ;

  string read_str ;
  ifstream myfile ("write.txt");
  if (myfile.is_open())
  {
    getline (myfile,read_str) ;
    myfile.close();
  }
  BOOST_REQUIRE( data_str == read_str ) ;
}

