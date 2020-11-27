typedef struct _un_elem
{
  Un_truc *truc; //station ou connexion

  struct _un_elem *suiv;
}Un_elem;


typedef enum
{
   NOM,
   LONG,
   LAT,
}liste_types;

char * str_dup (const char * str) ;

Un_elem *inserer_liste_trie(Un_elem *list, Un_truc *truc);

void ecrire_liste(FILE *flux, Un_elem *liste);

void detruire_liste(Un_elem *liste);

void detruire_liste_et_truc(Un_elem *liste);

Un_elem *lire_stations(char *nom_fichier);

Un_elem *inserer_deb_liste(Un_elem *liste, Un_truc *truc);

void limites_zone(Un_elem *liste, Une_coord *limite_no, Une_coord *limite_se);

Un_truc *extraire_liste(Un_elem **liste, Un_truc *truc);

Un_truc *extraire_deb_liste(Un_elem **liste);
