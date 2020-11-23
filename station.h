typedef struct _une_station
{
  char *nom; //le nom
  struct _un_truc **tab_con; //Tableau des connexions
  unsigned int nb_con; //Nombre de connexions
  struct _un_truc *con_pcc; //connexion plus court chemin
}Une_station;
