//
//  assign.c
//  ProjetC_2IA
//
//  Created by Nathan Odic on 12/03/2023.
//

#include "assign.h"

void assign_families(struct Family families[], int num_families, int capacity[]) {
    // On affecte les familles à leur choix préféré jusqu'à
    // ce que la capacité maximale du jour soit atteinte
    
    // On parcourt chaque famille
    for (int i = 0; i < num_families; i++) {
        // On parcourt chaque choix de la famille
        int j;
        for (j = 0; j < MAX_CHOICES; j++) {
            int choice = families[i].choices[j];
            if (capacity[choice] >= families[i].num_people) {
                families[i].assigned_choice = choice;  // On affecte la famille
                capacity[choice] -= families[i].num_people;  // On retire les place prises par la famille
                break;
            }
        }
        // Si on a pas réussi à affecter la famille, on la marque
        // comme "sacrifiée" et on l'affectera plus tard
        if (j == MAX_CHOICES) {
            families[i].assigned_choice = -1;
        }
    }
}

// Fonction d'assignation des familles sacrifiées
void assign_sac_families(struct Family families[], int num_families) {
    // On affecte les familles sacrifiées à leur 2nd choix
    for (int i = 0; i < num_families; i++) {
        if (families[i].assigned_choice == -1) {
            families[i].assigned_choice = families[i].choices[1];
        }
    }
    
}
// Fonction d'assignation et d'affichage des familles supplémentaires
void assign_other_families(struct Family families[], int ind[][7], int exp) {
    printf("Experience %d:\n", exp+1);
    for (int i = 0; i < MAX_NEW_FAMILIES; i++) {
        // Chaque famille est assignée à son dernier
        // choix afin de maximiser les indemnités
        families[i].assigned_choice = ind[exp][6];
        for (int j = 0; j < MAX_CHOICES; j++) {
            // Les choix de la famille sont donc les 5 jours
            // les moins remplis, classés par odre décroissant
            families[i].choices[j] = ind[exp][j+2];
        }
    }
    // Affichage des résultats
    for (int i = 0; i < MAX_NEW_FAMILIES; i++) {
        printf("Famille %d: %d personnes, assignees a %d, choix: ", families[i].id, families[i].num_people, families[i].assigned_choice);
        for (int j = 0; j < MAX_CHOICES; j++) {
            printf("%d ", families[i].choices[j]);
        }
        printf("\n");
    }
}
