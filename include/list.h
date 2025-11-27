#ifndef INC_2526_TI301_PJT_LIST_H
#define INC_2526_TI301_PJT_LIST_H

#include "cell.h"
#include <stdio.h>
typedef struct {
    t_cell* head;
}t_list;

t_list* createEmptyList();

void addCellToList(t_list* list, int pointArrive, float proba);

void printList(t_list* list);

#endif //INC_2526_TI301_PJT_LIST_H