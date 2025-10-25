#include <stdio.h>

#include <unistd.h>
#include "include/list.h"
#include "include/list_adjacence.h"
#include "include/graphe.h"

int main() {

    liste_adjacence graphe = readGraph("../data/exemple1_from_chatGPT.txt");
    checkGraph(graphe);
    printTab(graphe);
    if (graphe.markovStatus == 1) {
        drawGraphe(graphe);
    }
    return 0;
}
