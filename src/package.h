//File: package.h
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
#ifndef REMOTETXTEDITOR_SRC_PACKAGE_H
#define REMOTETXTEDITOR_SRC_PACKAGE_H

#include <stdint.h>
#include <string.h>

//This class represents a block of information that network nodes
//use to communicate, e.g. request a text file or file updating.
class Package {
 public:
  static const uint16_t kPackageSize = 1024;
  static const uint16_t kHeadSize = 4;
  static const uint16_t kDataSize = kPackageSize - kHeadSize;
  Package();
  Package(const Package& package);
  Package& operator=(const Package& package);
  ~Package();
  //This function converts a package to C string.
  //Result is a pointer to the string.
  char* ToCStr() const;
  //This function populates a package from C string.
  void FromCStr(char* c_str);
  //This function verifies that the package is valid.
  inline bool IsValid() { return (data_ ? true : false); }
  //Getters and setters.
  inline const uint32_t GetType() { return type_; }
  inline const uint32_t GetOffset() { return offset_; }
  inline const char* GetData() { return data_; }
  inline void SetType(uint32_t type) { type_ = type; }
  inline void SetOffset(uint32_t offset) { offset_ = offset; }
  inline void SetData(const char* data) {
    //Sets data only if data_ and data are not null
    if(data_ && data) memcpy(data_, data, strlen(data) + 1);
  }

 private:
  //Type of message, for example, 0 - text file request,
  //1 - update request.
  uint32_t type_ : 1;
  //Offset in a file from the beginning.
  uint32_t offset_ : 31;
  //Text of file or file name should go here.
  char* data_;
};
//Masks to turn first bit on/off.
enum Masks {
  kFirstBitOn = 0x80000000,
  kFirstBitOff = 0x7FFFFFFF
};

#endif // REMOTETXTEDITOR_SRC_PACKAGE_H
