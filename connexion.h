typedef struct _une_connexion
{
  struct _un_truc *sta_dep; //station de depart
  struct _un_truc *sta_arr; //station d'arrivée

  struct _une_ligne *ligne; //ligne
} Une_connexion;
