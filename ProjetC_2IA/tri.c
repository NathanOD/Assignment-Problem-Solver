//
//  tri.c
//  ProjetC_2IA
//
//  Created by Nathan Odic on 12/03/2023.
//

#include "tri.h"

// Fonction d'échange de deux éléments dans un tableau de familles
void swap_families(struct Family* a, struct Family* b) {
    struct Family temp = *a; // On créé une famille temporaire pour pouvoir échanger les deux familles
    *a = *b;
    *b = temp;
}

// Fonction qui partitionne le tableau de familles en utilisant le dernier élément comme pivot
int partition(struct Family tableau[], int debut, int fin) {
    int pivot = tableau[fin].choices[0];
    int i = debut - 1;
    for (int j = debut; j < fin; j++) {
        if (tableau[j].choices[0] <= pivot) {
            i++;
            swap_families(&tableau[i], &tableau[j]);
        }
    }
    swap_families(&tableau[i+1], &tableau[fin]);
    return i+1;
}

// Fonction récursive de tri rapide pour le tableau de familles
void quicksort(struct Family tableau[], int debut, int fin) {
    if (debut < fin) {
        int pivot = partition(tableau, debut, fin);
        quicksort(tableau, debut, pivot-1);
        quicksort(tableau, pivot+1, fin);
    }
}

void tribulle(float stats[][7], int ind[][7]) {
    float temp_stats;
    int temp_ind;
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6 - i; j++) {
                if (stats[k][j] <= stats[k][j+1]) {
                    // Échange de deux éléments dans le tableau de nombres
                    temp_stats = stats[k][j];
                    stats[k][j] = stats[k][j+1];
                    stats[k][j+1] = temp_stats;
                    // Échange de deux éléments dans le tableau d'indices
                    temp_ind = ind[k][j];
                    ind[k][j] = ind[k][j+1];
                    ind[k][j+1] = temp_ind;
                }
            }
        }
    }
}
