#include "main.h"

//retourne l'index dans le tableau game->players du joueur en cours
int current_player_id(t_game* game)
{
	int a;
	int current_animal;
	int result;

	current_animal = game->data.now->curplayer;
	for(a=0;a<2;a++)
	{
		if(game->players[a].animal == current_animal)
		{
			result=a;
			break;	
		}
	}
	return result;
}

//retourne un pointeur sur le nom du joueur en cours
char* current_player_name(t_game * game)
{
	return game->data.player[current_player_id(game)];
}

//retourne un pointeur sur le t_player du joueur en cours
t_player* current_player(t_game* game)
{
	return &(game->players[current_player_id(game)]);
}

//change une variable de game pour que le click sur le terrain soit insensible
void game_lock(t_game* game, gboolean do_lock)
{
	game->locked = do_lock;
}

//indique si le terrain est bloqué localement (clics insensibles)
gboolean game_locked(t_game* game)
{
	return game->locked;
}

//gestionnaire de joueurs
//gboolean a un entête bizarre pour pouvoir être rappelé par g_timeout_add
gboolean next_turn(gpointer _game)
{
	t_game* game = (t_game*)_game;

	//si on est en mode réseau
	if(game->use_network)
	{
		//envoi de la position
		network_send(packet_make(NEW_POS,game->data.now)); //now est bien de type t_history*
		//lock du terrain
		game_lock(game,TRUE);
		//pas de vérification s'il y a fin de partie ou pas
		//c'est l'autre joueur qui le fera en recevant NEW_POS
	}
	//si on est en mode local
	else
	{
		//on n'échange pas l'animal du joueur devant jouer, c'est fait dans on_click
		//si le joueur en cours (on sait son animal) est humain (pas l'IA)
		if(current_player(game)->type == HUMAN)
		{	
			//on affiche que c'est son tour
			set_status_text("C'est au tour de %s de jouer.",current_player_name(game));
			//on le laisse jouer
		}
		//si c'est l'intelligence artificielle
		else
		{
			//on la fait jouer directement
			preIA(game,8);
			//on fait appeler une seconde plus tard next_turn pour faire jouer le joueur suivant 
			//ça laisse un délai si l'IA joue contre elle-même tour à tour
			g_timeout_add(1000,next_turn,game);
		}
	}
	//comme ça, g_timeout_add n'executera pas cette fonction plus d'une fois seulement
	return FALSE;
}

void make_movement(t_game *game,int x1,int y1,int x2,int y2)
{
    int i=0, type;
    gchar path[128];
    /** - détecter l'animal concerné\n
    */
    while(game->pawn[i].position.x != x1 || game->pawn[i].position.y != y1)
    {
        i++;
    }
    if(i==0) type = LAMB;
    else type = WOLF;
    /** - retirer l'image initiale de la case où se trouve l'animal\n
    */
    gtk_container_remove(GTK_CONTAINER(game->eventbox[x1][y1].eventbox),(GtkWidget*)gtk_container_get_children(GTK_CONTAINER(game->eventbox[x1][y1].eventbox))->data);
    /** - -> remettre l'image de fond\n
    */
    sprintf(path,"%s%s",PATH,"Bcase.BMP");
	gtk_container_add(GTK_CONTAINER(game->eventbox[x1][y1].eventbox),gtk_image_new_from_file(path));
	gtk_widget_show_all(game->eventbox[x1][y1].eventbox);
    /** - -> créer un historique du jeu\n
    */
	game_history_add(game);
	/** - -> modifier les positions dans les structures\n
	*/
    if(type == LAMB)
    {
        game->data.now->lamb.x = x2;
        game->data.now->lamb.y = y2;
    }
    else
    {
        game->data.now->wolf[i-1].x = x2;
        game->data.now->wolf[i-1].y = y2;
    }
    game->pawn[i].position.x = x2;
    game->pawn[i].position.y = y2;
    /** - -> superposer l'image de l'animal sur la nouvelle case\n
    */
	if(type == LAMB) sprintf(path,"%s%s",PATH,"lamb.BMP");
    else sprintf(path,"%s%s",PATH,"wolf.BMP");
	gtk_image_superimpose(game->eventbox[x2][y2].eventbox,path);
    afficher_console(game);
}

