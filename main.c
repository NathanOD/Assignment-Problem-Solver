#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_FAMILIES 500 // Nombre maximum de familles dans le CSV
#define MAX_CHOICES 5    // Nombre maximum de choix par famille

// On créé un structure Family
struct Family {
    int id; // Identifiant de la famille
    int num_people; // Nombre de personnes dans la famille
    int choices[MAX_CHOICES]; // Liste des choix de la famille
    int assigned_choice; // Jour assigné à la famille
};

// Fonction de calcul du coût des assignations
int calculerCout(int choix, int nmb) {
    int cout = 0;
    // On créé un switch pour calculer les différents coûts
    // selon le choix auquel a été assigné la famille
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

// Fonction de calcul de la pénalité des assignations
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

// Fonction d'assignation des familles
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


int main() {
    // Ouverture du fichier CSV
    char filename[] = "pb20.csv";
    FILE *fp;
    char line[100];
    char *token;
    struct Family families[MAX_FAMILIES];
    int num_families = 0;
    int i, j;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Erreur: Impossible d'ouvrir le fichier %s\n", filename);
        exit(1);
    }
    // Chargement des données du CSV dans la structure Family
    fgets(line, sizeof(line), fp); // On ne tient pas compte de la première ligne du tableau
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
    // On ferme le fichier CSV
    fclose(fp);


    //CODE
    
    // Trier le tableau de familles en utilisant le tri rapide
    quicksort(families, 0, num_families-1);
    
    // Assignation des familles
    int capacities[7] = {250, 250, 250, 250, 250, 250, 250};
    assign_families(families, num_families, capacities);
    assign_sac_families(families, num_families);
    

    // Affichage des informations sur les familles
    for (i = 0; i < num_families; i++) {
        printf("Famille %d: %d personnes, assignees à %d, choix: ", families[i].id, families[i].num_people, families[i].assigned_choice);
        for (j = 0; j < MAX_CHOICES; j++) {
            printf("%d ", families[i].choices[j]);
        }
        printf("\n");
    }

    // Calcul et affichage du nombre de personnes par jour
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

    // Calcul et affichage de la fonction objectif
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
    double penalite = calculerPenalite(pers_jour);
    printf("Cout : %d\n", cout_tot);
    printf("Penalite : %f\n", penalite);
    printf("Fonction objectif : %f\n", cout_tot + penalite);

    return 0;
}
