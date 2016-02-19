//File: server.h
//
//Copyright (C) 2015  Oleksiy Tsubera
//
//This file is free resource: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//This file is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this file.  If not, see <http://www.gnu.org/licenses/>.
#ifndef REMOTETXTEDITOR_SRC_SERVER_H
#define REMOTETXTEDITOR_SRC_SERVER_H

#include "src/networknode.h"

//This class represents server side.
//It manage connections and requests from clients.
//To create a server object you need to set a port and and IP address.
//Then you should initialize a socket and start listen for connections.
//Then accept a connection and communicate with a client through given
//socket by using Send and Receive functions.
class Server : public NetworkNode {
 public:
  static const string kDefaultIpAddress_;
  Server(uint16_t port, const string& ip_address);
  virtual ~Server() = default;
  //This function allows server to start listen for connections
  //number of that you set. It returns true if everything is OK.
  bool Listen(uint16_t num_of_conn);
  //This function set new target and then starts listen for
  //probably new number of connections.
  bool Listen(uint16_t port, const string& ip_address, uint16_t num_of_conn);
  //This function accepts incoming connection request and
  //returns a client socket.
  Socket AcceptConnection();
  //This function closes accepted connection, namely, closes
  //a client socket.
  static void CloseConnection(Socket socket);

 private:
  sockaddr_in target_;  //target information
};

#endif // REMOTETXTEDITOR_SRC_SERVER_H
