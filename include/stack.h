#ifndef INC_2526_TI301_PJT_STACK_H
#define INC_2526_TI301_PJT_STACK_H

#include <stdio.h>
#include "cell.h"

typedef struct s_stack {
    t_cell *head;
} t_stack;

void push(t_stack *stack, t_cell noeud);

t_cell* top(t_stack *stack);

t_cell* pop(t_stack *stack);


#endif //INC_2526_TI301_PJT_STACK_H