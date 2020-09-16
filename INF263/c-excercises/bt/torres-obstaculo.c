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

#include "torres-obstaculo.h"

#include <stdio.h>
#include <string.h>

int main()
{
    int n = 4, total = 0;
//    int board[n][n];
//    memset(board, 0, n*n*sizeof(int));

    int board[4][4] = {
            {0,2,0,0},
            {0,0,0,0},
            {2,2,0,0},
            {0,0,0,0}
    };

    solve_torres(n, board, 0, 0, &total);

    return 0;
}

bool solve_torres(int n, int board[n][n], int row, int col, int* total)
{
    if (*total == 5) {
//        return false;
    }

    if (row == n) {
        print_board(n, board);
        printf("\n");
        (*total)++;
        return false;
    }

    for (int i = col; i < n; ++i) {
        if (is_safe(n, board, row, i)) {
            board[row][i] = 1;

            if (solve_torres(n, board, row, i, total)) {
                return true;
            }

            board[row][i] = 0;
        }
    }

    return solve_torres(n, board, row + 1, 0, total);
}

bool is_safe(int n, int board [n][n], int row, int col)
{
    // debe estar libre la posicion
    if (board[row][col] != 0) return false;

    // verificar en la misma fila
    for (int i = col; i >= 0; --i) {
        if (board[row][i] == 2) break;
        if (board[row][i] == 1) return false;
    }

    // verificar misma columna
    for (int i = row; i >= 0; --i) {
        if (board[i][col] == 2) break;
        if (board[i][col] == 1) return false;
    }

    return true;
}

void print_board(int n, int board[n][n])
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            switch (board[i][j]) {
                case 2:
                    printf("\u2588");
                    break;
                case 1:
                    printf("T");
                    break;
                case 0:
                    printf("_");
                    break;
            }
        }
        printf("\n");
    }
}