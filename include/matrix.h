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

t_matrix createEmptyMatrix(int n);
void freeMatrix(t_matrix *m);

t_matrix createMatrixFromAdjList(liste_adjacence graphe);

void copyMatrix(const t_matrix *src, t_matrix *dst);
void multiplyMatrices(const t_matrix *A, const t_matrix *B, t_matrix *result);
float diffMatrix(const t_matrix *A, const t_matrix *B);



#endif // MATRIX_H






