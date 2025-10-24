#include "list_adjacence.h"

liste_adjacence createEmptyTab(int taille) {
    liste_adjacence adj;
    adj.taille = taille;
    adj.tab = (t_list**)malloc(adj.taille * sizeof(t_list*));
    if (!adj.tab) {
        perror("Erreur d’allocation mémoire pour la liste d’adjacence");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < taille; i++)
        adj.tab[i] = createEmptyList();
    return adj;
}

void printTab(liste_adjacence tab) {
    if (tab.tab != NULL) {
        for (int i = 0; i < tab.taille; i++) {
            printf("Liste pour le sommet %d : ", i+1);
            printList(tab.tab[i]);
        }
    }
}