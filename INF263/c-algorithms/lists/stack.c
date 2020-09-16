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

#include "stack.h"

int main()
{
    TStack* stack;

    create_stack(&stack);
    push(&stack, 5);
    push(&stack, 3);
    push(&stack, 7);

    show_stack_elems(stack);
    printf("\n");
    pop(&stack);
    show_stack_elems(stack);


    return 0;
}

void create_stack(TStack** ptr_stack)
{
    *ptr_stack = NULL;
}

void push(TStack** ptr_stack, int elem)
{
    TStack * ptrNewNode;
    ptrNewNode = GC_malloc(sizeof(TStack));
    ptrNewNode->value = elem;
    ptrNewNode->next = *ptr_stack;
    *ptr_stack = ptrNewNode;
}

void show_stack_elems(TStack* stack)
{
    if (stack == NULL) {
        return;
    }

    show_stack_elems(stack->next);
    printf("%d ", stack->value);
}

int is_empty(TStack** stack)
{
    return *stack == NULL;
}

int pop(TStack** stack)
{
    TStack * delete;
    int value = -1;

    if (!is_empty(stack)) {
        delete = *stack;
        value = delete->value;
        (*stack) = (*stack)->next;
    }

    return value;
}