#include <stdio.h>
#include <windows.h>

#include "include/list_adjacence.h"
#include "include/graphe.h"
#include "include/tarjan_vertex.h"
#include "include/matrix.h"

int main() {

    SetConsoleOutputCP(CP_UTF8);
    //Variables pour Graphe
    liste_adjacence graphe = readGraph("../data/exemple_scc1.txt");
    t_tarjan_class_list* tarjanClassList =  tarjanFunction(graphe);
    t_tab_node_to_class* tabLinkNodeToClass = linkNodeToClass(*tarjanClassList, graphe);
    t_list_link* linkSummary = linkRecence(graphe, *tabLinkNodeToClass);
    t_matrix* matrice = createMatrixFromAdjList(graphe);
    t_matrix* result = multiplyMatricesBy(matrice, 7);

    int inputUser = 0;
    while (inputUser != 4) {
        printf("# ------------------ MENU ------------------ #\n\n");
        printf("1. Informations Graphe\n");
        printf("2. Partitions et Classes");
        printf("3. Matrices et probabilités");
        printf("4. Quitter");
        do {
            printf("Votre choix (1-4): ");
            scanf("%d", &inputUser);
        }while (inputUser >= 1 && inputUser <= 4);

        switch (inputUser) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;

        }
    }
    checkGraph(graphe);
    printTab(graphe);
    if (graphe.markovStatus == 1) {
        drawGraphe(graphe);
    }




    printf("# ------------------------------- Partition & Classes -------------------------------# \n");
    //Partition et Classes

    printf("\n\nAffichage Partition\n");
    printPartition(*tarjanClassList);

    printf("\n");
    //Classes et lien
    printLinks(*linkSummary);

    caracGraphe(*linkSummary,*tarjanClassList);

    drawClassesGraphe(*linkSummary, *tarjanClassList);
    printf("# ------------------------------- Matrices de proba -------------------------------# \n");
    //Matrice de Proba

    //Création de matrice de proba
    printMatric(*matrice);

    //Calcul de matrice de proba au rang n
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
    printf("%d %d - Epsilon : %f", m, n, diffMatrix(result1, result2));


    //SubMatrix for class
    t_matrix* matClass1 = subMatrix(matrice, *tarjanClassList, 0);
    printMatric(*matClass1);
    return 0;
}
