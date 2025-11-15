#include "../include/tarjan_vertex.h"


t_tab_tarjan_vertex initTarjanVertexTab(liste_adjacence graphe) {
    t_tab_tarjan_vertex tarjanVertexTab = (t_tab_tarjan_vertex) malloc(sizeof(t_tarjan_vertex*)*graphe.taille);
    for (int i =0; i<graphe.taille; i++) {
        //graphe.tab[i] ==t_list*
        t_tarjan_vertex* newTarjanVertex = (t_tarjan_vertex*) malloc(sizeof(t_tarjan_vertex));
        newTarjanVertex->id = i+1;
        newTarjanVertex->tempNum = -1;
        newTarjanVertex->accessibleNumber = -1;
        newTarjanVertex->inStack = 0;
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

// ---------------------------- Création avec malloc (listes chaînées) ---------------------------- //

t_vertex_cell* createVertexCell(t_tarjan_vertex *tarjanVertexPop) {
    t_vertex_cell* newCell = (t_vertex_cell*) malloc(sizeof(t_vertex_cell));
    newCell->noeud = tarjanVertexPop;
    newCell->next = NULL;
    return newCell;
}


t_vertex_list* createNewVertexList() {
    t_vertex_list* newVertexList = (t_vertex_list*) malloc(sizeof(t_vertex_list));
    newVertexList->head = NULL;
    return newVertexList;
}

t_tarjan_class* createNewClass(int name) {
    t_tarjan_class* newClass = (t_tarjan_class*) malloc(sizeof(t_tarjan_class));
    newClass->className = name;
    newClass->list = createNewVertexList();
    return newClass;
}


void parcours(int sommetId, t_tab_tarjan_vertex tabTarjanVertex, int* num, t_stack* stack, liste_adjacence graphe, t_tarjan_class_list* tarjanClassList) {
    t_tarjan_vertex* tarjanVertex = tabTarjanVertex[sommetId]; //Avoir le noeud en Tarjan
    t_list* voisinVertex = graphe.tab[sommetId]; //Avoir les voisins de ce noeud

    tarjanVertex->tempNum = *num;
    tarjanVertex->accessibleNumber = *num;
    *num = *num + 1;
    push(stack, tarjanVertex);
    tarjanVertex->inStack = 1;

    //Je regard tous les voisins, s'ils ne sont pas associées à une classe ou dans la pile je lance la fonction dessus sinon j'attribue à la même classe
    t_cell* voisinActuel = voisinVertex->head;
    while (voisinActuel != NULL) {
        int sommetW = voisinActuel->pointArrive - 1;
        if (tabTarjanVertex[sommetW]->tempNum == -1) {
            parcours(sommetW, tabTarjanVertex, num, stack, graphe, tarjanClassList);
            tarjanVertex->accessibleNumber = min(tarjanVertex->accessibleNumber, tabTarjanVertex[sommetW]->accessibleNumber);
        }else if (tabTarjanVertex[sommetW]->inStack == 1) {
            tarjanVertex->accessibleNumber = min(tarjanVertex->accessibleNumber, tabTarjanVertex[sommetW]->tempNum);
        }
        voisinActuel = voisinActuel->next;
    }

    //Si on est à la racine de la classe
    if (tarjanVertex->accessibleNumber == tarjanVertex->tempNum) {
        //je crée une classe
        t_tarjan_class* newClasse = createNewClass(0);
        t_tarjan_cell* cellToPop;
        t_tarjan_vertex* tarjanVertexPop;
        //On récupère un par un tous les noeuds faisant partie d'une même classe
        do {
            cellToPop = pop(stack);
            tarjanVertexPop = cellToPop->tarjanVertex;
            tarjanVertexPop->inStack = 0;

            t_vertex_cell* newCell = createVertexCell(tarjanVertexPop);
            //Ajout du tarjan dans la classe (LCC)
            if (newClasse->list->head == NULL) {
                newClasse->list->head = newCell;
            }
            else {
                t_vertex_cell* curr = newClasse->list->head;
                while (curr->next != NULL) {
                    curr = curr->next;
                }
                curr->next = newCell;
            }
        }while (tarjanVertexPop != tarjanVertex);


        //Ajout de la classe dans le tab de classe (LCC)
        t_tarjan_class_cell* newClassCell = (t_tarjan_class_cell*) malloc(sizeof(t_tarjan_class_cell));
        newClassCell->classe = newClasse;
        newClassCell->next = NULL;

        if (tarjanClassList->head == NULL) {
            tarjanClassList->head = newClassCell;
        }else {
            t_tarjan_class_cell* curr = tarjanClassList->head;
            while (curr->next != NULL) {
                curr = curr->next;
            }
            curr->next = newClassCell;
        }
    }

}


t_tarjan_class_list* initTarjanClassList() {
    t_tarjan_class_list* tarjanClassList = (t_tarjan_class_list*) malloc(sizeof(t_tarjan_class_list));
    tarjanClassList->head = NULL;
    return tarjanClassList;
}


t_tarjan_class_list* tarjanFunction(liste_adjacence graphe) {
    int num = 0;
    t_stack stack;
    t_tarjan_class_list* tarjanClassList = initTarjanClassList();
    t_tab_tarjan_vertex tarjanVertexTab = initTarjanVertexTab(graphe);

    for (int i = 0; i < graphe.taille; i++) {
        if (tarjanVertexTab[i]->tempNum == -1) {
            parcours(i, tarjanVertexTab, &num, &stack, graphe, tarjanClassList);
        }
    }

    //Renommage des classes
    t_tarjan_class_cell* curr = tarjanClassList->head;
    int numClass = 1;
    while (curr != NULL) {
        curr->classe->className = numClass;
        curr = curr->next;
        numClass++;
    }

    return tarjanClassList;
}


// ------------------------ AFFICHAGE ------------------------ //

void printClass(t_tarjan_class class) {
    printf("Classe C%d : { ", class.className);
    t_vertex_cell* curr = class.list->head;
    while (curr != NULL) {
        printf("%d ", curr->noeud->id);
        curr = curr->next;
    }
    printf("}\n");
}

void printPartition(t_tarjan_class_list partition) {
    if (partition.head != NULL) {
        t_tarjan_class_cell* curr = partition.head;
        while (curr != NULL) {
            printClass(*curr->classe);
            curr = curr->next;
        }
    }
}