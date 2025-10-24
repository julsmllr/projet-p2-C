#include <stdio.h>

#include <unistd.h>
#include "list.h"
#include "list_adjacence.h"
#include "graphe.h"

int main() {

    liste_adjacence adj = createEmptyTab(4);

    // Exemple du graphe donné dans le sujet
    addCellToList(adj.tab[0], 3, 0.01);
    addCellToList(adj.tab[0], 2, 0.04);
    addCellToList(adj.tab[0], 1, 0.95);

    addCellToList(adj.tab[1], 4, 0.05);
    addCellToList(adj.tab[1], 3, 0.05);
    addCellToList(adj.tab[1], 2, 0.90);

    addCellToList(adj.tab[2], 4, 0.20);
    addCellToList(adj.tab[2], 3, 0.80);

    addCellToList(adj.tab[3], 1, 1.00);

    printTab(adj);

    drawGraphe(adj);
    return 0;
}
