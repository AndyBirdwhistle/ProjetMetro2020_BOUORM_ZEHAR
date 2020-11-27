#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "coord.h"
#include "station.h"
#include "connexion.h"
#include "truc.h"
#include "liste.h"
#include "ligne.h"

#define DELIM ","
#define BUFF_SIZE 128000

//###################################################

Une_ligne *lire_lignes(char *nom_fichier)
{

  char *token = NULL;
  char buff[BUFF_SIZE];

  char *code; //station pour le truc

  Une_ligne *ligne_ret; //liste a retourner

  char *color;

  FILE *flux = fopen(nom_fichier, "r");

  ligne_ret = (Une_ligne *)malloc(sizeof(Une_ligne));

  if(flux != NULL)
  {
  for(int j = 0; j<63; j++) //Il y a 383 lignes dans le fichier csv
  {
    if((fgets(buff, BUFF_SIZE, flux)) != NULL)
    {
      char *p = buff;
      int i = 0;

      float *inter = (float *)malloc(sizeof(float));
      float *vitesse = (float *)malloc(sizeof(float));


      if(ligne_ret != NULL)
      {
        while((token = strtok(p, DELIM)) != NULL) //On extrait les champs délimités par des "," (ou ";" selon le fichier csv)
        {                                        //Avec strtok
          if(i==0)
            p = NULL;

          switch(i) //On itere entre nom, longitude et latitude; enum liste_types définie dans le .h
          {
            case CODE:
              {

                code = (char *)malloc(sizeof(char)*100);

                strncpy(code, str_dup(token),100);

              }
              break;

            case VIT:
            {


              *vitesse = atof(str_dup(token));

            }
            break;

            case INTER:
            {


              *inter = atof(str_dup(token));

            }

            case COLOR:
            {

              color = (char *)malloc(sizeof(char)*100);

              strncpy(color, str_dup(token),100);

            }

            default:
              break;
          }
          i++;
          }
        }

        //On cree le truc correspondant au donnees extraites
        Une_ligne *maillon = (Une_ligne *)malloc(sizeof(Une_ligne));
        maillon->code = code;
        maillon->color = color;
        (maillon->vitesse) = vitesse;
        (maillon->intervalle) = inter;
        if(j==0)
        {
          ligne_ret = maillon;
          ligne_ret->suiv = NULL; //Premier maillon pointe vers NULL


        }
        else
        {

          Une_ligne *temp = (Une_ligne *)malloc(sizeof(Une_ligne));
          temp = maillon;
          temp->suiv = ligne_ret;
          ligne_ret = temp;
        }
      }

  }
    fclose(flux);
  }

  return ligne_ret;
}


//###################################################

void afficher_lignes(Une_ligne *ligne)
{
  Une_ligne *parcours = (Une_ligne *)malloc(sizeof(Une_ligne));
  parcours = ligne;

  while(parcours != NULL)
  {
    printf("Ligne %s : vitesse moyenne : %f intervalle moyen entre deux stations : %f couleur en code html : %s\n", parcours->code, *(parcours->vitesse), *(parcours->intervalle), parcours->color);
    parcours = parcours->suiv;
  }
}

//###################################################

Une_ligne *chercher_ligne(char *code, Une_ligne *tete)
{
  Une_ligne *parcours = (Une_ligne *)malloc(sizeof(Une_ligne));
  parcours = tete;

  while(strcmp(parcours->code, code))
  {
    parcours = parcours->suiv;
    if(parcours == NULL) break;
  }

  return parcours;

}

//###################################################

void detruire_ligne(Une_ligne *li)
{
  if(li->suiv == NULL) //Cas darret
    free(li);
  else
    detruire_ligne(li->suiv);
}
/*
int main()
{


}*/
