//File: networknode.h
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
#ifndef REMOTETXTEDITOR_SRC_NETWORKNODE_H
#define REMOTETXTEDITOR_SRC_NETWORKNODE_H

#ifdef _WIN32
#include <winsock.h>
typedef SOCKET Socket;

#elif __linux__
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)
typedef int Socket;
#endif

#include <string>
#include "src/package.h"
using std::string;

//This abstract class represents a network unit.
//Implementation class for Client and Server classes.
class NetworkNode {
 public:
  static const uint16_t kSocketVersion_ = 0x0202;
  static const uint16_t kDefaultPort_ = 2323;
  NetworkNode();
  virtual ~NetworkNode();
  //This function initializes a socket and returns true if success
  bool InitSocket();
  //This function closes the socket
  void CloseSocket();
  //This function sends a packages fixed size to another network node
  //and returns a number of sent bytes or -1 if not sent
  virtual int Send(Socket socket, const Package& msg, int flags);
  //This function receives a packages fixed size from another network node
  //and returns a number of received bytes, or -1 if not received
  //or 0 if connection was aborted
  virtual int Receive(Socket socket, Package& buf, int flags);
  //Gets socket number
  inline Socket GetSocket() const { return socket_; }

 private:
  Socket socket_; //socket of current network node
};

#endif  // REMOTETXTEDITOR_SRC_NETWORKNODE_H
