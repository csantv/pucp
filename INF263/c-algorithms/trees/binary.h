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

#ifndef ALGORITHMS_BINARY_H
#define ALGORITHMS_BINARY_H

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

typedef enum {false, true} bool;

typedef struct Node TNode;
typedef struct Tree TBinaryTree ;

struct Node {
    int info;
    TNode * left;
    TNode * right;
};

struct Tree {
    TNode * root;
};

void create_binary_tree(TBinaryTree**);
void insert(TBinaryTree**, int);
bool is_empty(TBinaryTree*);
void print_preorder(TNode*);
void print_inorder(TNode*);
void print_postorder(TNode*);
bool is_present(TBinaryTree*, int);
int height(TNode*);
int weight(TNode*);
void remove_node(TBinaryTree**, int);
int min_value(TBinaryTree*);
bool is_balanced(TNode*);
void combine(TBinaryTree**, TNode*);

typedef struct Stack TStack;

struct Stack {
    TNode * value;
    TStack * next;
};

TNode* pop(TStack**);
void push(TStack**, TNode*);
void create_stack(TStack**);

// iterative functions
void it_preorder(TBinaryTree*);
void it_inorder(TBinaryTree*);
void it_postorder(TBinaryTree*);

#endif //ALGORITHMS_BINARY_H
