//
// Created by zeoni on 11/17/2025.
//


#ifndef MATRIX_H
#define MATRIX_H
#include "../include/list_adjacence.h"   // pour liste_adjacence
#include "../include/tarjan_vertex.h"    // pour t_tarjan_class_list, t_tarjan_class



typedef struct {
    int size;
    float **mat;
} t_matrix;


t_matrix* createEmptyMatrix(int n);
void freeMatrix(t_matrix *m);

t_matrix* createMatrixFromAdjList(liste_adjacence graphe);
void printMatric(t_matrix matrice);


void copyMatrix(const t_matrix *src, t_matrix *dst);
t_matrix* multiplyMatrices(t_matrix *A, t_matrix *B);
float diffMatrix(t_matrix *A, t_matrix *B);
t_matrix* multiplyMatricesBy(t_matrix *matrice, int times);

t_matrix* subMatrix(t_matrix *matrix, t_tarjan_class_list partition, int compo_index);
int gcd_int_array(const int *vals, int nbvals);
int getPeriod(const t_matrix sub_matrix);

#endif // MATRIX_H






