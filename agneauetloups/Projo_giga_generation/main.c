#include "main.h"

void go_back(GtkWidget *emitter, t_game *game)
{
  game_history_back(game,1);
}

void go_save(GtkWidget *emitter, t_game *game)
{
	save_game(game,"save.ece");
}

int main (int argc, char *argv[])
{
  GtkWidget *win = NULL;
  GtkWidget *table = NULL;
  GtkWidget *button = NULL;
  FILE *current_path;
  t_game *game;
  int i,depth;
  
  // Initialisation de GTK
  
  srand(time(NULL));
  gtk_init (&argc, &argv);
  
  init_OS_path();
  
  table = window_init(&win);
  
  
  //game_init(&game,table,"Joe",HUMAN,WOLF,"Bob",HUMAN,LAMB);
  //game_init(&game,table,"ooo",HUMAN,LAMB,"eee",HUMAN,WOLF);
  load_game(&game,table,"save.ece");
  button = gtk_button_new_with_label("back");
  gtk_table_attach_defaults(GTK_TABLE(table),button,10,11,9,10);
  g_signal_connect(button,"clicked",GTK_SIGNAL_FUNC(go_back),game);
  
  afficher_console(game);
  //printf("mouton %d:%d , loups : %d:%d %d:%d %d:%d %d:%d %d:%d\n",game->data.now->lamb.x,game->data.now->lamb.y,game->data.now->wolf[0].x,game->data.now->wolf[0].y,game->data.now->wolf[1].x,game->data.now->wolf[1].y,game->data.now->wolf[2].x,game->data.now->wolf[2].y,game->data.now->wolf[3].x,game->data.now->wolf[3].y,game->data.now->wolf[4].x,game->data.now->wolf[4].y);
  //scanf("%d",&depth);
  
  //preIA(game,depth);
  //preIA(game,8);sleep(500);
  
  // Afficher et envoyer la sauce
  gtk_widget_show_all(win);
  gtk_main();
  return 0;
}

