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

#include "p2.h"

#include <stdio.h>
#include <gc/gc.h>

int main()
{
    TStack * stackp1 = NULL;
    TStack * stackp2 = NULL;
    TStack * stackp3 = NULL;

    printf("Ingrese los palets: (-1 -1 -1 para terminar):\n");
    while (true) {
        int id, calidad, peso;
        scanf("%d %d %d", &id, &calidad, &peso);
        if (id == -1 && calidad == -1 && peso == -1) {
            break;
        }

        if (peso >= 500) {
            printf("Error en el peso.\n");
            continue;
        }

        TNode * nodo = GC_malloc(sizeof(TNode));
        nodo->peso = peso;
        nodo->id = id;
        nodo->calidad = calidad;

        switch (calidad) {
            case 1:
                push(&stackp1, nodo);
                break;
            case 2:
                push(&stackp2, nodo);
                break;
            case 3:
                push(&stackp3, nodo);
                break;
            default:
                printf("Calidad desconocida!\n");
                break;
        }
    }

    sort_stack(&stackp1);

    return 0;
}

void sort_stack(TStack** stack)
{
    TBinaryTree * tree;
    create_binary_tree(&tree);
    while (*stack) {
        TNode * node = pop(stack);
        insert(&tree, node);
    }

    TNode* curr = tree->root;
    while (true) {
        if (curr) {
            push(stack, curr);
            curr = curr->left;
        } else {
            if (!(*stack)) break;

            curr = pop(stack);
            printf("%d ", curr->id);
            curr = curr->right;
        }
    }

    printf("\n");
}

void create_binary_tree(TBinaryTree** tree)
{
    *tree = GC_malloc(sizeof(TBinaryTree));
    (*tree)->root = NULL;
}

void insert(TBinaryTree** tree, TNode* node)
{
    TNode * new_node = node;
    new_node->left = NULL;
    new_node->right = NULL;

    TNode * aux = (*tree)->root;
    TNode * father = NULL;

    while (aux) {
        father = aux;
        if (node->id <= aux->id) {
            aux = aux->left;
        } else {
            aux = aux->right;
        }
    }

    if (!father) {
        (*tree)->root = new_node;
    } else {
        if (node->id <= father->id) {
            father->left = new_node;
        } else {
            father->right = new_node;
        }
    }
}

void push(TStack** ptr_stack, TNode* node)
{
    TStack * ptrNewNode;
    ptrNewNode = GC_malloc(sizeof(TStack));
    ptrNewNode->value = node;
    ptrNewNode->next = *ptr_stack;
    *ptr_stack = ptrNewNode;
}

TNode* pop(TStack** stack)
{
    TStack * delete;
    TNode * node = NULL;

    if (*stack) {
        delete = *stack;
        node = delete->value;
        (*stack) = (*stack)->next;
    }

    return node;
}