#include <stdio.h>
#include <stdlib.h>

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

typedef struct Stack TStack;

struct Stack {
    TNode * value;
    TStack * next;
};

void create_binary_tree(TBinaryTree**);
void insert(TBinaryTree**, int);
TNode* pop(TStack**);
void push(TStack**, TNode*);
float proporcion(TBinaryTree*);

int main()
{
    TBinaryTree * tree;
    create_binary_tree(&tree);

    int val = 0;

    printf("Ingrese los valores a insertar en el arbol (-1 para terminar)\n");
    while (val != -1) {
        scanf("%d", &val);
        insert(&tree, val);
    }

    printf("Proporcion %.2f", proporcion(tree));

    return 0;
}

float proporcion(TBinaryTree* tree)
{
    TStack * stack = NULL;
    TNode * curr = tree->root;

    float num_nodos = 0, niveles = 0;
    int flag = 0;

    while (true) {
        if (curr) {
            push(&stack, curr);
            curr = curr->left;
            if (!flag) {
                niveles++;
            }
        } else {
            if (!stack) break;
            flag = 1;

            curr = pop(&stack);
            num_nodos++;
            curr = curr->right;
        }
    }

    return num_nodos / niveles;
}

void create_binary_tree(TBinaryTree** tree)
{
    *tree = malloc(sizeof(TBinaryTree));
    (*tree)->root = NULL;
}

void insert(TBinaryTree** tree, int data)
{
    TNode * new_node = malloc(sizeof(TNode));
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

void push(TStack** ptr_stack, TNode* node)
{
    TStack * ptrNewNode;
    ptrNewNode = malloc(sizeof(TStack));
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
        free(delete);
    }

    return node;
}