# HttpServerClient
In this project, we used sockets to implement a simple web client that communicates
with a web server using a restricted subset of HTTP. The main objective of this project is
to give you hands-on experience with UNIX sockets.

#Server Side
Our web server accepts incoming connection requests. It should then look for the `GET`
request and pick out the name of the requested file. If the request is `POST` then it sends
OK message and wait for the uploaded file from the client. Note that a `GET` request from a
real **WWW** client may have several lines of optional information following the `GET`. These
optional lines, though, will be terminated by a blank line `’\r\n’`

##How to run
You could run the Server using this command.\

`./HttpServer port-number`


#Client Side
Our web client must read and parse a series of commands from input file. For this assignment,
only the `GET` and `POST` commands are required to be handled. The commands syntax should
be as follows:

`GET file-name host-name (port-number)` \
`POST file-name host-name (port-number)`

Note that the port-number is optional. If it is not specified, use the default HTTP port
number, **8000**. In response to the specified operation (`GET` or `POST`), the client must open
a connection to an HTTP server on the specified host listening on the specified (or default)
port-number. The receiver must display the file and then store it in the local directory. The client will shut down
when reaching the end of file.

##How to run

You could run the Client using this command.\

`./HttpClient server-ip port-number`

#Http 1.1
Our server support simple **Http/1.1**, consisting of persistent Connection and `GET` requests pipelining.
In our definition of persistent connection, that is, after the results of a single request are returned (e.g., index.html), the server should
by default leave the connection open for some period of time, allowing the client to reuse that
connection to make subsequent requests. This timeout needs to be configured in the server
and ideally should be dynamic based on the number of other active connections the server is
currently supporting.


#Additional Work
Our server works also with a **FireFox** web browser as Client.


#Design Diagram
Below you will find the design diagram of the project. \
![Diagram](https://github.com/MuhammedKhamis/HttpServerClient/blob/master/Design%20Diagram/design_diagram.png)
