//
// Created by lauri on 24/10/2025.
//

#include "graphe.h"
#include "list_adjacence.h"

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
    while(fscanf(file,"%d %d %f",&depart,&arrivee,&proba) ==3) {
        t_cell *arete = createNewCell(int depart, float proba);
        arete -> next
    }
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
            printf("La somme des probabilités du sommet 3 est %f", sum);
            i = graphe.taille;
        }
    }
    printf("Le graphe est une chaine de Markov");
}

void drawGraphe(liste_adjacence graphe) {
    FILE *file = fopen("mermaid_file.txt", 'w');

}