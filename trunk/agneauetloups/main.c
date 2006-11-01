#include "projet.h"

/// fonction d'initialisation du programme
/**
crée les widgets, configure leurs comportement et lance l'affichage
*/

int main (int argc, char *argv[])
{

  GtkWidget *win = NULL;
  GtkWidget *button[50];
  GtkWidget *table;
  t_movement move;
  gint i;

  t_tout* tout;

  /* Initialize GTK+ */
  gtk_init(&argc,&argv);
  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(win),"Sheep run - alpha test");
  gtk_window_set_position(GTK_WINDOW(win),GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(win),300,300);
  g_signal_connect(win,"destroy",gtk_main_quit,NULL);
  
  table = gtk_table_new(10,10,TRUE);
  gtk_container_add(GTK_CONTAINER(win),GTK_WIDGET(table));
  
  move.lastone = NULL;

  
  //mise des labels des boutons à VIDE
  //positionnement des boutons
  for(i=0;i<50;i++)
  {
      button[i] = gtk_button_new_with_label("");
      gtk_table_attach_defaults(GTK_TABLE(table),button[i],2*(i%5)+1-(i%10-i%5)/5,2*(i%5)+1-(i%10-i%5)/5+1,2*(i-i%10)/10+(i%10-i%5)/5,2*(i-i%10)/10+(i%10-i%5)/5+1);
  }
  //creation de la structure tout
  tout = (t_tout*)malloc(sizeof(t_tout));
  //champs de data pour chacun des pions (allocation du pointeur sur tableau)
  tout->
  for(i=0;i<5;i++)
  {
    //mise des labels pour les boutons des pions
    gtk_button_set_label(GTK_BUTTON(button[i]),"L");
    //creation des champs de data pour chacun des pions
    
  gtk_button_set_label(GTK_BUTTON(button[47]),"A");
  
  //configuration de la fonction callback a appeler quand un bouton est presse
  for(i=0;i<50;i++) //g_signal_connect(G_OBJECT(button[i]),"clicked",G_CALLBACK(make_movement),&move);
	g_signal_connect(G_OBJECT(button[i]),"clicked",G_CALLBACK(make_movement),tout);
  
  //insertion du tableau de boutons dans la pointeur sur structure "tout"
  tout->button = button;
  

  gtk_widget_show_all(win);
  gtk_main ();
  return 0;
}

/// retourne l'entier correspondant au bouton donne dans le tableau de boutons du jeu
int get_button_index(GtkWidget* whatButton, t_tout* tout)
{
  int a=0;
  while(tout->button[a] != whatButton) a++;
  return a;
}
/// retourne la position d'un entier dans un tableau d'entier ; -1 si non trouve
int get_int_index(int integer, int* table, int table_length)
{
  int a=0;
  while(a<table_length && table[a] != integer) a++;
  return (a == table_length) ? -1 : a;
}
/// retourne un booleen indiquant si un bouton donne correspond a un pion du joueur dont c'est le tour
int belongs_to_player(GtkWidget* what, t_tout* tout)
{
  // resultat
  int result;
  // iterateur
  int a=0;
  // index du bouton donne dans "tout"
  int button_index = get_button_index(what, tout);
  // selon le role du joueur dont c'est le tour
  switch(tout->cur_player)
  {
    // s'il joue comme un agneau
    case LAMB:
      // le resultat 
      result = (get_int_index(button_index,tout->data->lamb.poss) != -1);
      break;
    case WOLF:
      while(a<5 && (result = get_int_index(button_index,tout->data->wolf[a].poss)) == -1) a++;
      result = (result != -1);
      break;
  }
  return result;
}

void clicked(GtkWidget *emitter, t_tout* tout)
{
  //Si le bouton est un pion du joueur en cours
  if(emitter
}

void make_movement(GtkWidget *newone,t_movement *move)
{
  gchar *animal;
  if(move->lastone == NULL)
  {
    move->lastone = newone;
  }
  else
  {
    animal = gtk_button_get_label(GTK_BUTTON(move->lastone));
    gtk_button_set_label(GTK_BUTTON(newone),animal);
    gtk_button_set_label(GTK_BUTTON(move->lastone),"");
    move->lastone = NULL;
  }
}
