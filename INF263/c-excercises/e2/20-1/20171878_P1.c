// Examen Final 2020-1, pregunta 1
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
 * UTILIZANDO LA ESTRATEGIA BACKTRACK, DISTRIBUIR
 * LA CANTIDAD MAXIMA DE PALETS EN UN ALMACEN.
 * SE UTILIZARA COMO CODIGO BASE EL PROBLEMA DE
 * N-REINAS, MODIFICANDOLO PARA NUESTRAS NECESIDADES.
 * EL ALMACEN SE REPRESENTARA COMO UNA MATRIZ, SIENDO
 * 0 UNA POSICION DISPONIBLE, Y 1 UN PALET.
 * SE UTILIZARA UNA MASACARA DE POSIBLES POSICIONES
 * PARA SIMPLIFICAR LA VERIFICACION.
 * COMO SOLO SE PIDE IMPRIMIR LA PRIMERA SOLUCION, SE
 * UTILIZARA LA FUNCION 'EXIT' PARA TERMINAR EL PROGRAMA
 * UNA VEZ SE OBTENGA LA PRIMERA SOLUCION.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// usar booleanos sin incluir stdbool
typedef enum {false, true} bool;

// prototipo de las funciones a utilizar
bool solve_palets(int n, int m, int [n][m], int, int);
bool is_correct(int n, int m, int [n][m], int, int);
void print_almacen(int n, int m, int [n][m]);
int count_palets(int n, int m, int [n][m]);

int main()
{
    // obtener dimensiones del almacen
    int n, m;
    printf("Ingrese las dimensiones del almacen:\n");
    printf("n = ");
    scanf("%d", &n);
    printf("m = ");
    scanf("%d", &m);

    // inicializar almacen con 0s
    int almacen[n][m];
    memset(almacen, 0, n*m*sizeof(int));

    // mostrar posibilidades
    solve_palets(n, m, almacen, 0, 0);

    return 0;
}

bool solve_palets(int n, int m, int almacen[n][m], int row, int col)
{
    if (row == n) {
        // en esta solucion, la maxima siempre se encuentra
        // al principio, por ende, la cantidad de palets
        // maximos sera en la primera solucion y como nos
        // piden solo imprimir la primera solucion, hacer eso mismo
        int max = count_palets(n, m, almacen);
        printf("\nMaxima cantidad de palets: %d\n", max);
        printf("Posible distribucion:\n\n");
        print_almacen(n, m, almacen);
        printf("\n");
        // es necesario el exit para detener todo el programa
        // si no seguira tratando de encontrar las posibles
        // soluciones restantes
        exit(0);
    }

    // recorrer todas las columnas de una fila
    for (int i = col; i < m; ++i) {
        if (is_correct(n, m, almacen, row, i)) {
            // asignar el palet
            almacen[row][i] = 1;

            // verificar siguiente solucion
            if (solve_palets(n, m, almacen, row, i)) {
                return true;
            }

            // backtrack
            almacen[row][i] = 0;
        }
    }

    // una vez verificada todas las columnas, pasar a la siguiente fila
    return solve_palets(n, m, almacen, row + 1, 0);
}

bool is_correct(int n, int m, int almacen[n][m], int row, int col)
{
    // (0,0) debe estar libre
    if (row == 0 && col == 0) return false;

    // mascara de posibles posiciones
    int x_moves[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
    int y_moves[9] = {0, 1, 1, 0, -1, -1, -1, 0, 1};

    // verificar mascara
    for (int i = 0; i < 9; ++i) {
        int new_x = row + x_moves[i];
        int new_y = col + y_moves[i];

        // si encuentra un palet, no es correcto
        if (0 <= new_x && new_x < n && 0 <= new_y && new_y < m) {
            if (almacen[new_x][new_y] == 1) return false;
        }
    }

    return true;
}

// funcion que imprime los posibles palets
void print_almacen(int n, int m, int almacen[n][m])
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            switch (almacen[i][j]) {
                case 1:
                    printf("P");
                    break;
                case 0:
                    printf("_");
                    break;
            }
        }
        printf("\n");
    }
}

// contar la cantidad de palets en una solucion
int count_palets(int n, int m, int almacen[n][m])
{
    int total = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (almacen[i][j] == 1) total++;
        }
    }

    return total;
}