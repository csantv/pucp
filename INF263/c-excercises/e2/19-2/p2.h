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

#ifndef EXCERCISES_P2_H
#define EXCERCISES_P2_H

// estructuras necesarias
typedef enum {false, true} bool;

// BST
typedef struct Node TNode;
typedef struct Tree TBinaryTree ;

struct Node {
    int id;
    int calidad;
    int peso;
    TNode * left;
    TNode * right;
};

struct Tree {
    TNode * root;
};

void insert(TBinaryTree**, TNode*);
void create_binary_tree(TBinaryTree**);

// Stack
typedef struct Stack TStack;

struct Stack {
    TNode * value;
    TStack * next;
};

TNode* pop(TStack**);
void push(TStack**, TNode*);
void sort_stack(TStack**);

#endif //EXCERCISES_P2_H
