#include <stdio.h>
#include <stdlib.h>

#define MAX_CHOICES 5
#define MAX_CAPACITY 250

// Structure de données pour représenter une famille
struct Family {
    int num_people;
    int choices[MAX_CHOICES];
    int assigned_choice; // choix affecté (0 si aucun choix n'a été affecté)
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

// Fonction principale
int main() {
    // Exemple de tableau de familles
    struct Family families[] = {
        {5, {3, 6, 1, 4, 0}, 0},
        {4, {1, 4, 2, 0, 6}, 0},
        {2, {2, 5, 1, 0, 4}, 0},
        {3, {0, 6, 5, 1, 4}, 0},
        {7, {6, 5, 3, 0, 2}, 0}
    };
    int num_families = sizeof(families) / sizeof(struct Family);

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

    // Afficher les affectations de chaque famille
    for (int i = 0; i < num_families; i++) {
        printf("Famille %d : ", i+1);
        if (families[i].assigned_choice == 0) {
            printf("non affectée\n");
        } else {
            printf("affectée au choix %d\n", families[i].assigned_choice);
        }
    }

    return 0;
}
