#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_FAMILIES 500 // Maximum number of families
#define MAX_CAPACITY 250
#define MAX_CHOICES 5    // Maximum number of choices per family

struct Family {
    int id;
    int num_people;
    int choices[MAX_CHOICES];
    int assigned_choice;
};

int calculerCout(int choix, int nmb) {
    int cout = 0;
    switch (choix) {
        case 1:
            cout = 0;
            break;
        case 2:
            cout = 50;
            break;
        case 3:
            cout = 50 + 9 * nmb;
            break;
        case 4:
            cout = 100 + 9 * nmb;
            break;
        case 5:
            cout = 200 + 9 * nmb;
            break;
    }
    return cout;
}

double calculerPenalite(int *pop) {
    double penalite = 0.0;
    for (int i = 0; i < 7; i++) {
        double pen = 0.0;
        if (i < 6)
        {
            pen = ((pop[i]-125)/400.0)*pow(pop[i], abs(pop[i]-pop[i+1])/50.0);
        }
        else
        {
            pen = ((pop[i]-125)/400.0)*pow(pop[i], abs(pop[i]-pop[i])/50.0);
        }
        penalite += pen;
    }
    return penalite;
}

void assign_families(struct Family families[], int num_families, int capacity[]) {
    // Affecter les familles à leur choix préféré (jusqu'à ce que la capacité soit atteinte)
    for (int i = 0; i < num_families; i++) {
        int j;
        for (j = 0; j < MAX_CHOICES; j++) {
            int choice = families[i].choices[j];
            if (capacity[choice] >= families[i].num_people) {
                families[i].assigned_choice = choice;  // mettre à jour le choix de la famille
                capacity[choice] -= families[i].num_people;  // mettre à jour la capacité
                break;
            }
        }
        if (j == MAX_CHOICES) {
            families[i].assigned_choice = -1;  // marquer la famille comme "sacrifiée"
        }
    }
}

// Fonction qui échange deux éléments dans un tableau de familles
void swap_families(struct Family* a, struct Family* b) {
    struct Family temp = *a;
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

// Fonction qui trie un tableau de familles en utilisant l'algorithme de tri rapide
void quicksort(struct Family tableau[], int debut, int fin) {
    if (debut < fin) {
        int pivot = partition(tableau, debut, fin);
        quicksort(tableau, debut, pivot-1);
        quicksort(tableau, pivot+1, fin);
    }
}

int compute_cost(struct Family* families, int num_families) {
    int cost = 0;
    for (int i = 0; i < num_families; i++) {
        int num_people = families[i].num_people;
        int choice = families[i].assigned_choice;
        if (choice == 1) {
            cost += 50;
        } else if (choice == 2) {
            cost += 50 + 9 * num_people;
        } else if (choice == 3) {
            cost += 100 + 9 * num_people;
        } else if (choice == 4) {
            cost += 200 + 9 * num_people;
        }
    }
    return cost;
}

int main() {
    char filename[] = "pb50.csv";
    FILE *fp;
    char line[100];
    char *token;
    struct Family families[MAX_FAMILIES];
    int num_families = 0;
    int i, j;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }

    // Skip the first line (header)
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp) != NULL) {
        token = strtok(line, ";");
        families[num_families].num_people = atoi(token);

        for (i = 0; i < MAX_CHOICES; i++) {
            token = strtok(NULL, ";");
            if (token == NULL) {
                break;
            }
            families[num_families].choices[i] = atoi(token);
        }
        families[num_families].id = num_families+1;
        num_families++;
    }

    fclose(fp);

    //CODE
    
    // Trier le tableau de familles en utilisant le tri rapide
    quicksort(families, 0, num_families-1);
    
    int capacities[7] = {250, 250, 250, 250, 250, 250, 250};
    assign_families(families, num_families, capacities);

    for (int i = 0; i < num_families; i++) {
        if (families[i].assigned_choice == -1) {
            // Les familles sacrifiées sont ajoutées à leur second choix
            families[i].assigned_choice = families[i].choices[1];
        }
    }

    // Print
    for (i = 0; i < num_families; i++) {
        printf("Family %d: %d people, assigned at %d, choices: ", families[i].id, families[i].num_people, families[i].assigned_choice);
        for (j = 0; j < MAX_CHOICES; j++) {
            printf("%d ", families[i].choices[j]);
        }
        printf("\n");
    }

    int pers_jour[7];
    for (i = 0; i < num_families; i++) {
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
    printf("\n");
    printf("Nombre de personnes affectees le lundi : %d\n", pers_jour[0]);
    printf("Nombre de personnes affectees le mardi : %d\n", pers_jour[1]);
    printf("Nombre de personnes affectees le mercredi : %d\n", pers_jour[2]);
    printf("Nombre de personnes affectees le jeudi : %d\n", pers_jour[3]);
    printf("Nombre de personnes affectees le vendredi : %d\n", pers_jour[4]);
    printf("Nombre de personnes affectees le samedi : %d\n", pers_jour[5]);
    printf("Nombre de personnes affectees le dimanche : %d\n", pers_jour[6]);
    printf("\n");

    int cout_tot = 0;
    for (i = 0; i < num_families; i++) {
        int choix = 0;
        for (j = 0; j < MAX_CHOICES; j++) {
            if (families[i].choices[j] == families[i].assigned_choice)
            {
                choix = j;
            }
        }
        int cout = calculerCout(choix, families[i].num_people);
        cout_tot += cout;
    }
    printf("Cout : %d\n", cout_tot);

    double penalite = calculerPenalite(pers_jour);
    printf("Penalite : %f\n", penalite);

    printf("Fonction objectif : %f\n", cout_tot + penalite);

    return 0;
}
