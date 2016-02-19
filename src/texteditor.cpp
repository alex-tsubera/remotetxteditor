//File: texteditor.cpp
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
#include "src/texteditor.h"

TextEditor::TextEditor()
  : text_(), file_name_(), offset_(), length_() {}

void TextEditor::AddLine(const string& line) {
  text_.push_back(line);
}

void TextEditor::EditLine(const string& line, uint32_t line_num) {
  list<string>::iterator position = GetPosition(line_num);
  text_.erase(position);
  position = GetPosition(line_num);
  text_.insert(position, line + "\n");
}

void TextEditor::InsertLine(const string& line, uint32_t line_num) {
  list<string>::iterator position = GetPosition(line_num);
  text_.insert(position, line + "\n");
}

void TextEditor::LoadText(const string& text) {
  text_.clear();
  uint32_t from = 0;
  uint32_t to = 0;
  length_ = text.length() - 1;
  string line;
  do {
    to = text.find_first_of('\n', from);
    line = text.substr(from, to - from + 1);
    text_.push_back(line);
    from = to + 1;
  } while (to < length_);
}

void TextEditor::Clear() {
  text_.clear();
  file_name_ = "";
  offset_ = 0;
  length_ = 0;
}

void TextEditor::RemoveLine(uint32_t line_num) {
  list<string>::iterator position = GetPosition(line_num);
  text_.erase(position);
}

const string TextEditor::ToString() {
  string result;
  list<string>::iterator it = text_.begin();
  while(it != text_.end()) {
    result += *it++;
  }
  if(result.back() == '\n') result.pop_back();
  return result;
}

list<string>::iterator TextEditor::GetPosition(uint32_t position) {
  list<string>::iterator position_it = text_.begin();
  while(position) {
    ++position_it;
    --position;
  }
  return position_it;
}
