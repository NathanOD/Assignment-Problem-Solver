//
//  assign.h
//  ProjetC_2IA
//
//  Created by Nathan Odic on 12/03/2023.
//

#ifndef assign_h
#define assign_h

#include <stdio.h>
#include "tri.h"

#define MAX_NEW_FAMILIES 3

void assign_families(struct Family families[], int num_families, int capacity[]);
void assign_sac_families(struct Family families[], int num_families);
void assign_other_families(struct Family families[], int ind[][7], int exp);

#endif /* assign_h */
