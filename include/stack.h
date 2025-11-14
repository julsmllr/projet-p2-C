#ifndef INC_2526_TI301_PJT_STACK_H
#define INC_2526_TI301_PJT_STACK_H

#include <stdio.h>
#include "tarjan_vertex.h"


typedef struct s_tarjan_cell {
    t_tarjan_vertex* tarjanVertex;
    struct s_tarjan_cell* next;
}t_tarjan_cell;

typedef struct s_stack {
    t_tarjan_cell *head;
} t_stack;

void push(t_stack *stack, t_tarjan_vertex* noeud);

t_tarjan_cell* top(t_stack *stack);

t_tarjan_cell* pop(t_stack *stack);


#endif //INC_2526_TI301_PJT_STACK_H
