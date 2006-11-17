#ifndef GAMEC
#define GAMEC

#include "[DOX]main.h"

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
    if(game->data.selection == NULL)
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
                strcpy(path,PATH);
			    if((i+j)%2==0) strcat(path,"Bcase.BMP");
					else strcat(path,"Ncase.BMP");
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
                strcpy(path,PATH);
	            strcat(path,"wolf.BMP");
                gtk_image_superimpose(game->eventbox[game->data.now->wolf[pos-1].x][game->data.now->wolf[pos-1].y].eventbox,path);
				game->data.now->curplayer = LAMB;
                // => appel du next_turn
                afficher_console(game);
            }
		}
    }
}

#endif
