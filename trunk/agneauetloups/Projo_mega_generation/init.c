#ifndef INITC
#define INITC

#include "[DOX]main.h"

GtkWidget *window_init(GtkWidget **win)
{
	GtkWidget *table;
	*win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(*win),0);
	gtk_window_set_title(GTK_WINDOW(*win),"Projo kilo generation");
	gtk_window_set_position(GTK_WINDOW(*win),GTK_WIN_POS_CENTER);
	gtk_widget_realize(*win);
	g_signal_connect(*win,"destroy",gtk_main_quit,NULL);
	if((table = gtk_table_new(10,10,TRUE))==NULL) return NULL;
	gtk_container_add(GTK_CONTAINER(*win),table);
	return table;
}

int game_init(t_game **game,GtkWidget *table,char *player1name,gboolean player1type,gboolean player1animal,char *player2name,gboolean player2type,gboolean player2animal)
 {
	int i,j;
    t_game *thegame = NULL;
	gchar path[128];
	// init jeu
	thegame = (t_game *) malloc(sizeof(t_game));
	if(thegame == NULL) return ERR_ALLOC_GAME;
	*game = thegame;
	
    // init joueurs
	thegame->players[0].type = player1type;
	thegame->players[0].animal = player1animal;
	thegame->players[1].type = player2type;
	thegame->players[1].animal = player2animal;
	if(player1animal == player2animal) return ERR_COMPATIBILITY;
	
	// init terrain
	thegame->data.orientation = (player1animal == LAMB);
	for(j=0;j<10;j++)
	{
		for(i=0;i<10;i++)
		{
			if((thegame->eventbox[i][j].eventbox = gtk_event_box_new())==NULL) return ERR_ALLOC_EVENTBOX;
			gtk_table_attach_defaults(GTK_TABLE(table),thegame->eventbox[i][j].eventbox,i,i+1,abs(9*thegame->data.orientation - j),abs(9*thegame->data.orientation - j)+1);
			gtk_signal_connect(GTK_OBJECT(thegame->eventbox[i][j].eventbox),"button_press_event",GTK_SIGNAL_FUNC(onclick),thegame);
			thegame->eventbox[i][j].position.x = i;
			thegame->eventbox[i][j].position.y = j;
			strcpy(path,PATH);
			if((abs(9*thegame->data.orientation - i)+abs(9*thegame->data.orientation - j))%2==0) strcat(path,"Bcase.BMP");
			else strcat(path,"Ncase.BMP");
			gtk_container_add(GTK_CONTAINER(thegame->eventbox[i][j].eventbox),gtk_image_new_from_file(path));
		}
	}
	
	// init data
	if((thegame->data.now = (t_history*) malloc(sizeof(t_history)))==NULL) return ERR_ALLOC_NOW;
	thegame->data.history = NULL;
	thegame->data.selection = NULL;
	if((thegame->data.player[0] = (char*) malloc((strlen(player1name)+1)*sizeof(char))) == NULL) return ERR_ALLOC_NAME1;
	strcpy(thegame->data.player[0],player1name);
	if((thegame->data.player[1] = (char*) malloc((strlen(player2name)+1)*sizeof(char))) == NULL) return ERR_ALLOC_NAME2;
	strcpy(thegame->data.player[1],player2name);
	
	// init positions dans data
	thegame->data.now->lamb.x = 4;
	thegame->data.now->lamb.y = 0;
	for(i=0;i<5;i++)
	{
		thegame->data.now->wolf[i].x = 2*i + 1;
		thegame->data.now->wolf[i].y = 9;
	}
	thegame->data.now->curplayer = player1animal;
	
	// init positions dans thegame
	thegame->pawn[0].position.x = thegame->data.now->lamb.x;
	thegame->pawn[0].position.y = thegame->data.now->lamb.y;
	thegame->pawn[0].eventbox = thegame->eventbox[thegame->data.now->lamb.x][thegame->data.now->lamb.y].eventbox;
	strcpy(path,PATH);
	strcat(path,"lamb.BMP");
	gtk_image_superimpose(thegame->eventbox[thegame->data.now->lamb.x][thegame->data.now->lamb.y].eventbox,path);
	strcpy(path,PATH);
	strcat(path,"wolf.BMP");
	for(i=0;i<5;i++)
	{
		thegame->pawn[i+1].position.x = thegame->data.now->wolf[i].x;
		thegame->pawn[i+1].position.y = thegame->data.now->wolf[i].y;
		thegame->pawn[i+1].eventbox = thegame->eventbox[thegame->data.now->wolf[i].x][thegame->data.now->wolf[i].x].eventbox;
		gtk_image_superimpose(thegame->eventbox[thegame->data.now->wolf[i].x][thegame->data.now->wolf[i].y].eventbox,path);
	}
	
	return SUCCESS;
}

#endif
