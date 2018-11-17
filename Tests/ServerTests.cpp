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

BOOST_AUTO_TEST_SUITE(suite2, * utf::label("HttpServer"))

BOOST_AUTO_TEST_CASE( test_server_intialization )
    {
        //creating server with directory none , 20 workers
        // , 1000 queue size  , on port 8080 , with 5 seconds time out
        HttpServer server(20 , 1000 , 8000 , 5);

    BOOST_REQUIRE_NO_THROW( server.initServer() ) ;
    }

BOOST_AUTO_TEST_CASE( test_server_read )
    {
        //creating server with directory none , 20 workers
        // , 1000 queue size  , on port 8080 , with 5 seconds time out
        HttpServer server(20 , 1000 , 8000 , 5);
        server.initServer() ;
        server.run() ;
        BOOST_REQUIRE_NO_THROW( server.initServer() ) ;
    }

BOOST_AUTO_TEST_SUITE_END()

