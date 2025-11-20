#include <stdio.h>
#include <windows.h>

#include "include/list_adjacence.h"
#include "include/graphe.h"
#include "include/tarjan_vertex.h"


int main() {

    SetConsoleOutputCP(CP_UTF8);

    liste_adjacence graphe = readGraph("../data/exemple_valid_step3.txt");
    checkGraph(graphe);
    printTab(graphe);
    if (graphe.markovStatus == 1) {
        drawGraphe(graphe);
    }


    //Partition
    t_tarjan_class_list* tarjanClassList =  tarjanFunction(graphe);

    printf("\n\nAffichage Partition\n");
    printPartition(*tarjanClassList);

    printf("\n");
    t_tab_node_to_class* tabLinkNodeToClass = linkNodeToClass(*tarjanClassList, graphe);
    t_list_link* linkSummary = linkRecence(graphe, *tabLinkNodeToClass);
    printLinks(*linkSummary);

    caracGraphe(*linkSummary,*tarjanClassList);
    return 0;
}
