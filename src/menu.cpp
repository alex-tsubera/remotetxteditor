//File: menu.cpp
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
#include "src/menu.h"
#include <stdio.h>

Menu::Menu()
  : menu_strings_(), line_(kScreenWidth, kMinus) {
  string str;
  str = "Main menu:\n1 - Request text file\n2 - Edit text\n";
  str += "3 - Reconnect to server\n0 - Exit";
  menu_strings_.push_back(str);
  str = "";
  menu_strings_.push_back(str);
  str = "Edit menu:\n1 - Add line\n2 - Remove line\n3 - Insert line\n";
  str += "4 - Edit line\n5 - Update changes\n6 - See changes\n0 - Back to main menu";
  menu_strings_.push_back(str);
}

void Menu::ShowMenuCommands(MenuCommands command) {
  printf("%s\n", line_.c_str());
  printf("%s\n", menu_strings_[command].c_str());
  printf("%s\n", line_.c_str());
}

void Menu::PrintGreetings() {
  printf("%s\n", line_.c_str());
  printf("%s\n", line_.c_str());
  printf("Welcome to remote text editor client application!\n");
  printf("%s\n", line_.c_str());
}
