// C-Excercises , algoritmos en C que uso
// Copyright (C) 2020   Carlos Toro
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef EXCERCISES_P3_H
#define EXCERCISES_P3_H

typedef enum {false, true} bool;

bool solve_ips(int, char*, int, char [4][4]);
bool is_valid(char [4][4], char*);
void print_ip(char [4][4]);

#endif //EXCERCISES_P3_H
