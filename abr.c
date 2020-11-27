#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "coord.h"

#include "station.h"
#include "connexion.h"

#include "truc.h"

#include "liste.h"
#include "ligne.h"
#include "abr.h"
#include "dijkstra.h"



Un_nabr *creer_nabr(Un_truc *truc){
  Un_nabr *tmp=NULL;
  tmp=(Un_nabr *)malloc(sizeof(Un_nabr));
  if(!tmp){
    fprintf(stderr, "Erreur : allocation mémoire\n");
    return NULL;
  }
  tmp->truc=truc;
  tmp->g=NULL;
  tmp->d=NULL;
  return tmp;
}

Un_nabr *inserer_abr(Un_nabr *abr, Un_nabr *n){
  if (!abr)
    return n;
  if (strcmp (n->truc->data.sta.nom,abr->truc->data.sta.nom)<=0){
    abr->g = inserer_abr(abr->g, n);
  }
  else{
    abr->d = inserer_abr(abr->d, n);
  }
  return abr;
}

Un_nabr *construire_abr(Un_elem *liste_sta){
  Un_nabr *abr=NULL;
  Un_nabr *noeud=NULL;
  Un_elem *mem=liste_sta;
  while(liste_sta){
    noeud = creer_nabr(liste_sta->truc);
    abr = inserer_abr(abr, noeud);
    liste_sta = liste_sta->suiv;
  }
  liste_sta=mem;
  return abr;
}


void detruire_abr(Un_nabr *abr){
  if(abr){
    detruire_abr(abr->g);
    detruire_abr(abr->d);
    free(abr);
  }
}

//###################################################

Un_truc *chercher_station(Un_nabr *abr, char *nom)
{
  Un_nabr *parcours = (Un_nabr *)malloc(sizeof(Un_nabr));

  parcours = abr;

  while(parcours != NULL)
  {

    printf("%s\n", (parcours->truc->data).sta.nom);
    if(!strcmp((parcours->truc->data).sta.nom, nom))
      break;

    if(strcmp((parcours->truc->data).sta.nom, nom) < 0)
      parcours = parcours->d;

    if(parcours == NULL) return NULL;

    if(strcmp((parcours->truc->data).sta.nom, nom) > 0)
      parcours = parcours->g;

    if(parcours == NULL) return NULL;
  }
  printf("\n");

  return parcours->truc;
}
