//File: client.h
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
#ifndef REMOTETXTEDITOR_SRC_CLIENT_H
#define REMOTETXTEDITOR_SRC_CLIENT_H

#include "src/networknode.h"

//This class represents client side.
//Client connects to server and communicates with it.
//To create a client object you need to set a port and an IP address
//of server. Then initialize a socket and connect to server.
//You can use Send and Receive functions to communicate with server.
//You can close socket if work is done.
class Client : public NetworkNode {
 public:
  static const string kDefaultIpAddress_;
  Client(uint16_t port, const string& ip_address);
  virtual ~Client() = default;
  //This function tries to establish a connection with server
  //by current target information
  bool Connect();
  //This function sets a new target and then tries to connect to it
  bool Connect(uint16_t port, const string& ip_address);
  virtual int Send(const Package& msg, int flags);
  virtual int Receive(Package& buf, int flags);

 private:
  sockaddr_in target_;  //target information
};

#endif // REMOTETXTEDITOR_SRC_CLIENT_H
