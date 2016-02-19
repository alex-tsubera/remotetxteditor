//File: txtfilemanager.cpp
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
#include "src/txtfilemanager.h"
#include <string.h>
#include "src/package.h"

TxtFileManager::TxtFileManager()
  : file_name_(), file_() {}

TxtFileManager::TxtFileManager(const string& file_name)
  : file_name_(file_name), file_(file_name) {}

TxtFileManager::~TxtFileManager() {
  file_.close();
}

const string TxtFileManager::ReadLine() {
  string line = ""; //Buffer to read line.
  if(!file_.eof()) {
    getline(file_, line);
    line += "\n";
  }
  return line;
}

const string TxtFileManager::ReadLine(const uint32_t offset) {
  string line = "";
  if((GetFileSize() >= offset) && (!file_.eof())) {
    file_.seekg(offset);  //Move to position needed.
    line = ReadLine();
  }
  return line;
}

bool TxtFileManager::Update(const string& text, uint32_t from, uint32_t to) {
  static const char* new_file_name = "tmp.txt";
  std::ofstream new_file(new_file_name,
                         std::ios_base::out|std::ios_base::trunc);
  file_.seekg(0);  //Back to beginning.
  Copy(0, from, new_file);  //Copy first part of the file.
  //Write changes to new file.
  new_file.write(text.c_str(), text.length());
  //Copy rest part of the file.
  Copy(to, GetFileSize(), new_file);
  file_.close();
  new_file.close();
  remove(file_name_.c_str());  //Remove old file.
  rename(new_file_name, file_name_.c_str());  //Rename new file as old.
  file_.open(file_name_);
  return true;
}

void TxtFileManager::OpenFile(const string& file_name) {
  if(file_.is_open()) file_.close();
  file_.open(file_name);
  file_name_ = file_name;
}

void TxtFileManager::Copy(uint32_t from, uint32_t to, ofstream& destination) {
  if(from >= to) return;
  file_.seekg(from);
  char buf;
  while(++from < to) {
    file_.get(buf);
    if(!file_.eof()) destination.put(buf);
  }
}

inline uint32_t TxtFileManager::GetFileSize() {
  file_.seekg(0, file_.end);
  return file_.tellg();
}
