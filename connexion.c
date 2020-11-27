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

Un_elem *inserer_deb_liste(Un_elem *liste, Un_truc *truc)
{
  Un_elem * ret = (Un_elem *)malloc(sizeof(Un_elem));
  ret->truc = truc;
  ret->suiv = liste;

  return ret;
}

//###################################################
/*

Un_elem *lire_connexions(char *nom_fichier, Une_ligne *liste_ligne, Un_nabr *abr_sta)
{

  char *token = NULL;
  char buff[BUFF_SIZE];

  Un_elem *liste_ret; //liste a retourner

  char *nom; //nom de la station

  FILE *flux = fopen(nom_fichier, "r");

  liste_ret = (Un_elem*)malloc(sizeof(Un_elem));

  if(flux != NULL)
  {
  for(int j = 0; j<1542; j++) //Il y a 1552 lignes dans le fichier csv
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

          switch(i)
          {
            case LIGNE:
              {

                Une_ligne *L = (Une_ligne*)malloc(sizeof(Une_ligne));
                L = chercher_ligne(str_dup(token), liste_ligne);

              }
              break;

            case PTA:
            {
              Un_truc *Tr_PTA = (Un_truc *)malloc(sizeof(Un_truc));
              Tr_PTA = chercher_station(abr_sta, str_dup(token));
              break;
            }

            case PTB:
            {
              Un_truc *Tr_PTB = (Un_truc *)malloc(sizeof(Un_truc));
              Tr_PTB = chercher_station(abr_sta, str_dup(token));
              break;
            }

            case ZERO1:
            {
              break;
            }

            case ZERO2:
            {
              break;
            }

            default:
              break;
          }

          i++;
          }
        }

        Une_connexion * = (Une_connexion *)malloc(sizeof(Une_connexion));
        if((Tr_PTA->data).sta.nb_con == NULL) //on initialize le tableau des connexions
        {

          (Tr_PTA->data).sta.nb_con = 1;
          (Tr_PTA->data).sta.tab_con = (Un_truc **)malloc(sizeof(Un_truc*)*20);
          for(int k = 0; k<20: k++)
            (Tr_PTA->data).sta.tab_con[k] = (Un_truc *)malloc(sizeof(Un_truc));
            (Tr_PTA->data).sta.tab_con[k] = NULL;
            (Tr_PTA->data).sta.tab_con[0] =
        }
        else
        {
          (Tr_PTA->data).sta.nb_con ++;
          Un_truc *parcours = (Un_truc*)malloc(sizeof(Un_truc));
          while(parcours != NULL)
        }


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
*/

Un_elem *lire_connexions(char *nom_fichier, Une_ligne *liste_ligne, Un_nabr *abr_sta)
{
    Un_elem *liste=NULL;
    FILE *f;
    char ligne[1542];
    f=fopen(nom_fichier, "r");

    if(f==NULL){
        fprintf(stderr, "Erreur d'ouverture du fichier \n");
        return NULL;
    }
    while(fgets(ligne, 1542, f)){
        Une_coord coord;
        Tdata data;
        char *pc=ligne;
        char *code, *nom_dep, *nom_arr;
        float val;
        Un_truc *connex, *sta_dep;

        if(*ligne == '#') continue;
        code=pc;
        while(*pc!=',') pc++;
        *pc++='\0';
        nom_dep=pc;
        while(*pc!=',') pc++;
        *pc++='\0';
        nom_arr=pc;
        while(*pc!=',') pc++;
        *pc++='\0';
        val=atof(pc);

        if((data.con.ligne=chercher_ligne(code, liste_ligne)) == NULL){     //appel de chercher_ligne
            fprintf(stderr, "ligne non trouvée : %s\n", code);
            continue;
        }
        if((data.con.sta_dep=chercher_station(abr_sta, nom_dep)) == NULL){//appel de chercher_station
            fprintf(stderr, "station non trouvée : %s\n", nom_dep);
            continue;
        }
        if((data.con.sta_arr=chercher_station(abr_sta, nom_arr)) == NULL){//appel de chercher_station
            fprintf(stderr, "station non trouvée : %s\n", nom_arr);
            continue;
        }

        if(val==0.0){
            Une_coord cdep, carr;
            float dx, dy;
            cdep=data.con.sta_dep->coord;
            carr=data.con.sta_arr->coord;
            coord.lon=cdep.lon;
            coord.lat=cdep.lat;
            dx=((carr.lat-cdep.lat)*M_PI*6370)/180;
            dy=((carr.lon-cdep.lon)*M_PI*6370)/180;
            val=60*(sqrtf((dx*dx)+(dy*dy)))/(*(data.con.ligne->vitesse));
        }

        connex=creer_truc(coord, CON, data, val);

        // ajout à la station de départ

        sta_dep=data.con.sta_dep;
        (sta_dep->data.sta.nb_con)++;
        sta_dep->data.sta.tab_con=realloc(sta_dep->data.sta.tab_con, sta_dep->data.sta.nb_con*sizeof(Un_truc *));
        sta_dep->data.sta.tab_con[sta_dep->data.sta.nb_con-1]=connex;
        liste=inserer_deb_liste(liste, connex);
    }
    fclose(f);
    return liste;
}
