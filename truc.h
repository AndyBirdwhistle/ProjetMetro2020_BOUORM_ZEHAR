typedef enum _ttype{STA, CON}Ttype;

typedef union _data
{
  Une_station sta;
  Une_connexion con;
}Tdata;

typedef struct _un_truc
{
  Une_coord coord;
  Ttype type;
  Tdata data;
  float user_val; //Distance pour le plus court chemin
} Un_truc;