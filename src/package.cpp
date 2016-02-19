//File: package.cpp
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
#include "src/package.h"
#include <stdio.h>
#include <stdlib.h>

Package::Package()
  : type_(0), offset_(0), data_(new char [kDataSize]) {}

Package::Package(const Package& package)
  : type_(package.type_), offset_(package.offset_),
    data_(new char [kDataSize]) {
  SetData(package.data_);
}

Package& Package::operator=(const Package& package) {
  if(this == &package) {
    type_ = package.type_;
    offset_ = package.offset_;
    SetData(package.data_);
  }
  return *this;
}

Package::~Package() { free(data_); }

char* Package::ToCStr() const {
  char* str = new char [kPackageSize];
  if(str) { //OK
    //Set first bit of head to 1 or 0.
    uint32_t head = type_ ? (offset_ | kFirstBitOn)
                          : (offset_ & kFirstBitOff);
    //Put head at start of string.
    *(reinterpret_cast<uint32_t*>(str)) = head;
    //Copy data next to head.
    sprintf((str + kHeadSize), "%s", data_);
  }
  return str;
}

void Package::FromCStr(char* c_str) {
  static const uint16_t kByteBits = 8;
  static const uint16_t kHeadBits = kHeadSize * kByteBits;
  //Get type and offset.
  uint32_t head = *(reinterpret_cast<uint32_t*>(c_str));
  //Move bits to right to get first bit.
  type_ = head >> (kHeadBits - 1);
  //First bit will truncate.
  offset_ = head;
  //Next to head is data.
  sprintf(data_, "%s", (c_str + kHeadSize));
}
