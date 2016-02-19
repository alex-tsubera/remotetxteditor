//File: client.cpp
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
#include "src/client.h"
const string Client::kDefaultIpAddress_ = "127.0.0.1";

Client::Client(uint16_t port, const string& ip_address)
  : target_{AF_INET, htons(port),
#ifdef _WIN32
            {{.S_addr = inet_addr(ip_address.c_str())}}
#elif __linux__
            {inet_addr(ip_address.c_str())}
#endif // __linux__
            } {}

bool Client::Connect() {
  //try connecting
  int result = connect(GetSocket(),
                       reinterpret_cast<sockaddr*>(&target_),
                       sizeof(target_));
  if(result == SOCKET_ERROR) return false;  //check if connect is successful
  return true;  //OK
}

bool Client::Connect(uint16_t port, const string& ip_address) {
  //set new target information
  target_.sin_port = htons(port);
  target_.sin_addr.s_addr = inet_addr(ip_address.c_str());
  target_.sin_family = AF_INET;
  return Client::Connect();
}

int Client::Send(const Package& msg, int flags) {
  return NetworkNode::Send(GetSocket(), msg, flags);
}
int Client::Receive(Package& buf, int flags) {
  return NetworkNode::Receive(GetSocket(), buf, flags);
}
