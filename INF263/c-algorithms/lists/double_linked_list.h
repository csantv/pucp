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

#ifndef ALGORITHMS_DOUBLE_LINKED_LIST_H
#define ALGORITHMS_DOUBLE_LINKED_LIST_H

typedef struct Tnode TNode;
typedef TNode* TList;


struct Tnode {
    int data;
    TNode* next;
    TNode* prev;
};

void create_list(TList* ptr_list);
void show_list(TList ptr_list);
void append_node(TList* ptr_list, int data);
int is_empty(TList list);
void insert_begin(TList *ptr_list, int data);
void reverse(TList* ptr_list);
int list_size(TList ptr_list);
void order_list(TList* ptr_list);
void swap_nodes(TNode*,TNode*);

#endif
