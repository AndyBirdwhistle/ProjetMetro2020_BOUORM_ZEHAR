//
//  EXERCICE DIKJ 6.h
//  projet info
//
//  Created by zehar on 24/11/2020.
//

#ifndef EXERCICE_DIKJ_6_h
#define EXERCICE_DIKJ_6_h

/* includes */
#include "liste.h"
#include "truc.h"

/* defines */
#define T_COR 1.5
#define T_PAU 0.5

/* fonctions */
void dijkstra(Un_elem *liste_sta, Un_truc *sta_dep);

Un_elem *cherche_chemin(Un_truc *sta_arr);

#endif /* EXERCICE_DIKJ_6_h */
