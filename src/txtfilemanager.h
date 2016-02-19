//File: txtfilemanager.h
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
#ifndef REMOTETXTEDITOR_SRC_TXTFILEMANAGER_H
#define REMOTETXTEDITOR_SRC_TXTFILEMANAGER_H

#include <fstream>
#include <string>
using std::fstream;
using std::ofstream;
using std::string;

//This class represents a text file manager that helps
//to work with files, e.g. update client changes.
class TxtFileManager {
 public:
  TxtFileManager();
  TxtFileManager(const string& file_name);
  TxtFileManager(const TxtFileManager&) = delete;
  TxtFileManager& operator=(const TxtFileManager&) = delete;
  ~TxtFileManager();
  //This function checks that file exist and successfully opened.
  inline bool IsValid() { return (!file_.fail()); }
  //Defines whether is end of file or not.
  inline bool Eof() { return file_.eof(); }
  //This function reads line on current position in the file.
  const string ReadLine();
  //This function reads line start with offset position.
  const string ReadLine(const uint32_t offset);
  //This function updates file according to client changes.
  //Returns the success of the update operation.
  bool Update(const string& text, uint32_t from, uint32_t to);
  //This function open new file if it exists and return true if OK.
  void OpenFile(const string& file_name);

 private:
  //This function copies bounded part of the text file to destination file.
  void Copy(uint32_t from, uint32_t to, ofstream& destination);
  //This function returns size of the file.
  inline uint32_t GetFileSize();
  string file_name_;
  fstream file_;
};

#endif // REMOTETXTEDITOR_SRC_TXTFILEMANAGER_H
