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

// TODO:
/*
 * TODO:
 * - Combinar 2 arboles usando postorden
 */

#include <stdio.h>
#include <stdlib.h>
#include <gc/gc.h>

#include "binary.h"

int main()
{
    TBinaryTree* tree;
    create_binary_tree(&tree);
    if (is_empty(tree))
        printf("El arbol esta vacio!\n");

    insert(&tree, 12);
    insert(&tree, 16);
    insert(&tree, 7);
    insert(&tree, 4);
    insert(&tree, 3);
    insert(&tree, 2);
    insert(&tree, 20);
    insert(&tree, 21);

    TBinaryTree* tree2;
    create_binary_tree(&tree2);
    insert(&tree2, 13);
    insert(&tree2, 17);
    insert(&tree2, 8);
    insert(&tree2, 5);
    insert(&tree2, 142);
    insert(&tree2, 23);
    insert(&tree2, 256);
    insert(&tree2, 278);

    it_preorder(tree);
    it_postorder(tree);
    it_inorder(tree);

    /*
    print_preorder(tree->root);
    printf("\n");

    combine(&tree, tree2->root);

    print_preorder(tree->root);
    printf("\n");
    */
    // insert(&tree, 9);
    /*
    printf("Imprimir en preorden: ");
    print_preorder(tree->root);
    printf("\n");

    printf("Imprimir en orden: ");
    print_inorder(tree->root);
    printf("\n");

    printf("Imprimir en postorden: ");
    print_postorder(tree->root);
    printf("\n");

    if (!is_empty(tree))
        printf("El arbol no esta vacio!\n");

    if (is_present(tree, 5)) {
        printf("El valor 5 esta presente.\n");
    }

    insert(&tree, 8);
    printf("Imprimir en orden: ");
    print_inorder(tree->root);
    printf("\n");

    remove_node(&tree, 7);
    printf("Imprimir en preorden: ");
    print_preorder(tree->root);
    printf("\n");

    printf("Imprimir en orden: ");
    print_inorder(tree->root);
    printf("\n");

    printf("Imprimir en postorden: ");
    print_postorder(tree->root);
    printf("\n");

    printf("La altura del arbol es %d. \n", height(tree->root));

    printf("El peso del arbol es %d.\n", weight(tree->root));*/

    printf("%d\n", is_balanced(tree2->root));

    return 0;
}

void it_preorder(TBinaryTree* tree)
{
    if (!tree) return;

    TStack * stack = NULL;
    push(&stack, tree->root);

    while (stack) {
        TNode * node = pop(&stack);
        printf("%d ", node->info);

        if (node->right)
            push(&stack, node->right);

        if (node->left)
            push(&stack, node->left);
    }

    printf("\n");
}

void it_inorder(TBinaryTree* tree)
{
    TStack * stack = NULL;
    TNode * curr = tree->root;

    while (true) {
        if (curr) {
            push(&stack, curr);
            curr = curr->left;
        } else {
            if (!stack) break;

            curr = pop(&stack);
            printf("%d ", curr->info);
            curr = curr->right;
        }
    }

    printf("\n");
}

