//
//  aqr.h
//  projet info
//
//  Created by zehar on 27/11/2020.
//



/* includes */

#include "liste.h"
#ifndef aqr
#define aqr

/* includes */

#include "truc.h"

/* types */

typedef struct _un_noeud
    {
    Un_truc *truc; //Une station ou une connexion
    Une_coord limite_no; //Limite zone
    Une_coord limite_se; //Limite zone
    struct _un_noeud *no; //Fils pour quart NO
    struct _un_noeud *so; //Fils pour quart SO
    struct _un_noeud *ne; //Fils pour quart NE
    struct _un_noeud *se; //Fils pour quart SE
    } Un_noeud;

/* fonctions generiques */

Un_noeud *inserer_aqr(Un_noeud *aqr, Une_coord limite_no, Une_coord limite_se, Un_truc *truc);

Un_noeud *construire_aqr(Un_elem *liste);

void detruire_aqr(Un_noeud *aqr);

Un_truc *chercher_aqr(Un_noeud *aqr, Une_coord coord);

Un_elem *chercher_zone(Un_noeud *aqr, Un_elem *liste, Une_coord limite_no, Une_coord limite_se);

int hauteur_aqr(Un_noeud *aqr);

/* fonctions ajoutées */
int max(int a, int b);

#endif
