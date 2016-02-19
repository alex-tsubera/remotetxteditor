//File: menu.h
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
#ifndef REMOTETXTEDITOR_SRC_MENU_H
#define REMOTETXTEDITOR_SRC_MENU_H

#include <vector>
#include <string>
using std::vector;
using std::string;
//Main menu commands.
enum MenuCommands {
  kExit,
  kMainMenu = 0,
  kFileRequest,
  kAddLine = 1,
  kFileUpdate,
  kRemoveLine = 2,
  kReconnect,
  kInsertLine = 3,
  kEditLine,
  kUpdateChanges,
  kSeeChanges
};
//Character constants to make borders.
enum LineBorders {
  kMinus = '-',
  kEqual = '='
};
//This class provides ability to print greetings and menu commands
//to the screen.
class Menu {
 public:
  static const uint16_t kScreenWidth = 79;
  Menu();
  Menu(const Menu&) = delete;
  Menu& operator=(const Menu&) = delete;
  ~Menu() = default;
  //This function prints menu commands to the screen.
  void ShowMenuCommands(MenuCommands command);
  //This function prints a greetings line to a user.
  void PrintGreetings();

 private:
  vector<string> menu_strings_;  //Menu strings for menu commands.
  const string line_;
};

#endif // REMOTETXTEDITOR_SRC_MENU_H
