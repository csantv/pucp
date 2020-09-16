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

#ifndef ALGORITHMS_PRIORITY_QUEUE_H
#define ALGORITHMS_PRIORITY_QUEUE_H

typedef struct QueueNode TQueueNode;
typedef TQueueNode * TQueue;

struct QueueNode {
    int elem;
    TQueueNode * next;
};

void create_queue(TQueue*);
void enqueue(TQueue*, int);
void show_queue_elements(TQueue);
int is_empty(TQueue);
int dequeue(TQueue*);
int max_queue_elem(TQueue);

#endif
