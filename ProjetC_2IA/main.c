//
//  main.c
//  ProjetC_2IA
//
//  Created by Nathan Odic on 12/03/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// On ajoute les fontions définies dans les autres fichiers
#include "tri.h"
#include "assign.h"
#include "calcul.h"

#define MAX_FAMILIES 500     // Nombre maximum de familles dans le CSV
#define MAX_NEW_FAMILIES 3   // Nombre maximum de familles ajoutées dans la partie 2
#define MAX_CHOICES 5        // Nombre maximum de choix par famille


int main() {
    
    /*
        CHARGEMENT FICHIER CSV
        (NE PAS OUBLIER DE CHANGER L'ARBORESCENCE)
    */
    
    char filename[] = "/Users/nathanodic/Dev/C/ProjetC_2IA/ProjetC_2IA/pb10.csv";
    FILE *fp;
    char line[100];
    char *token;
    // Initialisation de la structure Family
    struct Family families[MAX_FAMILIES];
    // Initialisation de la variable de comptage du nombre de familles
    int num_families = 0;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Erreur: Impossible d'ouvrir le fichier %s\n", filename);
        exit(1);
    }
    // Chargement des données du CSV dans la structure Family
    fgets(line, sizeof(line), fp); // On ne tient pas compte de la première ligne du tableau
    while (fgets(line, sizeof(line), fp) != NULL) {
        token = strtok(line, ";"); // On separe les colonnes avec le séparateur ';'
        families[num_families].num_people = atoi(token);

        for (int i = 0; i < MAX_CHOICES; i++) {
            token = strtok(NULL, ";"); 
            if (token == NULL) {
                break;
            }
            families[num_families].choices[i] = atoi(token);
        }
        families[num_families].id = num_families+1;
        num_families++;
    }
    // On ferme le fichier CSV
    fclose(fp);


    /*
        CODE PARTIE 1
    */
    
    // Trier le tableau de familles en utilisant le tri rapide
    quicksort(families, 0, num_families-1);
    
    // Assignation des familles
    int capacities[7] = {250, 250, 250, 250, 250, 250, 250};
    assign_families(families, num_families, capacities);
    assign_sac_families(families, num_families);

    // Affichage des informations sur les familles
    printf("Partie 1 :\n");
    for (int i = 0; i < num_families; i++) {
        printf("Famille %d: %d personnes, assignees a %d, choix: ", families[i].id, families[i].num_people, families[i].assigned_choice);
        for (int j = 0; j < MAX_CHOICES; j++) {
            printf("%d ", families[i].choices[j]);
        }
        printf("\n");
    }

    // Calcul et affichage du nombre de personnes par jour
    int pers_jour[7] = {0};
    for (int i = 0; i < num_families; i++) {
        switch (families[i].assigned_choice) {
        case 0:
            pers_jour[0] += families[i].num_people;
            break;
        case 1:
            pers_jour[1] += families[i].num_people;
            break;
        case 2:
            pers_jour[2] += families[i].num_people;
            break;
        case 3:
            pers_jour[3] += families[i].num_people;
            break;
        case 4:
            pers_jour[4] += families[i].num_people;
            break;
        case 5:
            pers_jour[5] += families[i].num_people;
            break;
        case 6:
            pers_jour[6] += families[i].num_people;
            break;
        }
    }
    
    printf("\nNombre de personnes affectees par jour : ");
    for (int i = 0; i < 7; i++) {
        printf("%d ", pers_jour[i]);
    }
    printf("\n");
    
    // Calcul et affichage de la fonction objectif
    int cout_tot = 0;
    for (int i = 0; i < num_families; i++) {
        int choix = 0;
        for (int j = 0; j < MAX_CHOICES; j++) {
            if (families[i].choices[j] == families[i].assigned_choice)
            {
                choix = j;
            }
        }
        int cout = calculerCout(choix, families[i].num_people);
        cout_tot += cout;
    }
    double penalite = calculerPenalite(pers_jour);
    printf("Cout : %d\n", cout_tot);
    printf("Penalite : %f\n", penalite);
    printf("Fonction objectif : %f\n", cout_tot + penalite);
    printf("\n");
    
    
    
    /*
        CODE PARTIE 2
    */
    
    // On génère le tableau des évènements
    float stat[3][7] = {
            {14.15, 14.24, 14.81, 14.02, 13.32, 15.30, 14.15},
            {14.16, 14.16, 14.26, 14.75, 14.48, 14.37, 13.83},
            {14.47, 12.74, 13.66, 14.53, 14.74, 14.91, 14.96}
    };
    // On génère le tableau des indices
    int indices[3][7] = {0};
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < 7; i++) {
            indices[k][i] = i;
        }
    }
    
    // On génère les 3 familles aléatoirement
    struct Family new_families[MAX_NEW_FAMILIES];
    uint32_t seed = (uint32_t) time(NULL);
    // Initialisation du générateur de nombres aléatoires
    srand(seed);
    // On créé les 9 nouvelles familles
    for (int i = 0; i < MAX_NEW_FAMILIES; i++) {
        int num_people = rand() % 5 + 3;
        new_families[i].id = i+1;
        new_families[i].num_people = num_people;
        new_families[i].assigned_choice = 0;
        for (int j = 0; j < MAX_CHOICES; j++) {
            new_families[i].choices[j] = 0;
        }
    }
    
    // On utilise le tri à bulles pour trier les listes
    // de stats et d'indices dans l'ordre décroissant
    tribulle(stat, indices);
    
    // On affiche les résultats et on calcule le coût
    printf("Partie 2 :\n\n");
    for (int exp = 0; exp < 3; exp++) {
        assign_other_families(new_families, indices, exp);
        int cout_tot = 0;
        for (int i = 0; i < MAX_NEW_FAMILIES; i++) {
            // Le coût est toujours celui du 5ème choix
            // car on veut la maximum d'indemnités
            cout_tot += 200 + 9 * new_families[i].num_people;
        }
        printf("Cout : %d", cout_tot);
        printf("\n\n");
    }
    
    return 0;
}
