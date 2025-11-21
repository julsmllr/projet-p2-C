#include <windows.h>
#include "include/list_adjacence.h"
#include "include/graphe.h"
#include "include/tarjan_vertex.h"
#include "include/matrix.h"

void graphInformation(liste_adjacence graphe) {
    int userInput = 0;
    while (userInput != 3) {
        printf("# ------------------ INFORMATIONS GRAPHE ------------------ #\n\n");
        printf("1. Afficher la liste d'adjacence\n");
        printf("2. Créer le fichier Mermaid\n");
        printf("3. Revenir au menu principal\n");
        do {
            printf("Votre choix (1-3): ");
            scanf("%d", &userInput);
        }while (!(userInput >= 1 && userInput <= 3));

        switch (userInput) {
            case 1:
                checkGraph(graphe);
                printTab(graphe);
                break;
            case 2:
                if (graphe.markovStatus == 1) {
                    drawGraphe(graphe);
                }else {
                    printf("Le graphe n'est pas une chaîne de Markov\n");
                }
                break;
        }

        printf("\n\n");
    }
}

void partitionAndClass(t_tarjan_class_list* tabClass, t_list_link* tabLink) {
    int userInput = 0;
    while (userInput != 5) {
        printf("# ------------------ PARITIONS ET CLASSES ------------------ #\n\n");
        printf("1. Afficher les classes\n");
        printf("2. Afficher les relations entre les classes\n");
        printf("3. Afficher les caractéristiques du graphe\n");
        printf("4. Créer le fichier mermaid des classes\n");
        printf("5. Revenir au menu principal\n");
        do {
            printf("Votre choix (1-5): ");
            scanf("%d", &userInput);
        }while (!(userInput >= 1 && userInput <= 5));

        switch (userInput) {
            case 1:
                printf("\nAffichage Partition\n");
                printPartition(*tabClass);
                break;
            case 2:
                printLinks(*tabLink);
                break;
            case 3:
                caracGraphe(*tabLink,*tabClass);
                break;
            case 4:
                drawClassesGraphe(*tabLink, *tabClass);
                break;

        }

        printf("\n\n");
    }
}

void matrixandProba(t_matrix* matrice, t_tarjan_class_list* tarjanClassList) {
    int userInput = 0;
    while (userInput != 5) {
        printf("# ------------------ MATRICES ET PROBABILITES ------------------ #\n\n");
        printf("1. Afficher la matrice de probabilité\n");
        printf("2. Afficher la matrice au rang n\n");
        printf("3. Rang où epsilon < 0.01\n");
        printf("4. Afficher la matrice de classe\n");
        printf("5. Revenir au menu principal\n");

        do {
            printf("Votre choix (1-5): ");
            scanf("%d", &userInput);
        }while (!(userInput >= 1 && userInput <= 5));

        switch (userInput) {
            case 1:
                printMatric(*matrice);
                break;
            case 2:
                int rang;
                printf("Rang :");
                scanf("%d", &rang);
                t_matrix* result = multiplyMatricesBy(matrice, rang);
                printMatric(*result);
                break;
            case 3:

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
                break;
            case 4:
                printf("Rappel des classes :\n");
                printPartition(*tarjanClassList);
                printf("\nQuelle classe voulez-vous analyser ?");
                int input;
                scanf("%d", &input);
                t_matrix* matClass1 = subMatrix(matrice, *tarjanClassList, input);
                printMatric(*matClass1);
                break;

        }

        printf("\n\n");
    }
}

int main() {

    SetConsoleOutputCP(CP_UTF8);
    //Variables pour Graphe
    liste_adjacence graphe = readGraph("../data/exemple_scc1.txt");
    t_tarjan_class_list* tarjanClassList =  tarjanFunction(graphe);
    t_tab_node_to_class* tabLinkNodeToClass = linkNodeToClass(*tarjanClassList, graphe);
    t_list_link* linkSummary = linkRecence(graphe, *tabLinkNodeToClass);
    t_matrix* matrice = createMatrixFromAdjList(graphe);

    int inputUser = 0;
    while (inputUser != 4) {
        printf("# ------------------ MENU ------------------ #\n\n");
        printf("1. Informations Graphe\n");
        printf("2. Partitions et Classes\n");
        printf("3. Matrices et probabilités\n");
        printf("4. Quitter\n");
        do {
            printf("Votre choix (1-4): ");
            scanf("%d", &inputUser);
        }while (!(inputUser >= 1 && inputUser <= 4));

        switch (inputUser) {
            case 1:
                graphInformation(graphe);
                break;
            case 2:
                partitionAndClass(tarjanClassList, linkSummary);
                break;
            case 3:
                matrixandProba(matrice, tarjanClassList);
                break;

        }
    }
    return 0;
}
