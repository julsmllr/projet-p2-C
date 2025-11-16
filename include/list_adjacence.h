#ifndef INC_2526_TI301_PJT_LIST_ADJACENCE_H
#define INC_2526_TI301_PJT_LIST_ADJACENCE_H

#include "../include/list.h"
#include "list_adjacence.h"


typedef struct {
    t_list **tab;
    int taille;
    int markovStatus;
}liste_adjacence;

liste_adjacence createEmptyTab(int size);

void printTab(liste_adjacence);

#endif //INC_2526_TI301_PJT_LIST_ADJACENCE_H