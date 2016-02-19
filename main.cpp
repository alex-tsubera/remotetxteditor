//File: main.cpp
//Here is a sample of working with client and server sides.
//It can work only in one mode at the same time.
//You should choose a mode at the start of the program.
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
#include <stdio.h>
#include "src/clientapplication.h"
#include "src/serverapplication.h"

int main() {
  printf("Choose a side (server - 0, client - 1)> ");
  const uint16_t buf_size = 6;
  char* buf = new char[buf_size];
  buf = fgets(buf, buf_size, stdin);
  uint16_t side;
  sscanf(buf, "%hu", &side);
  while(side > 1) {
    printf("Wrong! Try again, please> ");
    buf = fgets(buf, buf_size, stdin);
    sscanf(buf, "%hu", &side);
  }
  delete [] buf;
  if(side == 1) { //Client side
    ClientApplication client_app;
    client_app.ProcessUserInputs();
  } else if(side == 0) { //Server side
    ServerApplication server_app;
    server_app.Run();
  }
  printf("Press any key to continue...");
  side = fgetc(stdin);
  return 0;
}
