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



// ------------------- LIENS ENTRE CLASSE ------------------- //


t_tab_node_to_class* linkNodeToClass(t_tarjan_class_list partition, liste_adjacence graphe) {
    int taille = graphe.taille;
    t_tab_node_to_class* newTabNodeToClass = (t_tab_node_to_class*) malloc(sizeof(t_tarjan_class**)*taille);
    if (partition.head != NULL) {
        t_tarjan_class_cell* curr = partition.head;
        while (curr != NULL) {
            t_tarjan_class* classe = curr->classe;
            t_vertex_cell* vertexInClass = classe->list->head;
            while (vertexInClass != NULL) {
                int nodeId = vertexInClass->noeud->id;
                *newTabNodeToClass[nodeId-1] = classe;
                vertexInClass = vertexInClass->next;
            }
            curr = curr->next;
        }
    }
    return newTabNodeToClass;
}

t_list_link* createNewListLink() {
    t_list_link* newlistLink = (t_list_link*) malloc(sizeof(t_list_link));
    newlistLink->head = NULL;
    return newlistLink;
}


int isLink(t_list_link listLink, t_tarjan_class* depart, t_tarjan_class* arrivee) {
    if (listLink.head != NULL){
        t_cell_link* curr = listLink.head;
        while (curr != NULL) {
            if (curr->link->classeDepart == depart && curr->link->classeArrivee == arrivee) {
                return 1;
            }
            curr = curr->next;
        }
    }
    return 0;
}


t_link* createNewLink(t_tarjan_class* classCI,t_tarjan_class* classCJ) {
    t_link* newLink = (t_link*) malloc(sizeof(t_link));
    newLink->classeDepart = classCI;
    newLink->classeArrivee = classCJ;
    return newLink;
}

t_cell_link* newLinkCell(t_link* link) {
    t_cell_link* newCell = (t_cell_link*) malloc(sizeof(t_cell_link));
    newCell->link = link;
    return newCell;
}

void insertNewLink(t_list_link* listLink, t_link* newLink) {
    t_cell_link* newCell = newLinkCell(newLink);
    if (listLink->head != NULL){
        listLink->head = newCell;
    }else {
        t_cell_link* curr = listLink->head;
        while (curr->next != NULL) {
            curr = curr->next;
        }

        curr->next = newCell;
    }
}

t_list_link* linkRecence(liste_adjacence graphe, t_tab_node_to_class tabNodeToClass) {
    t_list_link* newlistLink = createNewListLink();
    for (int i = 0; i < graphe.taille; i++) {
        t_tarjan_class* classCI = tabNodeToClass[i];

        t_cell* curr = graphe.tab[i]->head;
        while (curr != NULL) {
            t_tarjan_class* classCJ = tabNodeToClass[curr->pointArrive - 1];
            if (!isLink(*newlistLink, classCI, classCJ)) {
                t_link* newLink = createNewLink(classCI, classCJ);
                insertNewLink(newlistLink, newLink);
            }
        }
    }
};


void printLinks(t_list_link linkSummary) {
    if (linkSummary.head != NULL) {
        t_cell_link* curr = linkSummary.head;
        while (curr != NULL) {
            printf("C%d -> C%d \n", curr->link->classeDepart->className, curr->link->classeArrivee->className);
            curr = curr->next;
        }
    }
}