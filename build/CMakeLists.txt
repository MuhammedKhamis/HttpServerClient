cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

add_executable(
		
        server

        ../src/server.cpp

        ../src/server-module/HttpServer.cpp
        ../src/server-module/ConnectionHandler.cpp

        ../src/http-messages/HttpMessage.cpp
        ../src/http-messages/Request.cpp
        ../src/http-messages/Response.cpp

        ../src/utilities/IOHandler.cpp
        ../src/utilities/PortHandler.cpp
        ../src/utilities/Parser.cpp
)
