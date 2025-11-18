//
// Created by zeoni on 11/17/2025.
//

// src/matrix.c
#include "../include/matrix.h"
#include <stdio.h>
#include <string.h>
#include <math.h>


t_matrix createEmptyMatrix(int n) {
    t_matrix m;
    m.size = n;
    m.mat = (float **) malloc(n * sizeof(float*));
    if (!m.mat) { perror("malloc"); exit(EXIT_FAILURE); }
    for (int i = 0; i < n; ++i) {
        m.mat[i] = (float *) calloc(n, sizeof(float));
        if (!m.mat[i]) { perror("calloc"); exit(EXIT_FAILURE); }
    }
    return m;
}

void freeMatrix(t_matrix *m) {
    if (!m || m->mat == NULL) return;
    for (int i = 0; i < m->size; ++i) {
        free(m->mat[i]);
        m->mat[i] = NULL;
    }
    free(m->mat);
    m->mat = NULL;
    m->size = 0;
}


t_matrix createMatrixFromAdjList(liste_adjacence graphe) {
    int n = graphe.taille;
    t_matrix M = createEmptyMatrix(n);
    for (int i = 0; i < n; ++i) {
        t_list *lst = graphe.tab[i];
        if (!lst) continue;
        t_cell *c = lst->head;
        while (c) {
            int j = c->pointArrive - 1;
            if (j >= 0 && j < n) {
                M.mat[i][j] = c->proba;
            }
            c = c->next;
        }
    }
    return M;
}

void copyMatrix(const t_matrix *src, t_matrix *dst) {
    if (!src) return;
    if (!dst) return;
    if (dst->mat == NULL || dst->size != src->size) {
        if (dst->mat != NULL) freeMatrix(dst);
        *dst = createEmptyMatrix(src->size);
    }
    int n = src->size;
    for (int i = 0; i < n; ++i) {
        memcpy(dst->mat[i], src->mat[i], n * sizeof(float));
    }
}


void multiplyMatrices(const t_matrix *A, const t_matrix *B, t_matrix *result) {
    int n = A->size;
    if (B->size != n) {
        fprintf(stderr, "multiplyMatrices: tailles incompatibles\n");
        exit(EXIT_FAILURE);
    }

    t_matrix temp = createEmptyMatrix(n);

    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            float a = A->mat[i][k];
            if (a == 0.0f) continue;
            for (int j = 0; j < n; ++j) {
                temp.mat[i][j] += a * B->mat[k][j];
            }
        }
    }
    copyMatrix(&temp, result);
    freeMatrix(&temp);
}


float diffMatrix(const t_matrix *A, const t_matrix *B) {
    if (!A || !B || A->size != B->size) {
        fprintf(stderr, "diffMatrix: tailles incompatibles\n");
        exit(EXIT_FAILURE);
    }
    int n = A->size;
    double sum = 0.0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            sum += fabs((double)A->mat[i][j] - (double)B->mat[i][j]);
    return (float) sum;
}


