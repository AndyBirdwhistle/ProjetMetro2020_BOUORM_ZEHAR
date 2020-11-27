

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
#include "aqrtopo.h"

#include "dijkstra.h"
#include <float.h>


void dijkstra(Un_elem *liste_sta, Un_truc *sta_dep)
{
  if(sta_dep != NULL)
  {
    Un_elem *t = liste_sta;

    Un_elem *liste_ = NULL;
    while(t != NULL)
    {
      if(t->truc == sta_dep)
      {
        sta_dep->user_val=0;
        liste_ = inserer_liste_trie(liste_, t->truc);
      }
      else
      {
        t->truc->user_val = DBL_MAX;
        liste_ = inserer_liste_trie(liste_, t->truc);
      }
      t = t->suiv;
    }

    while(liste_ != NULL)
    {
      Un_truc *extract = extraire_deb_liste(&liste_);
      for(int i=0; i<extract->data.sta.nb_con; i++)
      {
        Une_ligne *tLigne = extract->data.sta.tab_con[i]->data.con.ligne;

        double vit = *(tLigne->vitesse) * 1000 / 60;

        double distance = sqrt(((extract->coord.lat)-(sta_dep->coord.lat))*((extract->coord.lat)-(sta_dep->coord.lat))+((extract->coord.lon)-(sta_dep->coord.lon))*((extract->coord.lon)-(sta_dep->coord.lon)));

        double time = distance/(float)vit;



        if(time<extract->data.sta.tab_con[i]->user_val)
        {
          extract->data.sta.tab_con[i] -> user_val = time;
          extract->data.sta.tab_con[i] -> data.sta.con_pcc = extract;
          Un_truc *tr = extraire_liste(&liste_, extract->data.sta.tab_con[i]);
          printf("%f\n", extract->data.sta.tab_con[i] -> user_val);


          if(tr != NULL)
            liste_ = inserer_liste_trie(liste_, tr);
          else
            printf("NULL\n");
        }
      }
    }


  }
}
Un_elem *cherche_chemin(Un_truc *sta_arr){
  Un_elem *res=NULL;
  Un_truc *tmp=NULL;

  if(sta_arr->data.sta.con_pcc==NULL){
    fprintf(stdout, "Erreur : Le plus court chemin n'a pas été trouvé.\n");
    return NULL;
  }
  tmp=sta_arr;
  res=inserer_deb_liste(res, tmp);

  while(tmp->data.sta.con_pcc!=NULL){
    tmp=tmp->data.sta.con_pcc->data.con.sta_dep;
    res=inserer_deb_liste(res, tmp);
  }
  return res;
}
