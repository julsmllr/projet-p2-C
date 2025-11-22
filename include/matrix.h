#ifndef MATRIX_H
#define MATRIX_H

#include "../include/list_adjacence.h"
#include "../include/tarjan_vertex.h"

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


t_matrix subMatrix(const t_matrix *matrix, t_tarjan_class_list partition, int compo_index);

int getPeriod(const t_matrix *sub_matrix);

int gcd_int_array(const int *vals, int nbvals);

#endif
