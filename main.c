#include <stdio.h>
#include <stdlib.h>

int triple(int nombre)
{
    return 3 * nombre;
}

int main(int argc, char *argv[])
{
    int valeur = 5;
    int valeurtr = 0;
    valeurtr = triple(valeur);
    printf("Le triple de %d vaut %d\n", valeur, valeurtr);

    return 0;
}

