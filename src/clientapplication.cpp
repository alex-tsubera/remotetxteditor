//File: clientapplication.cpp
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
#include "src/clientapplication.h"
#include <stdio.h>
#include "src/package.h"

ClientApplication::ClientApplication()
  : client_(Client::kDefaultPort_, Client::kDefaultIpAddress_),
    menu_(), editor_() {}

void ClientApplication::ProcessUserInputs() {
  menu_.PrintGreetings();
  menu_.ShowMenuCommands(kMainMenu);
  client_.InitSocket();
  if(!client_.Connect()) { //Try connect to server
    printf("Could not connect to server. Please try to reconnect.\n");
  }
  int input;
  do {
    printf("Enter your action> ");
    ReadUserInput(&input);
    switch(input) {
      case kExit : { //Exit.
        break;
      }
      case kFileRequest : { //Text file request.
        ProcessFileRequestMenuInputs();
        break;
      }
      case kFileUpdate : { //File update request
        ProcessUpdateMenuInputs();
        break;
      }
      case kReconnect : { //Reconnect to server.
        Reconnect();
        break;
      }
      default : {
        printf("You have entered wrong action.\n");
      }
    }
  } while(input);
}

void ClientApplication::ProcessFileRequestMenuInputs() {
  printf("Enter offset> ");
  uint32_t offset;
  ReadUserInput(&offset);
  editor_.SetOffset(offset);
  printf("Enter file name> ");
  char* buf = new char[Package::kDataSize];
  ReadUserInput(buf);
  Package package;
  package.SetOffset(offset);
  package.SetData(buf);
  FileRequest(package);
  //Check if type is not equal 1 that means
  //everything is OK.
  if(!package.GetType()) {
    editor_.SetFileName(buf);
    editor_.LoadText(package.GetData());
    PrintTextFile();
  } else {
    printf("%s", package.GetData());
  }
  delete [] buf;
}

void ClientApplication::ProcessUpdateMenuInputs() {
  if(editor_.GetFileName() == "") {
    printf("Please request file first.\n");
    return;
  }
  menu_.ShowMenuCommands(kFileUpdate);
  int input;
  uint32_t offset;
  char* buf = new char[Package::kDataSize];
  do {
    printf("Enter your action> ");
    ReadUserInput(&input);
    switch(input) {
      case kExit : {
        break;
      }
      case kAddLine : {
        printf("Enter text for a new line> ");
        ReadUserInput(buf);
        editor_.AddLine(buf);
        break;
      }
      case kRemoveLine : {
        printf("Enter line number to remove> ");
        ReadUserInput(&offset);
        if(offset < editor_.GetLinesCount()) {
          editor_.RemoveLine(offset);
        } else {
          printf("There is no line like this.\n");
        }
        break;
      }
      case kInsertLine : {
        printf("Enter line number to insert> ");
        ReadUserInput(&offset);
        if(offset < editor_.GetLinesCount()) {
          printf("Enter text for a new line> ");
          ReadUserInput(buf);
          editor_.InsertLine(buf, offset);
        } else {
          printf("There is no line like this.\n");
        }
        break;
      }
      case kEditLine : {
        printf("Enter line number to edit> ");
        ReadUserInput(&offset);
        if(offset < editor_.GetLinesCount()) {
          printf("Enter new text for the line> ");
          ReadUserInput(buf);
          editor_.EditLine(buf, offset);
        } else {
          printf("There is no line like this.\n");
        }
        break;
      }
      case kUpdateChanges : {
        Package package;
        FileUpdateRequest(package);
        printf("%s", package.GetData());
        input = kExit;
        break;
      }
      case kSeeChanges : {
        PrintTextFile();
        break;
      }
      default : {
        printf("You have entered wrong action.\n");
      }
    }
  } while(input);
  delete [] buf;
  editor_.Clear();
  menu_.ShowMenuCommands(kMainMenu);
}

void ClientApplication::FileRequest(Package& package) {
  package.SetType(0);
  //Send package to server.
  if(client_.Send(package, 0) == -1) {
      printf("Could not request file.\n");
  }
  //Receive response from server.
  if(client_.Receive(package, 0) <= 0) {
      printf("Could not receive file.\n");
  }
}

void ClientApplication::FileUpdateRequest(Package& package) {
  package.SetType(1);
  package.SetOffset(editor_.GetOffset());
  string text = editor_.ToString();
  uint32_t pos = 0;
  do {
    package.SetData(text.substr(pos, Package::kDataSize).c_str());
    client_.Send(package, 0);
    pos += Package::kDataSize;
  } while(pos < (text.length()));
  //Send an ending package.
  package.SetType(0);
  package.SetOffset(editor_.GetLength());
  package.SetData("");
  client_.Send(package, 0);
  //Receive update result.
  client_.Receive(package, 0);
}

void ClientApplication::Reconnect() {
  printf("Enter port> ");
  uint16_t port;
  ReadUserInput(&port);
  char* ip_address = new char[16];
  printf("Enter IP address> ");
  ReadUserInput(ip_address);
  client_.CloseSocket();
  client_.InitSocket();
  //Try to reconnect.
  if(!client_.Connect(port, ip_address)) {
    printf("Could not reconnect to server. Please try again.\n");
  } else {
    printf("You have reconnected.\n");
  }
  delete [] ip_address;
}

void ClientApplication::ReadUserInput(int* val) const {
  const uint16_t buf_size = 13;
  char* buf = new char[buf_size];
  buf = fgets(buf, buf_size, stdin);
  if(sscanf(buf, "%d", val) <= 0) *val = -1;
  delete [] buf;
}

void ClientApplication::ReadUserInput(uint32_t* val) const {
  const uint16_t buf_size = 12;
  char* buf = new char[buf_size];
  buf = fgets(buf, buf_size, stdin);
  if(sscanf(buf, "%u", val) <= 0) *val = 0;
  delete [] buf;
}

void ClientApplication::ReadUserInput(uint16_t* val) const {
  const uint16_t buf_size = 6;
  char* buf = new char[buf_size];
  buf = fgets(buf, buf_size, stdin);
  if(sscanf(buf, "%hu", val) <= 0) *val = 0;
  delete [] buf;
}

void ClientApplication::ReadUserInput(char* str) const {
  char* buf = new char[Package::kDataSize];
  buf = fgets(buf, Package::kDataSize, stdin);
  if(sscanf(buf, "%[^\n]s", str) <= 0) str[0] = '\0';
  delete [] buf;
}

void ClientApplication::PrintTextFile() {
  string line(Menu::kScreenWidth, kEqual);
  printf("%s\n", line.c_str());
  printf("Text of %s\n", editor_.GetFileName().c_str());
  printf("%s\n", line.c_str());
  printf("%s\n", editor_.ToString().c_str());
  printf("%s\n", line.c_str());
}
