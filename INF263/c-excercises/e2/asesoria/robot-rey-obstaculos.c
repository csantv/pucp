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

/*
 * Programa que posiciona un rey en un tablero de ajedrez
 * pero con ciertos obstaculos
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "robot-rey-obstaculos.h"

#define BOLDWHITE   "\033[1m\033[37m"
#define BLACK   "\033[30m"
#define RESET   "\033[0m"

int main()
{
    unsigned int total = 0;

    int n = 8;

//    int board[8][8] = {
//            {0,0,0,0,0,0,0,0},
//            {0,0,0,0,0,0,0,0},
//            {0,0,0,0,0,0,0,0},
//            {0,0,0,0,0,0,0,0},
//            {0,0,0,0,0,0,0,0},
//            {0,0,0,0,0,0,0,0},
//            {0,0,0,0,0,0,0,0},
//            {0,0,0,0,0,0,0,0},
//    };
//    int board[8][8] = {
//            {2,0,0,0,2,0,0,0},
//            {2,0,0,0,2,0,0,0},
//            {2,0,0,0,2,0,0,0},
//            {0,0,0,0,0,0,0,0},
//            {0,0,0,0,0,0,0,0},
//            {0,0,2,0,0,0,2,0},
//            {0,0,2,0,0,0,2,0},
//            {0,0,2,0,0,0,2,0},
//    };
    int board[8][8] = {
            {2,2,2,2,2,2,2,2},
            {2,0,0,0,0,0,0,2},
            {2,0,2,2,2,2,0,2},
            {2,0,2,0,0,2,0,2},
            {2,0,2,0,0,2,0,2},
            {2,0,2,2,2,2,0,2},
            {2,0,0,0,0,0,0,2},
            {2,2,2,2,2,2,2,2},
    };
//    int board[8][8] = {
//            {2,0,2,2,2,2,2,2},
//            {2,0,2,0,0,0,0,2},
//            {2,0,2,0,2,2,0,2},
//            {2,0,2,0,0,2,0,2},
//            {2,0,2,0,0,2,0,2},
//            {2,0,2,2,2,2,0,2},
//            {2,0,0,0,0,0,0,2},
//            {2,2,2,2,2,2,2,2},
//    };

//    int n = 4;
//    int board[n][n];
//    memset(board, 0, n*n*sizeof(int));
//    int board[4][4] = {
//            {0,2,0,0},
//            {0,2,0,2},
//            {0,2,0,2},
//            {0,2,0,0},
//    };
//    solve_nk(n, board, 0, &total);

    solve_nk_max(n, board, 0, 0, &total);

    printf("Total Soluciones: %d\n", total);

    return 0;
}

bool solve_nk_max(int n, int board[n][n], int row, int col, unsigned int* total)
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

            if (solve_nk_max(n, board, row, i, total)) {
                return true;
            }

            board[row][i] = 0;
        }
    }

    return solve_nk_max(n, board, row + 1, 0, total);
}

bool solve_nk(int n, int board [n][n], int col, int* total)
{
    if ((*total) == 5) {
        // return false;
    }

    if (col >= n) {
        print_board(n, board);
        printf("\n");
        (*total)++;
        return false;
    }

    for (int i = 0; i < n; ++i) {
        if (is_safe(n, board, i, col)) {
            board[i][col] = 1;

            if (solve_nk(n, board, col + 1, total)) {
                return true;
            }

            board[i][col] = 0;
        }
    }

    return false;
}

bool is_safe(int n, int board [n][n], int row, int col)
{
    if (board[row][col] == 2) return false;

    int x_moves[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
    int y_moves[9] = {0, 1, 1, 0, -1, -1, -1, 0, 1};

    for (int i = 0; i < 9; ++i) {
        int new_x = row + x_moves[i];
        int new_y = col + y_moves[i];

        if (0 <= new_x && new_x < n && 0 <= new_y && new_y < n) {
            if (board[new_x][new_y] == 1) return false;
        }
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
                    printf("R");
                    break;
                case 0:
                    printf("_");
                    break;
            }
        }
        printf("\n");
    }
}