typedef struct _une_ligne
{
  char *code; //Le nom de la _une_ligne

  char *color; //Couleur code HTML
  float *vitesse; //vitesse moyenne en km/h

  float *intervalle; //intervalle moyen entre deux rames

  struct _une_ligne *suiv;
}Une_ligne;

typedef enum
{
   CODE,
   VIT,
   INTER,
   COLOR,
}lignes_types;

Une_ligne *lire_lignes(char *nom_fichier);

void detruire_ligne(Une_ligne *li);

void afficher_lignes(Une_ligne *ligne);

Une_ligne *chercher_ligne(char *code, Une_ligne *tete);
