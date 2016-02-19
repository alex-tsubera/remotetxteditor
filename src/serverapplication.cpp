//File: serverapplication.cpp
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
#include "src/serverapplication.h"
#include "src/server.h"

ServerApplication::ServerApplication()
  : server_(Server::kDefaultPort_, Server::kDefaultIpAddress_),
    client_socket_(), file_manager_() {}

void ServerApplication::Run() {
  uint16_t clients_count = 1;
  server_.InitSocket();
  if(!server_.Listen(clients_count)) {
    printf("Could not start listening.\n");
    return;
  }
  printf("Listening on port %d...\n", Server::kDefaultPort_);
  //Accept connection request
  client_socket_ = server_.AcceptConnection();
  int bytes;
  Package package;
  while(client_socket_ != INVALID_SOCKET) {
    //Read first package from client.
    bytes = server_.Receive(client_socket_, package, 0);
    if(bytes <= 0) {
      Server::CloseConnection(client_socket_);
      client_socket_ = server_.AcceptConnection();
      continue;
    }
    if(package.GetType()) { //Update file
      UpdateFile(package);
    } else { //Send text file
      GetFileText(package);
    }
    //Send a package with result.
    server_.Send(client_socket_, package, 0);
  }
}

void ServerApplication::GetFileText(Package& package) {
  file_manager_.OpenFile(package.GetData());
  if(!file_manager_.IsValid()) {
    package.SetData("File not found!\n");
    package.SetType(1);
    return;
  }
  string text = file_manager_.ReadLine(package.GetOffset());
  if(!text.length()) {
    text = "Offset is out of file length.\n";
  } else {
    string line = file_manager_.ReadLine();
    //Fill up the text to the package data size.
    while((text.length() + line.length()) <= Package::kDataSize) {
      text += line;
      if(file_manager_.Eof()) break;
      line = file_manager_.ReadLine();
    }
  }
  package.SetData(text.c_str());
}

void ServerApplication::UpdateFile(Package& package) {
  uint32_t from = package.GetOffset();
  string changes_buf = "";
  //Receive updates and append it to change buffer.
  do {
    changes_buf += package.GetData();
    server_.Receive(client_socket_, package, 0);
  } while(package.GetType());
  //Try to update.
  if(file_manager_.Update(changes_buf, from, from + package.GetOffset())) {
    package.SetData("Update completed.\n");
  } else {
    package.SetData("Could not update file.\n");
  }
}
