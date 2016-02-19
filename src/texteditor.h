//File: texteditor.h
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
#ifndef REMOTETXTEDITOR_SRC_TEXTEDITOR_H
#define REMOTETXTEDITOR_SRC_TEXTEDITOR_H

#include <stdint.h>
#include <string>
#include <list>
#include <iterator>
using std::list;
using std::string;

//This class should help to edit file text in console
//on client side.
class TextEditor {
 public:
  TextEditor();
  TextEditor(const TextEditor&) = delete;
  TextEditor& operator=(const TextEditor&) = delete;
  ~TextEditor() = default;
  //This function adds new line at the end of text.
  void AddLine(const string& line);
  //This function removes line by number.
  void RemoveLine(uint32_t line_num);
  //This function sets new text for line by number.
  void EditLine(const string& line, uint32_t line_num);
  //This function adds new line at given position.
  void InsertLine(const string& line, uint32_t line_num);
  //This function splits text to list of lines for handy modifying.
  void LoadText(const string& text);
  //This function clears up text and any other info.
  void Clear();
  //This function converts list of lines back to string.
  const string ToString();
  //Getters and setters for file attributes.
  inline const string GetFileName() { return file_name_; }
  inline void SetFileName(const string& file_name) { file_name_ = file_name; }
  inline const uint32_t GetOffset() { return offset_; }
  inline void SetOffset(uint32_t offset) { offset_ = offset; }
  inline const uint32_t GetLength() { return length_; }
  inline const uint32_t GetLinesCount() { return text_.size(); }

 private:
  //This function returns an iterator that points to the element
  //at the given position.
  list<string>::iterator GetPosition(uint32_t position);
  list<string> text_;
  string file_name_;
  uint32_t offset_;
  uint32_t length_;
};

#endif // REMOTETXTEDITOR_SRC_TEXTEDITOR_H
