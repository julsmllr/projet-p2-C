//
// Created by lauri on 24/10/2025.
//

#include "graphe.h"
#include "list_adjacence.h"

liste_adjacence readGraph(const char *filename{
    FILE *file = fopen(filename,"rt");
    int nbvert, depart, arrivee;
    float proba;
    liste_adjacence adj;
    if (file==NULL){
      perror("Could not open file for reading");
      exit(EXIT_FAILURE);
     }
     if(scanf(file,"%d",&nbvert)!=1){
       perror("Could not find number of vertices");
       exit(EXIT_FAILURE);
     }
