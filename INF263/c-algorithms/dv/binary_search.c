// C-Algorithms , algoritmos en C que uso
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

#include <stdio.h>

#include "../utils.h"

int binary_search(int* arr, int begin, int end, int elem)
{
    if (begin > end) return -1;

    int mid = (begin + end) / 2;

    if (arr[mid] == elem) {
        return mid;
    } else if (arr[mid] < elem){
        return binary_search(arr, mid + 1, end, elem);
    } else {
        return binary_search(arr, begin, mid - 1, elem);
    }
}

int main() {
    int N = 10;
    int arr[] = {3, 6, 9, 12, 17, 24, 34, 70, 190, 200};

    int K = 24;

    print_arr(arr, N);
    int index = binary_search(arr, 0, N -1, K);
    if (index != -1) {
        printf("Elemento encontrado en el indice %d.\n", index);
    } else {
        printf("Elemento no encontrado.\n");
    }

    return 0;
}