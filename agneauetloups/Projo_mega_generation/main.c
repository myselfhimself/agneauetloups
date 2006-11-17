#include "[DOX]main.h"

int main (int argc, char *argv[])
{
  GtkWidget *win = NULL;
  GtkWidget *table = NULL;
  FILE *current_path;
  t_game *game;
  int i,depth;
  
  // Initialisation de GTK
  
  gtk_init (&argc, &argv);
  
  init_OS_path();
  
  table = window_init(&win);
  
  game_init(&game,table,"Joe",HUMAN,WOLF,"Bob",HUMAN,LAMB);
  //game_init(&game,table,"Joe",HUMAN,LAMB,"Bob",HUMAN,WOLF);
  /*game->pawn[0].position.x=4;
  game->pawn[0].position.y=3;
  game->pawn[1].position.x=1;
  game->pawn[1].position.y=4;
  game->pawn[2].position.x=3;
  game->pawn[2].position.y=4;
  game->pawn[3].position.x=5;
  game->pawn[3].position.y=4;
  game->pawn[4].position.x=7;
  game->pawn[4].position.y=4;
  game->pawn[5].position.x=9;
  game->pawn[5].position.y=4;*/
  //afficher_console(game);
  //printf("mouton %d:%d , loups : %d:%d %d:%d %d:%d %d:%d %d:%d\n",game->data.now->lamb.x,game->data.now->lamb.y,game->data.now->wolf[0].x,game->data.now->wolf[0].y,game->data.now->wolf[1].x,game->data.now->wolf[1].y,game->data.now->wolf[2].x,game->data.now->wolf[2].y,game->data.now->wolf[3].x,game->data.now->wolf[3].y,game->data.now->wolf[4].x,game->data.now->wolf[4].y);
  //scanf("%d",&depth);
  
  //preIA(game,depth);
  
  // Afficher et envoyer la sauce
  gtk_widget_show_all(win);
  gtk_main();
  return 0;
}

