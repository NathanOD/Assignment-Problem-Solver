#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FAMILIES 500 // Maximum number of families
#define MAX_CAPACITY 250
#define MAX_CHOICES 5    // Maximum number of choices per family

struct Family {
    int id;
    int num_people;
    int choices[MAX_CHOICES];
    int assigned_choice;
};

// Fonction qui affecte une famille à un choix donné si la capacité maximale n'est pas atteinte
// Retourne 1 si l'affectation a réussi, 0 sinon
int assign_family(struct Family* family, int choice, int capacity[]) {
    if (capacity[choice] + family->num_people <= MAX_CAPACITY) {
        family->assigned_choice = choice;
        capacity[choice] += family->num_people;
        return 1;
    }
    return 0;
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
    char filename[] = "pb40.csv";
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

    /*
    // Afficher le tableau de familles trié
    for (int i = 0; i < num_families; i++) {
        printf("%d : %d %d %d %d %d\n", families[i].id, families[i].choices[0], families[i].choices[1], families[i].choices[2], families[i].choices[3], families[i].choices[4]);
    }
    */

    
    // Capacité maximale pour chaque choix
    int capacity[MAX_CHOICES] = {0};

    // Affecter chaque famille à son premier choix, s'il est possible
    for (int i = 0; i < num_families; i++) {
        int assigned = 0;
        for (int j = 0; j < MAX_CHOICES; j++) {
            if (assign_family(&families[i], families[i].choices[j], capacity)) {
                assigned = 1;
                break;
            }
        }
        if (!assigned) {
            printf("Impossible d'affecter la famille %d à un choix\n", i+1);
        }
    }
    /*
    // Afficher les affectations de chaque famille
    for (int i = 0; i < num_families; i++) {
        printf("Famille %d : ", families[i].id);
        printf("affectee au choix %d\n", families[i].assigned_choice);
    }

    int cost = compute_cost(families, num_families);
    printf("%d ", cost);
    */

    // Print out the families
    
    for (i = 0; i < num_families; i++) {
        //printf("Family %d: %d people, choices: ", i+1, families[i].num_people);
        printf("Family %d: %d people, assigned at %d, choices: ", families[i].id, families[i].num_people, families[i].assigned_choice);
        for (j = 0; j < MAX_CHOICES; j++) {
            printf("%d ", families[i].choices[j]);
        }
        printf("\n");
    }
    

    return 0;
}
