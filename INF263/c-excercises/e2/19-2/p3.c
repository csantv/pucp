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

#include "p3.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char* badip = "255011135\0";

    char pos_ip[4][4] = {
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
    };

    solve_ips(0, badip, 0, pos_ip);

    return 0;
}

bool solve_ips(int begin, char* badip, int row, char pos_ip[4][4])
{
    if (begin >= strlen(badip)) {
        // solo imprimir si estamos en el ultimo trozo
        // y nos encontramos al final de la cadena
        if (row == 4 && begin == strlen(badip)) {
            print_ip(pos_ip);
        }
        return false;
    }

    for (int i = 1; i < 4; ++i) {
        if (is_valid(pos_ip, badip)) {
            // copiar subcadena
            for (int j = begin, k = 0; j < begin + i; ++j, k++) {
                pos_ip[row][k] = badip[j];
            }

            // verificar siguiente solucion
            if (solve_ips(begin + i, badip, row + 1, pos_ip)) {
                return true;
            }

            // backtrack
            for (int j = begin, k = 0; j < begin + i; ++j, k++) {
                pos_ip[row][k] = 0;
            }
        }
    }

    return false;
}

void print_ip(char pos_ip[4][4])
{
    for (int i = 0; i < 4; ++i) {
        printf("%s", pos_ip[i]);
        if (i != 3) {
            printf(".");
        }
    }
    printf("\n");
}

bool is_valid(char pos_ip[4][4], char* badip)
{
    // obtener la cantidad de trozos no nulos
    // y sus longitudes
    int num = 0, total_len = 0;
    for (int i = 0; i < 4; ++i) {
        if (pos_ip[i][0] != 0) num++;
        total_len += strlen(pos_ip[i]);
    }

    if (num == 4 && total_len != strlen(badip)) return false;

    for (int i = 0; i < 4; ++i) {
        if (pos_ip[i][0] != 0) {
            // verificar que todos los trozos sean <= 255
            if (atoi(pos_ip[i]) > 255) return false;

            // verificar que 0 no es prefijo de ningun trozo
            if (strlen(pos_ip[i]) > 1) {
                if (pos_ip[i][0] == '0') return false;
            }
        }
    }

    return true;
}