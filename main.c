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


    //Parition Partition
    t_tarjan_class_list* tarjanClassList =  tarjanFunction(graphe);

    printf("\n\nAffichage Partition\n");
    printPartition(*tarjanClassList);

    printf("\n");
    t_tab_node_to_class* tabLinkNodeToClass = linkNodeToClass(*tarjanClassList, graphe);
    t_list_link* linkSummary = linkRecence(graphe, *tabLinkNodeToClass);
    printLinks(*linkSummary);
    return 0;
}
