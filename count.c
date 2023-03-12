#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 500 // définir la taille maximale du tableau
#define NUM_COLUMNS 6 // définir le nombre de colonnes dans le fichier CSV

int calculerCout(int choix, int nmb);
double calculerPenalite(int jour, int population[]);

int main() {
    FILE *fichier;
    fichier = fopen("pb40.csv", "r");
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
    int choix[nbligne+1][7];
    //float choix[nbligne+1][7];

    int pos = 0;

    for (int k = 1; k < nbligne+1; k++) {
        switch (tableau[k][1]) {
            case 0:
                choix[pos][0] = tableau[k][0];
                choix[pos][1] = 0;
                choix[pos][2] = 0;
                choix[pos][3] = 0;
                choix[pos][4] = 0;
                choix[pos][5] = 0;
                choix[pos][6] = 0;
                pos++;
                break;
            case 1:
                choix[pos][1] = tableau[k][0];
                choix[pos][0] = 0;
                choix[pos][2] = 0;
                choix[pos][3] = 0;
                choix[pos][4] = 0;
                choix[pos][5] = 0;
                choix[pos][6] = 0;
                pos++;
                break;
            case 2:
                choix[pos][2] = tableau[k][0];
                choix[pos][0] = 0;
                choix[pos][1] = 0;
                choix[pos][3] = 0;
                choix[pos][4] = 0;
                choix[pos][5] = 0;
                choix[pos][6] = 0;
                pos++;
                break;
            case 3:
                choix[pos][3] = tableau[k][0];
                choix[pos][0] = 0;
                choix[pos][1] = 0;
                choix[pos][2] = 0;
                choix[pos][4] = 0;
                choix[pos][5] = 0;
                choix[pos][6] = 0;
                pos++;
                break;
            case 4:
                choix[pos][4] = tableau[k][0];
                choix[pos][0] = 0;
                choix[pos][1] = 0;
                choix[pos][2] = 0;
                choix[pos][3] = 0;
                choix[pos][5] = 0;
                choix[pos][6] = 0;
                pos++;
                break;
            case 5:
                choix[pos][5] = tableau[k][0];
                choix[pos][0] = 0;
                choix[pos][1] = 0;
                choix[pos][2] = 0;
                choix[pos][3] = 0;
                choix[pos][4] = 0;
                choix[pos][6] = 0;
                pos++;
                break;
            case 6:
                choix[pos][6] = tableau[k][0];
                choix[pos][0] = 0;
                choix[pos][1] = 0;
                choix[pos][2] = 0;
                choix[pos][3] = 0;
                choix[pos][4] = 0;
                choix[pos][5] = 0;
                pos++;
                break;
        }
    }

    for (int j = 0; j < 7; j++) {
        int somme = 0;
        for (int i = 0; i < nbligne; i++) {
            somme += choix[i][j];
        }
        choix[pos][j] = somme;
    }

    for (int j = 0; j < 7; j++) {
        int somme = 0;
        for (int i = 0; i < nbligne; i++) {
            somme += choix[i][j];
        }
        choix[pos][j] = somme;
        
        /*
        if (somme <= 250)
        {
            choix[pos+1][j] = 1;
        }
        else
        {
            choix[pos+1][j] = 0;
        }
        */
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
    for (int k = 0; k < nbligne+1; k++) {
        for (int l = 0; l < 7; l++) {
            printf("%d ", choix[k][l]);
        }
        printf("\n");
    }




    // Calcul pénalité
    /*
    double penalite = 0.0;
    float list_pen[7];
    int ind_max = 0;
    for (int j = 0; j < 7; j++) {
        double pen = 0.0;
        if (j < 6)
        {
            pen = ((choix[pos][j]-125)/400.0)*pow(choix[pos][j], abs(choix[pos][j]-choix[pos][j+1])/50.0);
        }
        else
        {
            pen = ((choix[pos][j]-125)/400.0)*pow(choix[pos][j], abs(choix[pos][j]-choix[pos][j])/50.0);
        }
        list_pen[j] = pen;
        penalite += pen;
        
        if (pen>list_pen[ind_max])
        {
            ind_max = j;
        }
        printf("%f ", list_pen[j]);
    }
    printf("\n");
    printf("%f", penalite);
    printf("\n");
    printf("%d", ind_max);
    */

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
