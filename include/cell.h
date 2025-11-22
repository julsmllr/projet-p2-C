#ifndef INC_2526_TI301_PJT_CELL_H
#define INC_2526_TI301_PJT_CELL_H

#include <stdlib.h>

typedef struct s_cell{
    int pointArrive;
    float proba;
    struct s_cell* next;
}t_cell;


//Fonctions

t_cell* createNewCell(int pointArrive, float proba);
#endif //INC_2526_TI301_PJT_CELL_H