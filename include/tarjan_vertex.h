#ifndef INC_2526_TI301_PJT_TARJAN_VERTEXT_H
#define INC_2526_TI301_PJT_TARJAN_VERTEXT_H

typedef struct {
    int id; //n° du sommet
    int tempNum;
    int accessibleNumber;
    int inStack;
}t_tarjan_vertex;

typedef t_tarjan_vertex* t_tab_tarjan_vertex;

typedef struct {
    char* className;
    t_tab_tarjan_vertex tab;
}t_tarjan_class;

typedef t_tarjan_class* t_tab_tarjan_class;

#endif //INC_2526_TI301_PJT_TARJAN_VERTEXT_H