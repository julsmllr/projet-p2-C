#ifndef INC_2526_TI301_PJT_TARJAN_VERTEXT_H
#define INC_2526_TI301_PJT_TARJAN_VERTEXT_H


typedef struct {
    int id; //n° du sommet
    int tempNum; //N° random
    int accessibleNumber; //N° des noeuds qui communiquent avec
    int inStack; //N° dans la pile ou non
}t_tarjan_vertex;


typedef t_tarjan_vertex** t_tab_tarjan_vertex;

#include "stack.h"
#include "list_adjacence.h"



typedef struct s_vertex_cell{
    t_tarjan_vertex* noeud;
    struct s_vertex_cell* next;
}t_vertex_cell;


typedef struct {
    t_vertex_cell* head;
}t_vertex_list; //stocker des vertex dans une liste chainée



typedef struct {
    int className;
    t_vertex_list* list;
}t_tarjan_class;

typedef struct s_tarjan_class_cell {
    t_tarjan_class* classe;
    struct s_tarjan_class_cell* next;
}t_tarjan_class_cell;

typedef struct {
    t_tarjan_class_cell* head;
}t_tarjan_class_list; //stocker des classes dans une liste chainée

//--------------------- LIENS ENTRE CLASSE ----------------------//

typedef struct {
    t_tarjan_class* classeDepart;
    t_tarjan_class* classeArrivee;
}t_link;


typedef struct s_cell_link {
    t_link* link;
    struct s_cell_link* next;
}t_cell_link;


typedef struct {
    t_cell_link* head;
}t_list_link;



typedef t_tarjan_class** t_tab_node_to_class;


//-------------------------------------------//

t_tab_tarjan_vertex initTarjanVertexTab(liste_adjacence graphe);
t_tarjan_class_list* tarjanFunction(liste_adjacence graphe);

void printPartition(t_tarjan_class_list partition);


t_tab_node_to_class* linkNodeToClass(t_tarjan_class_list partition, liste_adjacence graphe);
t_list_link* linkRecence(liste_adjacence graphe, t_tab_node_to_class tabNodeToClass);
void printLinks(t_list_link linkSummary);


void caracGraphe(t_list_link linkSummary, t_tarjan_class_list classList);
void drawClassesGraphe(t_list_link linkSummary, t_tarjan_class_list classList);
#endif //INC_2526_TI301_PJT_TARJAN_VERTEXT_H