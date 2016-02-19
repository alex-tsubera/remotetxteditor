//File: serverapplication.h
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
#ifndef REMOTETXTEDITOR_SRC_SERVERAPPLICATION_H
#define REMOTETXTEDITOR_SRC_SERVERAPPLICATION_H

#include "src/server.h"
#include "src/txtfilemanager.h"
//This class represents a server side of a remote text editor
//and provides ability to send and update files that a user requests.
class ServerApplication {
 public:
  ServerApplication();
  ServerApplication(const ServerApplication&) = delete;
  ServerApplication& operator=(const ServerApplication&) = delete;
  ~ServerApplication() = default;
  //This function starts server application.
  void Run();

 private:
  //This function fills a package with a text of file
  //or with a error message.
  void GetFileText(Package& package);
  //This function provides ability to update file by received changes.
  //Result of updating puts in package.
  void UpdateFile(Package& package);
  Server server_;
  Socket client_socket_;
  TxtFileManager file_manager_;
};

#endif // REMOTETXTEDITOR_SRC_SERVERAPPLICATION_H
