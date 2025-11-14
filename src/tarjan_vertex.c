#include "../include/tarjan_vertex.h"
#include "../include/list_adjacence.h"

t_tab_tarjan_vertex initTarjanVertexTab(liste_adjacence graphe) {
    t_tab_tarjan_vertex tarjanVertexTab = (t_tab_tarjan_vertex) malloc(sizeof(t_tarjan_vertex)*graphe.taille);
    for (int i =0; i<graphe.taille; i++) {
        //graphe.tab[i] ==t_list*
        t_tarjan_vertex newTarjanVertex;
        newTarjanVertex.id = i;
    }

    return tarjanVertexTab;
}