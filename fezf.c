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