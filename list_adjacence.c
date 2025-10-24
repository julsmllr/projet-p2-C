//
// Created by jules on 24/10/2025.
//

#include "list_adjacence.h"

liste_adjacence creerListeAdjacenceVide(int taille) {
    liste_adjacence adj;
    adj.taille = taille;
    adj.tab = (liste )malloc(taille sizeof(liste));
    if (!adj.tab) {
        perror("Erreur d’allocation mémoire pour la liste d’adjacence");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < taille; i++)
        adj.tab[i] = creerListeVide();
    return adj;
}