void onrelease(GtkWidget *emitter,GdkEventButton *event,t_game *game)
{
    int x,y,imgw,imgh;
    GdkPixbuf *pixbuf;
    gtk_widget_get_pointer(gtk_widget_get_parent(gtk_widget_get_parent(game->eventbox[0][0].eventbox)),&x,&y);
    y -= 24;
    pixbuf = gtk_image_get_pixbuf(GTK_IMAGE((GtkWidget*)(gtk_container_get_children(GTK_CONTAINER(game->eventbox[0][0].eventbox))->data)));
    imgw = gdk_pixbuf_get_width(pixbuf);
    imgh = gdk_pixbuf_get_height(pixbuf);
    x /= imgw;
    y /= imgh;
    if(game->data.orientation) y = 9 - y; 
    onclick(game->eventbox[x][y].eventbox,NULL,game);
}

void onclick(GtkWidget *emitter,GdkEventButton *event,t_game *game)
{
    /** récupère la position du click en fonction de l'eventbox émettrice du signal\n
	*/
    int i,j,k,pos;
    gchar path[128];
    int game_result;

    if(game_locked(game) == FALSE)
    {
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            if(emitter == game->eventbox[i][j].eventbox)
            {
				i+=10; j+=10;
            }
        }
    }
    i-=11; j-=11;
	/** - si la sélection n'est pas faite\n
	*/
	//si la partie est finie
	if(game_result = game_is_over(game->pawn))
	{
		//étude de qui a gagné
		switch(game_result)
		{
			//si l'agneau a gagné
			case 1:
				break;
			//si les loups on gagné
			case -1:
				//on met du sang sur toutes les colonnes
				/*for(i=0;i<10;i+=2)
				{
					for(j=0;j<10;j++)
					{
						gtk_container_remove(GTK_CONTAINER(game->eventbox[i+1-j%2][j].eventbox),(GtkWidget*)gtk_container_get_children(GTK_CONTAINER(game->eventbox[i+1-j%2][j].eventbox))->data);
					sprintf(path,"%s%s",PATH,"blood.BMP");
						gtk_container_add(GTK_CONTAINER(game->eventbox[i+1-j%2][j].eventbox),gtk_image_new_from_file(path));
						gtk_widget_show_all(game->eventbox[i+1-j%2][j].eventbox);
					}
				}*/
				break;
        	}
    }
    //si la sélection est vide
    else if(game->data.selection == NULL)
    {
        /** -# regarder si la position correspond au bon joueur au bon endroit\n
		*     -# si oui enregistrer la position\n
		*/
		for(k=0;k<6;k++)
        {
            if(game->pawn[k].position.x == i && game->pawn[k].position.y == j)
            {
                if(k == 0 && game->data.now->curplayer == LAMB) game->data.selection = &(game->eventbox[i][j]);
                if(k != 0 && game->data.now->curplayer == WOLF) game->data.selection = &(game->eventbox[i][j]);
            }
        }
    }
	/** - si la sélection est déjà faite\n
	*/
    //si la case demandée est la case qui était déjà sélectionnée
    else if(game->data.selection->eventbox == emitter)
    {
        // ne rien faire
    }
    //si la sélection n'est pas vide et qu'on a cliqué autre part que sur le pion sélectionné
    else
    {
        /**  - si c'est à l'agneau de jouer\n
		* - vérifier si le déplacement est possible\n
		* - si oui retirer l'image initiale de la case où se trouve l'agneau\n
		* - -> remettre l'image de fond\n
		* - -> créer un historique du jeu\n
		* - -> modifier les positions dans les structures\n
		* - -> superposer l'image de l'agneau sur la nouvelle case\n
		* - -> changer le joueur\n
		* - -> appel du gestionnaire de tours\n
		*/
		if(game->data.now->curplayer == LAMB)
        {
            if((i == game->pawn[0].position.x+1 || i == game->pawn[0].position.x-1)&&(j == game->pawn[0].position.y+1 || j == game->pawn[0].position.y-1))
            {
                for(k=0;k<6;k++)
                    if(game->pawn[k].position.x == i && game->pawn[k].position.y == j) game->data.selection = NULL;
            }
            else game->data.selection = NULL;
            if(game->data.selection != NULL)
            {
                gtk_container_remove(GTK_CONTAINER(game->data.selection->eventbox),(GtkWidget*)gtk_container_get_children(GTK_CONTAINER(game->data.selection->eventbox))->data);
			    if((i+j)%2==0) sprintf(path,"%s%s",PATH,"Bcase.BMP");
					else sprintf(path,"%s%s",PATH,"Ncase.BMP");
			    gtk_container_add(GTK_CONTAINER(game->data.selection->eventbox),gtk_image_new_from_file(path));
			    gtk_widget_show_all(game->data.selection->eventbox);
			    game_history_add(game);
                game->data.now->lamb.x = i;
                game->data.now->lamb.y = j;
                game->pawn[0].position.x = i;
                game->pawn[0].position.y = j;
                game->data.selection = NULL;
                sprintf(path,"%s%s",PATH,"lamb.BMP");
	            gtk_image_superimpose(game->eventbox[game->data.now->lamb.x][game->data.now->lamb.y].eventbox,path);
                game->data.now->curplayer = WOLF;
		afficher_console(game);
                // => appel du next_turn
		g_timeout_add(500,next_turn,game); // un semblant de temps pour que l'IA n'enchaîne pas directement
            }
        }
        else
        {
            /**  - si c'est aux loups de jouer\n
			* -# trouver le loup correspondant\n
			* -# vérifier si le déplacement est possible\n
			* -# si oui retirer l'image initiale de la case où se trouve le loup\n
			* -# -> remettre l'image de fond\n
			* -# -> créer un historique du jeu\n
			* -# -> modifier les positions dans les structures\n
			* -# -> superposer l'image du loup sur la nouvelle case\n
			* -# -> changer le joueur\n
			* -# -> appel du gestionnaire de tours\n
			*/
			for(k=1;k<6;k++)
                if(game->pawn[k].position.x == game->data.selection->position.x && game->pawn[k].position.y == game->data.selection->position.y)
                    k+=9;
            pos = k-10;
            if((i == game->pawn[pos].position.x+1 || i == game->pawn[pos].position.x-1)&&(j == game->pawn[pos].position.y-1))
            {
                for(k=0;k<6;k++)
                    if(game->pawn[k].position.x == i && game->pawn[k].position.y == j) game->data.selection = NULL;
            }
            else game->data.selection = NULL;
            if(game->data.selection != NULL)
            {
                gtk_container_remove(GTK_CONTAINER(game->data.selection->eventbox),(GtkWidget*)gtk_container_get_children(GTK_CONTAINER(game->data.selection->eventbox))->data);
                sprintf(path,"%s%s",PATH,"Bcase.BMP");
			    gtk_container_add(GTK_CONTAINER(game->data.selection->eventbox),gtk_image_new_from_file(path));
			    gtk_widget_show_all(game->data.selection->eventbox);
			    game_history_add(game);
                game->data.now->wolf[pos-1].x = i;
                game->data.now->wolf[pos-1].y = j;
                game->pawn[pos].position.x = i;
                game->pawn[pos].position.y = j;
                game->data.selection = NULL;
                sprintf(path,"%s%s",PATH,"wolf.BMP");
	            gtk_image_superimpose(game->eventbox[game->data.now->wolf[pos-1].x][game->data.now->wolf[pos-1].y].eventbox,path);
				game->data.now->curplayer = LAMB;
                afficher_console(game);
		// => appel du next_turn
		g_timeout_add(500,next_turn,game); // un semblant de temps pour que l'IA n'enchaîne pas directement
            }
		}
    }
    }//fin du if(game_locked(game))
}
