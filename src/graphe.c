//
// Created by lauri on 24/10/2025.
//

#include "../include/graphe.h"
#include "../include/list_adjacence.h"
#include "../include/utils.h"




liste_adjacence readGraph(const char *filename) {
    FILE *file = fopen(filename,"rt");
    int nbvert, depart, arrivee;
    float proba;
    liste_adjacence adj;
    if (file==NULL){
        perror("Could not open file for reading");
        exit(EXIT_FAILURE);
    }
    if(fscanf(file,"%d",&nbvert)!=1){
        perror("Could not find number of vertices");
        exit(EXIT_FAILURE);
    }

    adj = createEmptyTab(nbvert);

    while(fscanf(file,"%d %d %f",&depart,&arrivee,&proba) == 3) {
        addCellToList(adj.tab[depart-1], arrivee, proba);
    }
    adj.markovStatus = 1;

    return adj;
}

float getProbaList(t_list* list) {
   float sum = 0;
   if (list->head != NULL) {
       t_cell* curr = list->head;

       while (curr != NULL) {
           sum += curr->proba;
           curr = curr->next;
       }
   }
   return sum;
}


void checkGraph(liste_adjacence graphe) {
    for (int i=0; i< graphe.taille; i++) {
        float sum = getProbaList(graphe.tab[i]);
        if (!(sum >= 0.99 && sum <= 1)) {
            printf("Le graphe n'est pas une chaine de Markov\n");
            printf("La somme des probabilités du sommet %d est %f\n", i+1, sum);
            graphe.markovStatus = 0;
            i = graphe.taille;
        }
    }
    if (graphe.markovStatus == 1) {
        printf("Le graphe est une chaine de Markov\n");
    }
}


void drawGraphe(liste_adjacence graphe){
    FILE *file = fopen("../mermaid_file.txt", "w");

    //Add Header
    fprintf(file, "---\nconfig:\nlayout: elk\ntheme: neo\nlook: neo\n---\n\nflowchart LR\n");

    for (int i = 1; i <= graphe.taille; i++) {
        fprintf(file, "%s((%d))\n", getID(i), i);
    }

    fprintf(file, "\n");

    for (int i = 0; i < graphe.taille; i++) {

        char *pointDepart = getID(i+1);

        t_list* currList = graphe.tab[i];
        t_cell* currCell = currList->head;
        while (currCell != NULL) {
            char *pointArrive = getID(currCell->pointArrive);
            fprintf(file, "%s -->|%.2f|%s\n", pointDepart , currCell->proba, pointArrive);
            currCell = currCell->next;
        }
    }

        fclose(file);

}

