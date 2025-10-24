#ifndef GRAPHE_H
#define GRAPHE_H

#include "list_adjacence.h"
#include "list.h"


liste_adjacence readGraph(const char *filename);

void checkGraph(liste_adjacence graphe);

void drawGraphe(liste_adjacence graphe);

#endif //GRAPHE_H
