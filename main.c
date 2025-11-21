#include <stdio.h>
#include <windows.h>

#include "include/list_adjacence.h"
#include "include/graphe.h"
#include "include/tarjan_vertex.h"
#include "include/matrix.h"

int main() {

    SetConsoleOutputCP(CP_UTF8);
    //Création Graphe
    liste_adjacence graphe = readGraph("../data/exemple_meteo.txt");
    checkGraph(graphe);
    printTab(graphe);
    if (graphe.markovStatus == 1) {
        drawGraphe(graphe);
    }

    printf("# ------------------------------- Partition & Classes -------------------------------# \n");
    //Partition et Classes
    t_tarjan_class_list* tarjanClassList =  tarjanFunction(graphe);

    printf("\n\nAffichage Partition\n");
    printPartition(*tarjanClassList);

    printf("\n");
    //Classes et lien
    t_tab_node_to_class* tabLinkNodeToClass = linkNodeToClass(*tarjanClassList, graphe);
    t_list_link* linkSummary = linkRecence(graphe, *tabLinkNodeToClass);
    printLinks(*linkSummary);

    caracGraphe(*linkSummary,*tarjanClassList);


    printf("# ------------------------------- Matrices de proba -------------------------------# \n");
    //Matrice de Proba

    //Création de matrice de proba
    t_matrix* matrice = createMatrixFromAdjList(graphe);
    printMatric(*matrice);

    //Calcul de matrice de proba au rang n
    t_matrix* result = multiplyMatricesBy(matrice, 7);
    printMatric(*result);


    //Vérifition epsilon <= 0.01
    int m = 1;
    int n = 2;
    t_matrix* result1 = multiplyMatricesBy(matrice, m);
    t_matrix* result2 = multiplyMatricesBy(matrice, n);

    while (diffMatrix(result1, result2) > 0.01) {
        n++;
        m++;
        result1 = multiplyMatricesBy(matrice, m);
        result2 = multiplyMatricesBy(matrice, n);

    }
    printf("%d %d", m, n);
    //printf("%f",  diffMatrix(result2, result3));

    return 0;
}
