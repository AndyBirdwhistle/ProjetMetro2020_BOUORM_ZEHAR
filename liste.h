typedef struct _un_elem
{
  Un_truc *truc; //station ou connexion

  struct _un_elem *suiv;
}Un_elem;

Un_elem *inserer_liste_trie(Un_elem *list, Un_truc *truc);

void ecrire_liste(FILE *flux, Un_elem *liste);

void detruire_liste(Un_elem *liste);

void detruire_liste_et_truc(Un_elem *liste);
