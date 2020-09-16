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

#include "linked_list.h"

int main()
{
    TList list;
    create_list(&list);
    append_node(&list, 6969);
    append_node(&list, 4321);
    append_node(&list, 666);
    append_node(&list, 1234);
    append_node(&list, 999);
    insert_begin(&list, 13232);
    show_list(list);
    //printf("Size: %d\n", list_size(list));
    //show_list(list);
    //reverse(&list);
    //merge_sort(&list);
    // show_list(list);
    //order_list(&list);
    r_reverse(&list);
    show_list(list);
    return 0;
}

void r_reverse(TList* ptr_list)
{
    (*ptr_list) = (*recursive_reverse(ptr_list));
}

TList* recursive_reverse(TList* ptr_list)
{
    if ((*ptr_list) == NULL || (*ptr_list)->next == NULL)
        return ptr_list;

    TNode * head = (*ptr_list);
    TList* rest = recursive_reverse(&(head->next));
    head->next->next = (*ptr_list);
    head->next = NULL;
    return rest;
}

void merge_sort(TList* ptr_list)
{
    TNode * head = *ptr_list;
    TNode *a, *b;

    if ((head == NULL) || (head->next == NULL)) return;

    split_list(head, &a, &b);

    merge_sort(&a);
    merge_sort(&b);

    *ptr_list = merge(a, b);
}

TList merge(TNode* a, TNode* b)
{
    TNode * result = NULL;

    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    if (a->data.data <= b->data.data) {
        result = a;
        result->next = merge(a->next, b);
    } else {
        result = b;
        result->next = merge(a, b->next);
    }

    return result;
}

void split_list(TList orig, TList* res1, TList* res2)
{
    TNode * runner1, *runner2;
    runner1 = orig;
    runner2 = orig->next;

    while (runner2 != NULL) {
        runner2 = runner2->next;
        if (runner2 != NULL) {
            runner1 = runner1->next;
            runner2 = runner2->next;
        }
    }

    *res1 = orig;
    *res2 = runner1->next;
    runner1->next = NULL;
}

void order_list(TList* ptr_list)
{
    int swapped;
    TNode *ptrRunner;
    TNode *ptrLast = NULL;

    do {
        swapped = 0;
        ptrRunner = *ptr_list;
        while (ptrRunner->next != ptrLast) {
            if (ptrRunner->data.data > ptrRunner->next->data.data) {
                swap_nodes(ptrRunner, ptrRunner->next);
                swapped = 1;
            }
            ptrRunner = ptrRunner->next;
        }
        ptrLast = ptrRunner;
    } while (swapped);
}

void swap_nodes(TNode* cur1, TNode* cur2)
{
    TData tmp = cur1->data;
    cur1->data = cur2->data;
    cur2->data = tmp;
}

void create_list(TList* ptr_list)
{
    *ptr_list = NULL;
}

void show_list(TList list)
{
    TNode* ptr_runner = list;
    while (ptr_runner) {
        printf("%d -> ", ptr_runner->data.data);
        ptr_runner = ptr_runner->next;
    }
    printf("NULL\n");
}

void append_node(TList* ptr_list, int data)
{
    TNode * new_node = GC_malloc(sizeof(TNode));
    TData newData = { .data = data};
    new_node->data = newData;
    new_node->next = NULL;

    TNode * ptrRunner = *ptr_list;
    TNode * ptr_last = NULL;

    while (ptrRunner) {
        ptr_last = ptrRunner;
        ptrRunner = ptrRunner->next;
    }

    if (ptr_last) {
        ptr_last->next = new_node;
    } else {
        *ptr_list = new_node;
    }
}

int is_empty(TList list)
{
    return list == NULL;
}

void reverse(TList* ptr_list)
{
    TNode* prev = NULL;
    TNode* curr = *ptr_list;
    TNode* next = NULL;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *ptr_list = prev;
}

int list_size(TList ptr_list)
{
    TNode * ptr_runner = ptr_list;
    int count = 0;
    while (ptr_runner) {
        count++;
        ptr_runner = ptr_runner->next;
    }
    return count;
}

void insert_begin(TList *ptr_list, int data)
{
    TNode * ptrNewNode = GC_malloc(sizeof(TNode));
    TData tData = { .data = data };
    ptrNewNode->data = tData;
    ptrNewNode->next = *ptr_list;
    *ptr_list = ptrNewNode;
}