void it_postorder(TBinaryTree* tree)
{
    if (!tree) return;

    TStack * s1 = NULL;
    TStack * s2 = NULL;

    push(&s1, tree->root);

    TNode * node;

    while (s1) {
        node = pop(&s1);
        push(&s2, node);

        if (node->left)
            push(&s1, node->left);

        if (node->right)
            push(&s1, node->right);
    }

    while (s2) {
        node = pop(&s2);
        printf("%d ", node->info);
    }

    printf("\n");
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

void create_stack(TStack** ptr_stack)
{
    *ptr_stack = NULL;
}

void combine(TBinaryTree** dest, TNode* src)
{
    if (!src) return;

    combine(dest, src->left);
    combine(dest, src->right);
    insert(dest, src->info);
    //free(src);
    //src = NULL;
}

bool is_balanced(TNode* node)
{
    if (!node) return true;

    int left_height = height(node->left);
    int right_height = height(node->right);

    return abs(left_height - right_height) <= 1 && is_balanced(node->left) && is_balanced(node->right);
}

int min_value(TBinaryTree* tree)
{
    TNode * node = tree->root;

    while (node->left) {
        node = node->left;
    }

    return node->info;
}

void remove_node(TBinaryTree** tree, int value)
{
    TNode * aux = (*tree)->root;
    TNode * p = NULL;

    // avanzar hasta el nodo con el valor requerido
    while (aux) {
        if (aux->info == value) break;

        p = aux;
        if (value < aux->info) {
            aux = aux->left;
        } else {
            aux = aux->right;
        }
    }

    if (!aux) return; // no hacer nada si no se encontro

    // primer caso, el nodo es una hoja
    if (!aux->left && !aux->right) {
        // el nodo es la raiz
        if (!p) {
            (*tree)->root = NULL;
        } else {
            if (p->left == aux) {
                p->left = NULL;
            } else if (p->right == aux) {
                p->right = NULL;
            }
        }
        return;
    }

    // el nodo tiene 1 solo hijo por la izquierda
    if (aux->left && !aux->right) {
        // el nodo es la raiz
        if (!p) {
            (*tree)->root = aux->left;
        } else {
            if (p->left == aux) {
                p->left = aux->left;
            } else if (p->right == aux) {
                p->right = aux->left;
            }
        }
        return;
    }

    // el nodo tiene 1 solo hijo por la derecha
    if (!aux->left && aux->right) {
        // el nodo es la raiz
        if (!p) {
            (*tree)->root = aux->right;
        } else {
            if (p->left == aux) {
                p->left = aux->right;
            } else if (p->right == aux) {
                p->right = aux->right;
            }
        }
        return;
    }

    // en el caso que el nodo a eliminar tenga 2 hijos
    TNode * q = aux->left;
    while (q->right)
        q = q->right;

    int data = q->info;
    remove_node(tree, data);

    aux->info = data;
}

int weight(TNode* node)
{
    if (!node) return 0;

    return 1 + weight(node->left) + weight(node->right);
}

int height(TNode* node)
{
    if (!node) return 0;

    int left_height = height(node->left);
    int right_height = height(node->right);

    return 1 + max(left_height, right_height);
}

bool is_present(TBinaryTree* tree, int info)
{
    TNode * aux = tree->root;
    while (aux) {
        if (aux->info == info) return true;

        if (info < aux->info) {
            aux = aux->left;
        } else {
            aux = aux->right;
        }
    }
    return false;
}

void print_postorder(TNode* node)
{
    if (!node) return;
    print_postorder(node->left);
    print_postorder(node->right);
    printf("%d ", node->info);
}

void print_inorder(TNode* node)
{
    if (!node) return;
    print_inorder(node->left);
    printf("%d ", node->info);
    print_inorder(node->right);
}

void print_preorder(TNode* node)
{
    if (!node) return;
    printf("%d ", node->info);
    print_preorder(node->left);
    print_preorder(node->right);
}

void create_binary_tree(TBinaryTree** tree)
{
    *tree = GC_malloc(sizeof(TBinaryTree));
    (*tree)->root = NULL;
}

void insert(TBinaryTree** tree, int data)
{
    TNode * new_node = GC_malloc(sizeof(TNode));
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->info = data;

    TNode * aux = (*tree)->root;
    TNode * father = NULL;

    while (aux) {
        father = aux;
        if (data <= aux->info) {
            aux = aux->left;
        } else {
            aux = aux->right;
        }
    }

    if (!father) {
        (*tree)->root = new_node;
    } else {
        if (data <= father->info) {
            father->left = new_node;
        } else {
            father->right = new_node;
        }
    }
}

bool is_empty(TBinaryTree* tree)
{
    return tree->root == NULL;
}