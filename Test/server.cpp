////
//// Created by abdelrhman on 11/3/18.
////
//
///******************************************/
///* import libraries */
///******************************************/
//#include <unistd.h>
//#include <stdio.h>
//#include <sys/socket.h>
//#include <stdlib.h>
//#include <netinet/in.h>
//#include <string.h>
//
//
///******************************************/
///* global variables */
///******************************************/
//#define PORT 8000
//
////char *hello = "Hello from server";
//char *hello =
//"HTTP/1.1 200 OK\r\n\
//Date: Sun, 10 Oct 2010 23:26:07 GMT\r\n\
//Server: Apache/2.2.8 (Ubuntu) mod_ssl/2.2.8 OpenSSL/0.9.8g\r\n\
//Last-Modified: Sun, 26 Sep 2010 22:04:35 GMT\r\n\
//Accept-Ranges: bytes\r\n\
//Content-Length: 1024\r\n\
//Connection: Keep-Alive\r\n\
//Content-Type: text\r\n\
//\r\n\
//<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\">\n<html>\n<head>\n   <title>folaaaa</title>\n</head>\n<body>\n <h1>Not Found</h1>\n <p>The requested URL /t.html was not found on this server.</p>\n</body>\n</html>";
//
///******************************************/
///* utility functions */
///******************************************/
//void
//run_server()
//{
//    int server_fd, new_socket, valread;
//    struct sockaddr_in address;
//    int opt = 1;
//    int addrlen = sizeof(address);
//    char buffer[1024] = {0};
//
//
//    // Creating socket file descriptor
//    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
//    {
//        perror("socket failed");
//        exit(EXIT_FAILURE);
//    }
//
//    // Forcefully attaching socket to the port 8080
//    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
//                                                  &opt, sizeof(opt)))
//    {
//        perror("setsockopt");
//        exit(EXIT_FAILURE);
//    }
//    address.sin_family = AF_INET;
//    address.sin_addr.s_addr = INADDR_ANY;
//    address.sin_port = htons( PORT );
//
//    // Forcefully attaching socket to the port 8080
//    if (bind(server_fd, (struct sockaddr *)&address,
//                                 sizeof(address))<0)
//    {
//        perror("bind failed");
//        exit(EXIT_FAILURE);
//    }
//    if (listen(server_fd, 3) < 0)
//    {
//        perror("listen");
//        exit(EXIT_FAILURE);
//    }
//    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
//                       (socklen_t*)&addrlen))<0)
//    {
//        perror("accept");
//        exit(EXIT_FAILURE);
//    }
//    valread = read( new_socket , buffer, 1024);
//    printf("%s\n",buffer);
//    send(new_socket , hello , strlen(hello) , 0 );
//    printf("Hello message sent\n");
//}
//
//
//void
//parse_request()
//{
//
//}
//
//
//int main(int argc, char const *argv[])
//{
//    while(1)
//    {
//        run_server();
//    }
//    return 0;
//}
