//
// Created by abdelrhman on 11/17/18.
//

#include <boost/test/unit_test.hpp>

#include "../Util/IOHandler.h"
#include <../Server/HttpServer.h>
#include <../Messages/Request.h>
#include <../Client/HttpClient.h>
#include <time.h>
#include <stdio.h>
#include "../Util/Parser.h"

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(suite4, * utf::label("Client"))

  BOOST_AUTO_TEST_CASE( test_client_initializing){
    HttpClient client("dir") ;
    BOOST_REQUIRE(client.connectionInit("127.1.1.1" , 8000) == 0);
  }

  BOOST_AUTO_TEST_CASE( test_client_get){
    HttpClient client("dir") ;
    BOOST_REQUIRE(client.connectionInit("127.1.1.1" , 8000) == 0);
    Request* req = new Request() ;
    req->setMethod(GET) ;
    req->setFileName("smile.jpeg");
    req->setHostName("http/1.1");
    BOOST_REQUIRE(client.sendGETRequest(*req) != -1) ;
    BOOST_REQUIRE(IOHandler::fileExist(Client,"smile.jpeg")) ;
  }

  BOOST_AUTO_TEST_CASE( test_client_post ){
    HttpClient client("dir") ;
    BOOST_REQUIRE(client.connectionInit("127.1.1.1" , 8000) == 0);
    Request* req = new Request() ;
    req->setMethod(POST) ;
    req->setFileName("sent.txt");
    req->setHostName("http/1.1");
    BOOST_REQUIRE(client.sendPOSTRequest(*req) != -1) ;
    BOOST_REQUIRE(IOHandler::fileExist(Server,"sent.txt")) ;
  }

  BOOST_AUTO_TEST_CASE( test_client_server_no_persistent ) {
    HttpClient client("dir") ;
    BOOST_REQUIRE(client.connectionInit("127.1.1.1" , 8000) == 0);
    Request* req = new Request() ;
    req->setMethod(GET) ;
    req->setFileName("sent.txt");
    req->setHostName("http/1.1");
    req->setKeyVal("Connection","close");
    BOOST_REQUIRE(client.sendGETRequest(*req) != -1) ;
    // second request must fail as close happens
    req = new Request() ;
    req->setMethod(GET) ;
    req->setFileName("sent.txt");
    req->setHostName("http/1.1");
    BOOST_REQUIRE(client.sendGETRequest(*req) == -1) ;
  }

  BOOST_AUTO_TEST_CASE( test_client_server_persistent ) {
    HttpClient client("dir") ;
    BOOST_REQUIRE(client.connectionInit("127.1.1.1" , 8000) == 0);
    Request* req = new Request() ;
    req->setMethod(GET) ;
    req->setFileName("sent.txt");
    req->setHostName("http/1.1");
    BOOST_REQUIRE(client.sendGETRequest(*req) != -1) ;
    req = new Request() ;
    req->setMethod(GET) ;
    req->setFileName("sent.txt");
    req->setHostName("http/1.1");
    BOOST_REQUIRE(client.sendGETRequest(*req) != -1) ;
  }

  BOOST_AUTO_TEST_CASE( test_client_server_persistent_timeout ) {
    HttpClient client("dir") ;
    BOOST_REQUIRE(client.connectionInit("127.1.1.1" , 8000) == 0);
    Request* req = new Request() ;
    req->setMethod(GET) ;
    req->setFileName("sent.txt");
    req->setHostName("http/1.1");
    BOOST_REQUIRE(client.sendGETRequest(*req) != -1) ;
    // second request must fail as connection is dead
    clock_t endwait;
    endwait = clock () + 6 * CLOCKS_PER_SEC ;
    while (clock() < endwait) {}
    req = new Request() ;
    req->setMethod(GET) ;
    req->setFileName("sent.txt");
    req->setHostName("http/1.1");
    BOOST_REQUIRE(client.sendGETRequest(*req) == -1) ;
  }

BOOST_AUTO_TEST_SUITE_END()
