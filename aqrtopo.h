typedef struct _un_noeud
{
  Un_truc *truc; //Une station ou connexion

  Une_coord limite_no; //limite zone
  Une_coord limite_se;//limite zone

  struct _un_noeud *no; //Fils pour quart NO

  struct _un_noeud *so; //Fils pour quart SO

  struct _un_noeud *ne; //Fils pour quart NE

  struct _un_noeud *se; //Fils pour quart SE
}Un_noeud;
