#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "coord.h"
#include "station.h"
#include "connexion.h"
#include "truc.h"
#include "liste.h"

#define DELIM ","
#define BUFF_SIZE 128000
Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *truc){
  Un_elem *n=NULL;
  Un_elem *p=NULL;
  n=(Un_elem*)malloc(sizeof(Un_elem));
  if (!n){
    fprintf(stderr, "Erreur : allocation mémoire\n");
    return NULL;
  }
  n->truc=truc;
  n->suiv=NULL;
  if(!liste){
    return n;
  }
  if(liste->truc->user_val > truc->user_val){
    n->suiv=liste;
    return n;
  }
  p=liste;
  while(liste->suiv){
    if(liste->suiv->truc->user_val > truc->user_val){
      n->suiv=liste->suiv;
      liste->suiv=n;
      break;
    }
    liste=liste->suiv;
  }
  if(liste->suiv==NULL){
    liste->suiv=n;
  }
  return p;
}
//###################################################

char * str_dup (const char * str) //Fonction intermediaire pour lire_stations
{                                        //duplique un str
   char * dup = NULL;


   if (str != NULL)
   {
      size_t size = strlen (str) + 1;
      dup = malloc (size);

      if (dup != NULL)
      {
         memcpy (dup, str, size);
      }
   }


   return dup;
}

//.......................................................

Un_elem *lire_stations(char *nom_fichier)
{

  char *token = NULL;
  char buff[BUFF_SIZE];

  Une_coord *c;
  c = (Une_coord*)malloc(sizeof(Une_coord)); //coord pour le truc

  Tdata *d; //station pour le truc
  d = (Tdata*)malloc(sizeof(Tdata));

  Un_elem *liste_ret; //liste a retourner

  char *nom; //nom de la station

  FILE *flux = fopen(nom_fichier, "r");

  liste_ret = (Un_elem*)malloc(sizeof(Un_elem));

  if(flux != NULL)
  {
  for(int j = 0; j<619; j++) //Il y a 1552 lignes dans le fichier csv
  {
    if((fgets(buff, BUFF_SIZE, flux)) != NULL)
    {
      char *p = buff;
      int i = 0;


      if(liste_ret != NULL)
      {
        while((token = strtok(p, DELIM)) != NULL) //On extrait les champs délimités par des "," (ou ";" selon le fichier csv)
        {                                        //Avec strtok
          if(i==0)
            p = NULL;

          switch(i) //On itere entre nom, longitude et latitude; enum liste_types définie dans le .h
          {
            case NOM:
              {

                nom = (char *)malloc(sizeof(char)*100);

                strncpy(nom, str_dup(token),100);
                (d->sta).nom = nom;
                (d->sta).tab_con = NULL;
                (d->sta).con_pcc = NULL;
                (d->sta).nb_con = 0;

              }
              break;

            case LONG:
            {
              c->lon = atof(str_dup(token));
              break;
            }

            case LAT:
              c->lat = atof(str_dup(token));
              break;

            default:
              break;
          }
          i++;
          }
        }

        Un_truc *t = creer_truc(*c, 0, *d, (float)(rand()%500)/(float)(11)); //J'utilise juste un rand pour tester
        //On cree le truc correspondant au donnees extraites
        if(j==0)
        {
          (liste_ret->truc) = t;
          (liste_ret->suiv) = NULL; //Premier maillon pointe vers NULL


        }
        else
        {

          liste_ret = inserer_liste_trie(liste_ret, t); //Autres maillons ordonnés par le user_val

        }
      }

  }
    fclose(flux);
  }

  return liste_ret;
}

//###################################################

void ecrire_liste(FILE *flux, Un_elem *liste)
{
  while(liste != NULL)
  {

    char *c = (char *)malloc(sizeof(char)*100);
    c = (liste->truc->data).sta.nom;



    double lon = (liste->truc->coord).lon;
    double lat = (liste->truc->coord).lat;
    double pcc = (liste->truc->user_val);

    fprintf(flux, "Nom de station : %s \n coordonnees: %f %f \n Plus court chemin :%f m\n\n", c, lon, lat, pcc);
    liste = liste->suiv;
  }
}

//###################################################

void detruire_liste(Un_elem *liste)
{
  free(liste);
}

void detruire_liste_et_truc(Un_elem *liste)
{

  Un_elem *iter = (Un_elem *)malloc(sizeof(Un_elem));
  iter = liste;
  while(liste != NULL)
  {
    detruire_truc(liste->truc);
    iter= iter->suiv;
  }
  detruire_liste(liste);
}

//###################################################

Un_truc *extraire_deb_liste(Un_elem **liste)
{
  Un_elem *tmp=NULL;
  Un_truc *extract=NULL;
  tmp=*liste;
  *liste=(*liste)->suiv;
  extract=tmp->truc;
  free(tmp);
  return extract;
}

//###################################################

Un_truc *extraire_liste(Un_elem **liste, Un_truc *truc)
{
  Un_elem *tmp=NULL;
  Un_elem *prec=NULL;
  Un_truc *extract=NULL;
  if((*liste)->truc==truc){
    return extraire_deb_liste(liste);
  }
  tmp=*liste;
  while((*liste)->suiv){
    prec=*liste;
    *liste=(*liste)->suiv;
    if((*liste)->truc==truc){
      extract=extraire_deb_liste(liste);
      prec->suiv=*liste;
      return extract;
    }
  }
  *liste=tmp;
  return extract;
}

//###################################################

void limites_zone(Un_elem *liste, Une_coord *limite_no, Une_coord *limite_se){
  float lat;
  float lon;
  if(!liste || liste->truc->type !=STA){
    fprintf(stderr, "Erreur : liste vide\n");
    return;
  }
  limite_no->lon=liste->truc->coord.lon;
  limite_no->lat=liste->truc->coord.lat;
  limite_se->lon=liste->truc->coord.lon;
  limite_se->lat=liste->truc->coord.lat;
  liste=liste->suiv;
  while(liste){
    lat=liste->truc->coord.lat;
    lon=liste->truc->coord.lon;

    if(lat > limite_no->lat){
      limite_no->lat=lat;
    }
    if(lon < limite_no->lon){
      limite_no->lon=lon;
    }
    if(lat < limite_se->lat){
      limite_se->lat=lat;
    }
    if(lon > limite_se->lon){
      limite_se->lon=lon;
    }
    liste=liste->suiv;
  }
}
