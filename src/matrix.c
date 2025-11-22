// src/matrix.c
#include "../include/matrix.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/* ===== Création / destruction ===== */

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


t_matrix subMatrix(const t_matrix *matrix, t_tarjan_class_list partition, int compo_index) {
    int idx = 1;
    t_tarjan_class_cell *cur = partition.head;
    while (cur && idx < compo_index) { cur = cur->next; idx++; }
    if (!cur) {
        fprintf(stderr, "subMatrix: composante %d non trouvée\n", compo_index);
        exit(EXIT_FAILURE);
    }
    t_tarjan_class *classe = cur->classe;

    int size = 0;
    t_vertex_cell *vcur = classe->list->head;
    while (vcur) { size++; vcur = vcur->next; }

    if (size == 0) {
        t_matrix empty = createEmptyMatrix(0);
        return empty;
    }

    int *nodes = (int *) malloc(size * sizeof(int));
    int p = 0;
    vcur = classe->list->head;
    while (vcur) {
        nodes[p++] = vcur->noeud->id; // ID 1-based
        vcur = vcur->next;
    }

    t_matrix sub = createEmptyMatrix(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int row = nodes[i] - 1;
            int col = nodes[j] - 1;
            if (row >= 0 && row < matrix->size && col >= 0 && col < matrix->size) {
                sub.mat[i][j] = matrix->mat[row][col];
            } else {
                sub.mat[i][j] = 0.0f;
            }
        }
    }

    free(nodes);
    return sub;
}

int gcd_int_array(const int *vals, int nbvals) {
    if (nbvals == 0) return 0;
    int result = vals[0];
    for (int k = 1; k < nbvals; ++k) {
        int a = result;
        int b = vals[k];
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        result = a;
    }
    return result;
}


int getPeriod(const t_matrix *sub_matrix) {
    int n = sub_matrix->size;
    if (n == 0) return 0;
    int *periods = (int *) malloc(n * sizeof(int));
    int period_count = 0;
    int cpt = 1;

    t_matrix power_matrix = createEmptyMatrix(n);
    t_matrix result_matrix = createEmptyMatrix(n);
    copyMatrix(sub_matrix, &power_matrix);

    for (cpt = 1; cpt <= n; ++cpt) {
        int diag_nonzero = 0;
        for (int i = 0; i < n; ++i) {
            if (power_matrix.mat[i][i] > 0.0f) {
                diag_nonzero = 1;
                break;
            }
        }
        if (diag_nonzero) {
            periods[period_count++] = cpt;
        }
        multiplyMatrices(&power_matrix, sub_matrix, &result_matrix);
        copyMatrix(&result_matrix, &power_matrix);
    }

    int result = gcd_int_array(periods, period_count);
    free(periods);
    freeMatrix(&power_matrix);
    freeMatrix(&result_matrix);
    return result;
}
