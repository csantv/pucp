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

#ifndef EXCERCISES_TORRES_OBSTACULO_H
#define EXCERCISES_TORRES_OBSTACULO_H

typedef enum {false, true} bool;

bool solve_torres(int n, int [n][n], int, int, int*);
void print_board(int n, int [n][n]);
bool is_safe(int n, int [n][n], int, int);

#endif
