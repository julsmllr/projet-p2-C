#ifndef INC_2526_TI301_PJT_TARJAN_VERTEXT_H
#define INC_2526_TI301_PJT_TARJAN_VERTEXT_H

#include "../include/stack.h"
#include "../include/list_adjacence.h"

typedef struct {
    int id; //n° du sommet
    int tempNum; //N° random
    int accessibleNumber; //N° des noeuds qui communiquent avec
    int inStack; //N° dans la pile ou non
}t_tarjan_vertex;

typedef t_tarjan_vertex* t_tab_tarjan_vertex;


typedef struct s_vertex_cell{
    t_tarjan_vertex* noeud;
    struct s_vertex_cell* next;
}t_vertex_cell;


typedef struct {
    t_vertex_cell* head;
}t_vertex_list; //stocker des vertex dans une liste chainée



typedef struct {
    char* className;
    t_vertex_list  tab;
}t_tarjan_class;

typedef struct s_tarjan_class_cell {
    t_tarjan_class* classe;
    struct s_tarjan_class_cell* next;
}t_tarjan_class_cell;

typedef struct {
    t_tarjan_class_cell* head;
}t_tarjan_class_list; //stocker des classes dans une liste chainée


//-------------------------------------------//

t_tab_tarjan_vertex initTarjanVertexTab(liste_adjacence graphe);


#endif //INC_2526_TI301_PJT_TARJAN_VERTEXT_H