

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

int main(int argc, char *argv[])
{

if(!strcmp(argv[1], "Chercher_ligne"))
{

  Une_ligne *test = (Une_ligne *)malloc(sizeof(Une_ligne));

  test = lire_lignes(argv[3]);

  test = chercher_ligne(argv[2], test);


  if(test == NULL)
    printf("NULL\n");
  else
  printf("Ligne %s : vitesse moyenne : %f intervalle moyen entre deux stations : %f couleur en code html : %s\n", test->code, *(test->vitesse), *(test->intervalle), test->color);
;

  return 0;
}

if(!strcmp(argv[1], "Chercher_station_alpha"))
{
  Un_elem *l = (Un_elem *)malloc(sizeof(Un_elem));
  l = lire_stations(argv[3]);

  FILE *texte = fopen(argv[4], "w");
  ecrire_liste(texte, l);


  Un_nabr *testabr = (Un_nabr *)malloc(sizeof(Un_nabr));
  testabr = construire_abr(l);

  Un_truc *t = chercher_station(testabr, argv[2]);

  if(t==NULL) printf("Pas de stations à ce nom\n" );


}

if(!strcmp(argv[1], "Connexions"))
{
  Un_elem *l = (Un_elem *)malloc(sizeof(Un_elem));
  l = lire_stations(argv[2]);


  Un_nabr *testabr = (Un_nabr *)malloc(sizeof(Un_nabr));
  testabr = construire_abr(l);

  Une_ligne *test = (Une_ligne *)malloc(sizeof(Une_ligne));
  test = lire_lignes(argv[3]);

  Un_elem *testcon = (Un_elem *)malloc(sizeof(Un_elem));
  testcon = lire_connexions(argv[4], test, testabr);

  free(testcon);

}

if(!strcmp(argv[1], "dijkstra"))
{
  Un_elem *l = (Un_elem *)malloc(sizeof(Un_elem));
  l = lire_stations(argv[3]);


  Un_nabr *testabr = (Un_nabr *)malloc(sizeof(Un_nabr));
  testabr = construire_abr(l);


  Un_truc *t = chercher_station(testabr, argv[2]);

  dijkstra(l, t);

}



}
