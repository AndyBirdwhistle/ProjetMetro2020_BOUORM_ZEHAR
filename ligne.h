typedef struct _une_ligne
{
  char *code; //Le nom de la _une_ligne

  char *color; //Couleur #RRGGBB
  float *vitesse; //vitesse moyenne en km/h

  float *intervalle; //intervalle moyen entre deux rames

  struct _une_ligne *suiv;
}Une_ligne;
