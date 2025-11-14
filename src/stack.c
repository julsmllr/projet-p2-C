#include "../include/stack.h"

#include <process.h>


void push(t_stack *stack, t_tarjan_cell *noeud) {
    noeud->next = stack->head;
    stack->head = noeud;
}

t_tarjan_cell* top(t_stack *stack) {
    if (stack->head == NULL) {
        printf("Stack empty");
        exit(EXIT_FAILURE);
    }
    return stack->head;
}

t_tarjan_cell* pop(t_stack *stack) {
    t_tarjan_cell* topNoeud = top(stack);
    stack->head = topNoeud->next;
    return topNoeud;
}