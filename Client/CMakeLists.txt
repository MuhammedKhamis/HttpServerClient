cmake_minimum_required(VERSION 3.10)
project(HttpClient)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")


set(APP_SERVER ../Server)
set(APP_UTIL ../Util)
set(APP_MESSEGES ../Messages)


include_directories(${APP_SERVER})
include_directories(${APP_UTIL})
include_directories(${APP_MESSEGES})

file(GLOB_RECURSE SRC_FILES ${APP_UTIL}/* ${APP_MESSEGES}/*)

add_executable(HttpClient.out
        ${SRC_FILES}
        main.cpp
        HttpClient.cpp
        HttpClient.h)
