cmake_minimum_required(VERSION 3.10)
project(HttpServer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

set(Boost_INCLUDE_DIR /mnt/16BE8F73BE8F4A67/program/IDES/boost_1_65_0)

set(APP_SERVER Server)
set(APP_FILES Files)
set(APP_UTIL Util)
set(APP_MESSEGES Messages)
set(APP_TESTS Tests)


find_package(Boost COMPONENTS system filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
include_directories(${APP_SERVER})
include_directories(${APP_UTIL})
include_directories(${APP_MESSEGES})

file(GLOB_RECURSE SRC_FILES ${APP_UTIL}/* ${APP_MESSEGES}/* ${APP_TESTS}/*)


configure_file(${APP_FILES}/smile.jpeg
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${APP_FILES}/read.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${APP_FILES}/write.txt
        ${CMAKE_CURRENT_BINARY_DIR})

configure_file(${APP_FILES}/to_modify.txt
        ${CMAKE_CURRENT_BINARY_DIR} )

add_executable(HttpServer.out
        Server/HttpServer.cpp
        Server/HttpHandler.cpp
        ${SRC_FILES}
        )
