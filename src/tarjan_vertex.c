#include "../include/tarjan_vertex.h"

t_tab_tarjan_vertex initTarjanVertexTab(liste_adjacence graphe) {
    t_tab_tarjan_vertex tarjanVertexTab = (t_tab_tarjan_vertex) malloc(sizeof(t_tarjan_vertex)*graphe.taille);
    for (int i =0; i<graphe.taille; i++) {
        //graphe.tab[i] ==t_list*
        t_tarjan_vertex newTarjanVertex;
        newTarjanVertex.id = i;
        newTarjanVertex.tempNum = -1;
        newTarjanVertex.accessibleNumber = -1;
        newTarjanVertex.inStack = 0;
        tarjanVertexTab[i] = newTarjanVertex;
    }
    return tarjanVertexTab;
}




// ------------------------ PARTIE 3 ------------------------ //

int min(int a, int b) {
    if (a <= b) {
        return a;
    }else {
        return b;
    }
}

void parcours(int sommetId, t_tab_tarjan_vertex* tabTarjanVertex, int* num, t_stack* stack, liste_adjacence graphe, t_tarjan_class_list tarjanClassList) {
    t_tarjan_vertex* tarjanVertex = tabTarjanVertex[sommetId];
    t_list* voisinVertex = graphe.tab[sommetId];

    tarjanVertex->tempNum = *num;
    tarjanVertex->accessibleNumber = *num;
    *num++;
    push(stack, tarjanVertex);
    tarjanVertex->inStack = 1;

    //On analyse et on regarde quel vertex appartient à la même classe (ils se trouvent dans la pile)
    t_cell* voisinActuel = voisinVertex->head;
    while (voisinActuel != NULL) {
        int sommetW = voisinActuel->pointArrive;
        if (tabTarjanVertex[sommetW]->tempNum == -1) {
            parcours(sommetW, tabTarjanVertex, num, stack, graphe, tarjanClassList);
            tarjanVertex->accessibleNumber = min(tarjanVertex->accessibleNumber, tabTarjanVertex[sommetW]->accessibleNumber);
        }else if (tabTarjanVertex[sommetW]->inStack == 1) {
            tarjanVertex->accessibleNumber = min(tarjanVertex->accessibleNumber, tabTarjanVertex[sommetW]->tempNum);
        }
        voisinActuel = voisinActuel->next;
    }

    if (tarjanVertex->accessibleNumber == tarjanVertex->tempNum) {
        //je crée une classe
        t_tarjan_class* newClasse;
        do {//Régler ça, il faut que v soit diff de w
            t_tarjan_cell* cellToPop = pop(stack);
            t_tarjan_vertex* tarjanVertexPop = cellToPop->tarjanVertex;
            tarjanVertexPop->inStack = 0;

            t_vertex_cell* newCell = (t_vertex_cell*) malloc(sizeof(t_vertex_cell));
            newCell->noeud = tarjanVertexPop;
            newCell->next = NULL;
            //Ajout du tarjan dans la classe (LCC)
            if (newClasse->tab.head == NULL) {
                newClasse->tab.head = newCell;
            }
            else {
                t_vertex_cell* curr = newClasse->tab.head;
                while (curr->next == NULL) {
                    curr = curr->next;
                }
                curr->next = newCell;
            }
        }while (tarjanVertexPop != )


        //Ajout de la classe dans le tab de classe (LCC)
        t_tarjan_class_cell* newClassCell;
        newClassCell->classe = newClasse;
        newClassCell->next = NULL;

        if (tarjanClassList.head == NULL) {
            tarjanClassList.head = newClassCell;
        }else {
            t_tarjan_class_cell* curr = tarjanClassList.head;
            while (curr->next != NULL) {
                curr = curr->next;
            }
            curr->next = newClassCell;
        }
    }



}