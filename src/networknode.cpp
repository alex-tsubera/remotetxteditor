//File: networknode.cpp
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
#include "src/networknode.h"

NetworkNode::NetworkNode() : socket_() {}

NetworkNode::~NetworkNode() {
  NetworkNode::CloseSocket();
}

bool NetworkNode::InitSocket() {
#ifdef _WIN32
  WSADATA wsa_data;
  //Start up socket
  int is_error = WSAStartup(kSocketVersion_, &wsa_data);
  if(is_error) return false;
  //Check for right socket version
  if (wsa_data.wVersion != kSocketVersion_) {
    WSACleanup();
    return false;
  }
#endif
  //Initialize socket
  socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(socket_ == INVALID_SOCKET) return false;
  return true; //OK
}

void NetworkNode::CloseSocket() {
#ifdef _WIN32
  closesocket(socket_);
  WSACleanup();
#elif __linux__
  close(socket_);
#endif
}

int NetworkNode::Send(Socket socket, const Package& msg, int flags) {
  char* c_buf = msg.ToCStr();
  if(c_buf == NULL) return -1;  //Not enough memory.
  int bytes = 0;  //Bytes sent.
  int total = 0;  //Total bytes sent.
  while(total < Package::kPackageSize) {
    bytes = send(socket, (c_buf + total), (Package::kPackageSize - total),
                 flags);
    if(bytes == -1) return -1;  //An error occurred.
    total += bytes;
  }
  delete [] c_buf;
  return bytes;
}

int NetworkNode::Receive(Socket socket, Package& buf, int flags) {
  char* c_buf = static_cast<char*>(calloc(Package::kPackageSize, 1));;
  int bytes = 0;  //Bytes received.
  int total = 0;  //Total bytes received.
  while(total < Package::kPackageSize) {
    bytes = recv(socket, (c_buf + total), (Package::kPackageSize - total),
                 flags);
    if(bytes <= 0) break;  //An error occurred.
    total += bytes;
  } //OK
  buf.FromCStr(c_buf);
  free(c_buf);
  return total;
}

