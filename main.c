#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 500 // définir la taille maximale du tableau
#define NUM_COLUMNS 6 // définir le nombre de colonnes dans le fichier CSV

int calculerCout(int choix, int nmb);
double calculerPenalite(int jour, int population[]);

int main() {
    FILE *fichier;
    fichier = fopen("pb10.csv", "r");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier\n");
        return 1;
    }

    char ligne[MAX_SIZE];
    char *valeur;

    int tableau[MAX_SIZE][NUM_COLUMNS];

    int i = 0;
    while (fgets(ligne, MAX_SIZE, fichier) != NULL) {
        valeur = strtok(ligne, ";");

        int j = 0;
        while (valeur != NULL) {
            tableau[i][j] = atoi(valeur);
            valeur = strtok(NULL, ";");
            j++;
        }

        i++;
    }

    fclose(fichier);

    int nbligne = i-1;
    int choix[nbligne][7];
    //int famille = 1;

    int pos0 = 0;
    int pos1 = 0;
    int pos2 = 0;
    int pos3 = 0;
    int pos4 = 0;
    int pos5 = 0;
    int pos6 = 0;

    for (int k = 1; k < nbligne; k++) {
        switch (tableau[k][1]) {
            case 0:
                choix[pos0][0] = tableau[k][0];
                pos0++;
                //famille++;
                break;
            case 1:
                choix[pos1][1] = tableau[k][0];
                pos1++;
                //famille++;
                break;
            case 2:
                choix[pos2][2] = tableau[k][0];
                pos2++;
                //famille++;
                break;
            case 3:
                choix[pos3][3] = tableau[k][0];
                pos3++;
                //famille++;
                break;
            case 4:
                choix[pos4][4] = tableau[k][0];
                pos4++;
                //famille++;
                break;
            case 5:
                choix[pos5][5] = tableau[k][0];
                pos5++;
                //famille++;
                break;
            case 6:
                choix[pos6][6] = tableau[k][0];
                pos6++;
                //famille++;
                break;
        }
    }

    /*
    int nb_ligne = nbligne;
    int ligne_sup = -1;

    for (int i = 0; i < nb_ligne; i++) {
        int nb_zero = 0;
        for (int j = 0; j < nb_ligne; j++) {
            if (choix[i][j] == 0) {
                nb_zero++;
            }
        }
        if (nb_zero == 7) {
            ligne_sup = i;
            break;
        }
    }

    if (ligne_sup != -1) {
        nb_ligne = ligne_sup;
    }

    if (ligne_sup != -1) {
        for (int i = ligne_sup; i < nb_ligne; i++) {
            for (int j = 0; j < 7; j++) {
                choix[i][j] = choix[i+1][j];
            }
        }
        nb_ligne--;
    }
    */

    /*
    // afficher le tableau
    for (int k = 1; k < i; k++) {
        for (int l = 0; l < NUM_COLUMNS; l++) {
            printf("%d ", tableau[k][l]);
        }
        printf("\n");
    }
    */

    // afficher le tableau
    for (int k = 0; k < i-1; k++) {
        for (int l = 0; l < 7; l++) {
            printf("%d ", choix[k][l]);
        }
        printf("\n");
    }

    return 0;
}





/*
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
        default:
            printf("Erreur : choix invalide\n");
            break;
    }
    return cout;
}

double calculerPenalite(int jour, int population[]) {
    double penalite = 0.0;
    int pop_jour = population[jour];
    if (jour < 6) {
        int pop_jour_suivant = population[jour + 1];
        double exposant = fabs(pop_jour - pop_jour_suivant) / 50.0;
        penalite = ((pop_jour - 125.0) / 400.0) * pow(pop_jour, exposant);
    } else if (jour == 6) {
        penalite = ((pop_jour - 125.0) / 400.0) * pow(pop_jour, 0.0);
    } else {
        printf("Erreur : jour invalide\n");
    }
    return penalite;
}
*/
