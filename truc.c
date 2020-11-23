#include <stdlib.h>
#include <stdio.h>

#include "coord.h"
#include "station.h"
#include "connexion.h"
#include "truc.h"

Un_truc  *creer_truc(Une_coord coord, Ttype type, Tdata data, double uv)
{
  Un_truc *ret;

  ret = (Un_truc *)malloc(sizeof(Un_truc));
  ret->coord = coord;
  ret->type = type;
  ret->data = data;
  ret->user_val = uv;

  return ret;
}

void detruire_truc(Un_truc *truc)
{
  free(truc);
  if(truc->type == 0)
  {
    free((truc->data).sta.nom);
    free((truc->data).sta.tab_con);
  }
}
