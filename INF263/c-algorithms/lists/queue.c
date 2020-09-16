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
#include <gc/gc.h>

#include "queue.h"

int main()
{
    TQueue ptrQueue;

    create_queue(&ptrQueue);
    enqueue(&ptrQueue, 8);
    enqueue(&ptrQueue, 666);
    enqueue(&ptrQueue, 7);
    enqueue(&ptrQueue, 19);
    enqueue(&ptrQueue, 3);
    show_queue_elements(ptrQueue);
    printf("=======\n");
    sort_queue(&ptrQueue);
    show_queue_elements(ptrQueue);

    return 0;
}

void sort_queue(TQueue* queue)
{
    int sorted, i;
    TQueueNode * runner = NULL;
    do {
        sorted = 1; i = 0;
        runner = *queue;
        while (runner != NULL) {
            if (!runner->next) break;
            if (runner->elem > runner->next->elem) {
                sorted = 0;
                swap_nodes(queue, i, i + 1);
            }
            runner = runner->next;
            i++;
        }
    } while (!sorted);
}

void swap_nodes(TQueue* queue, int x, int y)
{
    if (x == y) return;

    int i;

    i = 0;
    TQueueNode * prevX = NULL, *currX = *queue;
    while (currX && i != x) {
        prevX = currX;
        currX = currX->next;
        i++;
    }

    i = 0;
    TQueueNode * prevY = NULL, *currY = *queue;
    while (currY && i != y) {
        prevY = currY;
        currY = currY->next;
        i++;
    }

    if (prevX != NULL)
        prevX->next = currY;
    else
        *queue = currY;

    if (prevY != NULL)
        prevY->next = currX;
    else
        *queue = currX;

    if (!currX || !currY) return;

    TQueueNode * temp = currY->next;
    currY->next = currX->next;
    currX->next = temp;
}

int queue_size(TQueue queue)
{
    int size = 0;
    while (queue) {
        queue = queue->next;
        size++;
    }
    return size;
}

void create_queue(TQueue* queue)
{
    *queue = NULL;
}

int is_empty(TQueue queue)
{
    return queue == NULL;
}

int dequeue(TQueue* queue)
{
    TQueueNode * runner, * last;
    int value = -1;

    if (!is_empty(*queue)) {
        last = NULL;
        runner = *queue;
        while (runner->next) {
            last = runner;
            runner = runner->next;
        }
        if (last == NULL)
            *queue = NULL;
        else
            last->next = NULL;
        value = runner->elem;
        return value;
    }

    return value;
}

void enqueue(TQueue* queue, int val)
{
    TQueueNode * ptrNewNode = GC_malloc(sizeof(TQueueNode));
    ptrNewNode->elem = val;
    ptrNewNode->next = *queue;
    *queue = ptrNewNode;
}

void show_queue_elements(TQueue queue)
{
    while (queue != NULL) {
        printf("Elemento: %d\n", queue->elem);
        queue = queue->next;
    }
}