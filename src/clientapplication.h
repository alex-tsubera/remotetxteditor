//File: clientapplication.h
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
#ifndef REMOTETXTEDITOR_SRC_CLIENTAPPLICATION_H
#define REMOTETXTEDITOR_SRC_CLIENTAPPLICATION_H

#include "src/client.h"
#include "src/texteditor.h"
#include "src/menu.h"
//This class represents a client side of a remote text editor
//and provides ability to request text file, change it, and send it back
//to server that updates file.
class ClientApplication {
 public:
  ClientApplication();
  ClientApplication(const ClientApplication&) = delete;
  ClientApplication& operator=(const ClientApplication&) = delete;
  ~ClientApplication() = default;
  //This function processing all user inputs and runs
  //appropriate commands.
  void ProcessUserInputs();

 private:
  //This function provides processing user inputs
  //while requesting a file and run appropriate actions.
  void ProcessFileRequestMenuInputs();
  //This function provides processing user inputs
  //while editing and updating a text of a file.
  void ProcessUpdateMenuInputs();
  //This function requests a text file from server and returns
  //a package with a server response.
  void FileRequest(Package& package);
  //This function requests a file updating from server and returns
  //a package with an updating result.
  void FileUpdateRequest(Package& package);
  //This function tries to reconnect to server.
  void Reconnect();
  //This functions reads user input value to an appropriate type.
  void ReadUserInput(int* val) const;
  void ReadUserInput(uint16_t* val) const;
  void ReadUserInput(uint32_t* val) const;
  //This function reads user input string without end-line character.
  void ReadUserInput(char* str) const;
  //This function prints text and file name that stored in the editor.
  void PrintTextFile();
  Client client_;
  Menu menu_;
  TextEditor editor_;
};

#endif // REMOTETXTEDITOR_SRC_CLIENTAPPLICATION_H
