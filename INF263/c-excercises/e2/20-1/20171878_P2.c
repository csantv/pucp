// Examen Final 2020-1, pregunta 2
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

/*
 * ESTRATEGIA
 *
 *
 */

#include <stdio.h>

// utilizar booleanos sin incluir stdbool
typedef enum {false, true} bool;

// prototipos de funciones
bool solve_paquetes(int n, int [n], int, int[2], int*);
bool is_correct(int[2]);

int main()
{
    // obtener datos
    int n;
    printf("Ingrese el numero de paquetes: ");
    scanf("%d", &n);
    int paquetes[n];

    // llenar arreglo de paquetes
    for (int i = 0; i < n; ++i) {
        paquetes[i] = i + 1;
    }

    // posibilidades
    int pos[] = {0, 0};

    int total = 0;

    solve_paquetes(n, paquetes, 0, pos, &total);

    printf("Total posibilidades: %d\n", total);

    return 0;
}

bool solve_paquetes(int n, int paquetes[n], int x, int pos[2], int* total)
{
    if (x == 3) {
        (*total)++;
        return false;
    }

    for (int i = 1; i < 3; ++i) {
        for (int j = x; j <= n - i; ++j) {
            if (is_correct(pos)) {
                for (int k = 0; k < i; ++k) {
                    pos[k] = paquetes[j + k];
                }

                if (solve_paquetes(n, paquetes, j + 1, pos, total)) {
                    return true;
                }

                for (int k = 0; k < i; ++k) {
                    pos[k] = 0;
                }
            }
        }
    }

    return false;
}

bool is_correct(int pos[2])
{
    if (pos[0] != 0 && pos[1] != 0) {
        if (pos[0] == pos[1]) {
            return false;
        }
    }

    return true;
}