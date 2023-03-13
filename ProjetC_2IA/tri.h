//
//  tri.h
//  ProjetC_2IA
//
//  Created by Nathan Odic on 12/03/2023.
//

#ifndef tri_h
#define tri_h

#include <stdio.h>

#define MAX_CHOICES 5// Nombre maximum de choix par famille

// On créé un structure Family
struct Family {
    int id; // Identifiant de la famille
    int num_people; // Nombre de personnes dans la famille
    int choices[MAX_CHOICES]; // Liste des choix de la famille
    int assigned_choice; // Jour assigné à la famille
};

void swap_families(struct Family* a, struct Family* b);
int partition(struct Family tableau[], int debut, int fin);
void quicksort(struct Family tableau[], int debut, int fin);
void tribulle(float stats[][7], int ind[][7]);

#endif /* tri_h */
