//File: server.cpp
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
#include "src/server.h"
const string Server::kDefaultIpAddress_ = "0.0.0.0";

Server::Server(uint16_t port, const string& ip_address)
  : target_{AF_INET, htons(port),
#ifdef _WIN32
            {{.S_addr = inet_addr(ip_address.c_str())}}
#elif __linux__
            {inet_addr(ip_address.c_str())}
#endif // __linux__
            } {}

bool Server::Listen(uint16_t num_of_conn) {
  //try bind socket
  int result = bind(GetSocket(), reinterpret_cast<sockaddr*>(&target_),
                    sizeof(target_));
  if(result == SOCKET_ERROR) return false;  //check if bind was correct
  listen(GetSocket(), num_of_conn); //start listen
  return true;  //OK
}

bool Server::Listen(uint16_t port, const string& ip_address,
                    uint16_t num_of_conn) {
  //Set new target information
  target_.sin_port = htons(port); //port
  target_.sin_addr.s_addr = inet_addr(ip_address.c_str());  //IP address
  target_.sin_family = AF_INET; //address family Internet
  return Server::Listen(num_of_conn); //run base listen function
}

Socket Server::AcceptConnection() {
  return accept(GetSocket(), NULL, NULL);
}

void Server::CloseConnection(Socket socket) {
#ifdef _WIN32
  closesocket(socket);
#elif __linux__
  close(socket);
#endif
}
