#ifndef INC_2526_TI301_PJT_LIST_ADJACENCE_H
#define INC_2526_TI301_PJT_LIST_ADJACENCE_H

#include "list.h"
#include "list_adjacence.h"

//Essayer de changer pour un tableau de t_list pas de t_list*

typedef struct {
    t_list** tab;
    int taille;
}liste_adjacence;

liste_adjacence createEmptyTab(int size);

void printTab(liste_adjacence);

#endif //INC_2526_TI301_PJT_LIST_ADJACENCE_H