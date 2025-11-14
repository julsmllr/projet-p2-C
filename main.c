#include <stdio.h>

#include <unistd.h>
#include "include/list.h"
#include "include/list_adjacence.h"
#include "include/graphe.h"
#include "include/tarjan_vertex.h"


int main() {

    liste_adjacence graphe = readGraph("../data/exemple_valid_step3.txt");
    checkGraph(graphe);
    printTab(graphe);
    if (graphe.markovStatus == 1) {
        drawGraphe(graphe);
    }

    t_tab_tarjan_vertex tabTarjanVertex = initTarjanVertexTab(graphe);
    return 0;
}
