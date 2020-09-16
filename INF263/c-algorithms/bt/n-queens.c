#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "n-queens.h"

int main()
{
    int n = 8;
    int board[n][n];
    memset(board, 0, n*n*sizeof(int));
    solve_nq(n, board, 0);

    return 0;
}

void print_board(int n, int board[n][n])
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf(" %d ", board[i][j]);
        }
        printf("\n");
    }
}

bool is_safe(int n, int board[n][n], int row, int col)
{
    int i, j;

    // verificar fila
    for (i = 0; i < col; ++i) {
        if (board[row][i])
            return false;
    }

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j])
            return false;
    }

    for (i = row, j = col; j >= 0 && i < n; i++, j--) {
        if (board[i][j])
            return false;
    }

    return true;
}

bool solve_nq(int n, int board[n][n], int col)
{
    if (col >= n) {
        print_board(n, board);
        printf("\n");
    }

    for (int i = 0; i < n; ++i) {
        if (is_safe(n, board, i, col)) {
            board[i][col] = 1;

            if (solve_nq(n, board, col + 1)) {
                return true;
            }

            board[i][col] = 0;
        }
    }

    return false;
}