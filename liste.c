#include <stdlib.h>
#include <stdio.h>

#include "coord.h"
#include "station.h"
#include "connexion.h"
#include "truc.h"
#include "liste.h"

Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *t)
{
  Un_elem *iter = liste;
  Un_elem *temp;

  while((iter->truc)->user_val < t->user_val)
  {
    temp = iter;
    iter = iter->suiv;
  }

  Un_elem *Nouveau_elem;
  Nouveau_elem = (Un_elem *)malloc(sizeof(Un_elem));
  Nouveau_elem->truc = t;
  Nouveau_elem->suiv = iter;

  temp->suiv = Nouveau_elem;

  if(t->user_val < liste->truc->user_val)
    return Nouveau_elem; //Cas special ou le nouvel element devient lui meme tete de liste
  else
    return liste; //Cas general
}

void ecrire_liste(FILE *flux, Un_elem *liste)
