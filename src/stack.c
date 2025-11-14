#include "stack.h"


void push(t_stack *stack, t_cell *noeud) {
    noeud->next = stack->head;
    stack->head = noeud;
}

t_cell* top(t_stack *stack) {
    if (stack->head == NULL) {
        printf("Stack empty");
        exit(EXIT_FAILURE);
    }
    return stack->head;
}

t_cell* pop(t_stack *stack) {
    t_cell* topNoeud = top(stack);
    t_cell *cell = stack->head;
    stack->head = cell->next;
    free(cell);
    return topNoeud;
}