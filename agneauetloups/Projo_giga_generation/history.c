#include "main.h"

int game_history_add(t_game *game)
{
	int i;
	/** - création d'une nouvelle structure d'historique\n
	*/
	t_history *newhistory=NULL;
	newhistory = (t_history*) malloc(sizeof(t_history));
	if(newhistory == NULL) return ERR_ALLOC_HISTORY;
	/** - stockage de la structure dans un liste\n
	*/
	game->data.history = g_list_append (game->data.history,newhistory);
	/** - enregistrement des paramètres de la partie\n
	*/
	/** -# pour l'agneau\n
	* -# pour les loups\n
	* -# pour le joueur en cours\n
	*/
	newhistory->lamb.x = game->data.now->lamb.x;
	newhistory->lamb.y = game->data.now->lamb.y;
	for(i=0;i<5;i++)
	{
		newhistory->wolf[i].x = game->data.now->wolf[i].x;
		newhistory->wolf[i].y = game->data.now->wolf[i].y;
	}
	newhistory->curplayer = game->data.now->curplayer;
	return SUCCESS;
}

void game_history_back(t_game *game, int back)
{
	int i,j,x,y;system("CLS");
	gchar path[128];
	/** si l'historique correspond à la valeur de retour voulue\n
	*/
	if(g_list_length(game->data.history) >= back)
	{
		/** - si l'agneau a bougé\n
		* -# détruire l'image sur l'emplacement actuel\n
		* -# y charger l'image du terrain\n
		* -# détruire l'image sur le nouvel emplacement\n
		* -# y charger l'image du terrain\n
		* -# y superposer l'image de l'agneau\n
		*/
		x = ((t_history*)g_list_nth_data(game->data.history, g_list_length(game->data.history)-back))->lamb.x;
		y = ((t_history*)g_list_nth_data(game->data.history, g_list_length(game->data.history)-back))->lamb.y;
		if(game->data.now->lamb.x != x || game->data.now->lamb.y != y)
		{
			gtk_container_remove(GTK_CONTAINER(game->eventbox[game->data.now->lamb.x][game->data.now->lamb.y].eventbox),(GtkWidget*)(gtk_container_get_children(GTK_CONTAINER(game->eventbox[game->data.now->lamb.x][game->data.now->lamb.y].eventbox)))->data);
            sprintf(path,"%s%s",PATH,"Bcase.BMP");
			gtk_container_add(GTK_CONTAINER(game->eventbox[game->data.now->lamb.x][game->data.now->lamb.y].eventbox),gtk_image_new_from_file(path));
			gtk_widget_show_all(game->eventbox[game->data.now->lamb.x][game->data.now->lamb.y].eventbox);
			gtk_container_remove(GTK_CONTAINER(game->eventbox[x][y].eventbox),(GtkWidget*)gtk_container_get_children(GTK_CONTAINER(game->eventbox[x][y].eventbox))->data);
			sprintf(path,"%s%s",PATH,"Bcase.BMP");
			gtk_container_add(GTK_CONTAINER(game->eventbox[x][y].eventbox),gtk_image_new_from_file(path));
			sprintf(path,"%s%s",PATH,"lamb.BMP");
			gtk_image_superimpose(game->eventbox[x][y].eventbox,path);
			gtk_widget_show_all(game->eventbox[x][y].eventbox);
		}
		/** - pour chaque loup, si il a bougé\n
		* -# détruire l'image sur l'emplacement actuel\n
		* -# y charger l'image du terrain\n
		* -# détruire l'image sur le nouvel emplacement\n
		* -# y charger l'image du terrain\n
		* -# y superposer l'image du loup\n
		*/
		for(i=0;i<5;i++)
		{
			x = ((t_history*)g_list_nth_data(game->data.history, g_list_length(game->data.history)-back))->wolf[i].x;
			y = ((t_history*)g_list_nth_data(game->data.history, g_list_length(game->data.history)-back))->wolf[i].y;
			if(game->data.now->wolf[i].x != x || game->data.now->wolf[i].y != y)
			{
				gtk_container_remove(GTK_CONTAINER(game->eventbox[game->data.now->wolf[i].x][game->data.now->wolf[i].y].eventbox),(GtkWidget*)gtk_container_get_children(GTK_CONTAINER(game->eventbox[game->data.now->wolf[i].x][game->data.now->wolf[i].y].eventbox))->data);
				sprintf(path,"%s%s",PATH,"Bcase.BMP");
				gtk_container_add(GTK_CONTAINER(game->eventbox[game->data.now->wolf[i].x][game->data.now->wolf[i].y].eventbox),gtk_image_new_from_file(path));
				gtk_widget_show_all(game->eventbox[game->data.now->wolf[i].x][game->data.now->wolf[i].y].eventbox);
				gtk_container_remove(GTK_CONTAINER(game->eventbox[x][y].eventbox),(GtkWidget*)gtk_container_get_children(GTK_CONTAINER(game->eventbox[x][y].eventbox))->data);
				sprintf(path,"%s%s",PATH,"Bcase.BMP");
				gtk_container_add(GTK_CONTAINER(game->eventbox[x][y].eventbox),gtk_image_new_from_file(path));
				gtk_widget_show_all(game->eventbox[x][y].eventbox);
				sprintf(path,"%s%s",PATH,"wolf.BMP");
				gtk_image_superimpose(game->eventbox[x][y].eventbox,path);
			}
		}
		/** - libérer la mémoire de l'ancien terrain\n
		*/
		free(game->data.now);
		/** - définir le nouveau terrain a partir de l'historique\n
		*/
		game->data.now = (t_history*)g_list_nth_data(game->data.history, g_list_length(game->data.history)-back);
		/** - supprimer les historiques qui ont été sautés\n
		*/
		while((t_history*)g_list_nth_data(game->data.history,g_list_length(game->data.history)-1) != game->data.now)
		{
			free(g_list_nth_data(game->data.history,g_list_length(game->data.history)-1));
			game->data.history = g_list_remove(game->data.history,g_list_nth_data(game->data.history,g_list_length(game->data.history)-1));
		}
		game->data.history = g_list_remove(game->data.history,g_list_nth_data(game->data.history,g_list_length(game->data.history)-1));
		/** - mettre à jours l'accès rapide aux coordonnées (game->pawn[6])
		*/
		game->pawn[0].position.x = game->data.now->lamb.x;
		game->pawn[0].position.y = game->data.now->lamb.y;
		for(i=1;i<6;i++)
		{
            game->pawn[i].position.x = game->data.now->wolf[i-1].x;
		    game->pawn[i].position.y = game->data.now->wolf[i-1].y;
        }
	}
}
