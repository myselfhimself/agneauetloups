#include "main.h"

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

void onclick(GtkWidget *emitter,GdkEventButton *event,t_game *game)
{
    /** récupère la position du click en fonction de l'eventbox émettrice du signal\n
	*/
    int i,j,k,pos;
    gchar path[128];
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
	if(game_is_over(game->pawn))
	{
        /*if(wolves_won(game->pawn))
        {
            for(i=0;i<10;i+=2)
            {
                for(j=0;j<10;j++)
                {
                    gtk_container_remove(GTK_CONTAINER(game->eventbox[i+1-j%2][j].eventbox),(GtkWidget*)gtk_container_get_children(GTK_CONTAINER(game->eventbox[i+1-j%2][j].eventbox))->data);
                    sprintf(path,"%s%s",PATH,"blood.BMP");
	                gtk_container_add(GTK_CONTAINER(game->eventbox[i+1-j%2][j].eventbox),gtk_image_new_from_file(path));
	                gtk_widget_show_all(game->eventbox[i+1-j%2][j].eventbox);
                }
			}
        }*/
    }
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
                // => appel du next_turn
                afficher_console(game);
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
                // => appel du next_turn
                afficher_console(game);
            }
		}
    }
}
