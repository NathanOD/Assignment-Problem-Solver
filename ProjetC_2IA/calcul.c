//
//  calcul.c
//  ProjetC_2IA
//
//  Created by Nathan Odic on 12/03/2023.
//

#include "calcul.h"

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
