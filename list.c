//
// Created by jules on 24/10/2025.
//

#include "list.h"

t_list* createEmptyList() {
    t_list* newList = (t_list*) malloc(sizeof(t_list));
    newList->head = NULL;
    return newList;
}

void addCellToList(t_list* list, int pointArrive, float proba) {
    if (list != NULL ) {
        t_cell* newCell = createNewCell(pointArrive, proba);
        if (list->head == NULL) {
            list->head = newCell;
        }else {
            t_cell* curr = list->head;
            while (curr->next != NULL) {
                curr = curr->next;
            }
            curr->next =newCell;
        }
    }
}

void printList(t_list* list) {
    if (list != NULL && list->head != NULL) {
        printf("[@head] -> ");
        t_cell* curr = list->head;
        while (curr->next != NULL) {
            printf("(%d, %f) @-> ", curr->pointArrive, curr->proba);
            curr = curr->next;
        }
        printf("(%d, %f)\n", curr->pointArrive, curr->proba);

    }
}