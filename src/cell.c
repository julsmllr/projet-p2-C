//
// Created by jules on 24/10/2025.
//

#include "../include/cell.h"

t_cell* createNewCell(int pointArrive, float proba) {
    t_cell* newCell = (t_cell*) malloc(sizeof(t_cell));
    newCell->pointArrive = pointArrive;
    newCell->proba = proba;
    newCell->next = NULL;
    return newCell;
}
