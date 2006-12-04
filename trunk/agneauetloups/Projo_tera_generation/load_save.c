#include "main.h"

void go_load(GtkWidget *emitter, gpointer null)
{
	char path[128];
	sprintf(path,"%ssave.ece",PATH);
	/*if(GAME != NULL)
	{
		while((*GAME)->data.history != NULL) game_history_back(*GAME,1);
		free((*GAME)->data.now);
		free((*GAME)->data.selection);
		free((*GAME)->data.player[1]);
		free((*GAME)->data.player[2]);
		free((*GAME)->data.player);
		free((*GAME)->wintheme);
		free(*GAME);
	}*/
	load_game(GAME,gtk_widget_get_parent((*GAME)->eventbox[0][0].eventbox),path);
}

void go_save(GtkWidget *emitter, gpointer null)
{
	save_game(*GAME,"save.ece");
}

void load_game(t_game **gameadress,GtkWidget *table,char *path)
{
    FILE *fp;
    int i;
	t_game *game=*gameadress;
	char buffer[128],*player1name,*player2name;
	t_player joueur[2];
	gboolean orientation;
	t_coords selection;
	t_history *newhistory;
	char path2[128];
	int historynb;
	if(fp=fopen(path,"rb"))
    {                	
        fread(joueur,sizeof(t_player),2,fp);
		fread(&orientation,sizeof(gboolean),1,fp);
		i=-1;
		do
		{
            i++;
            buffer[i] = (char)getc(fp);
        }while(buffer[i] != '\0');
		player1name = (char*)malloc((strlen(buffer)+1)*sizeof(char));
		strcpy(player1name,buffer);
		i=0;
		do
		{
            buffer[i++] = getc(fp);
        }while(buffer[i-1] != '\0');
		player2name = (char*)malloc((strlen(buffer)+1)*sizeof(char));
		strcpy(player2name,buffer);
		fread(&selection,sizeof(t_coords),1,fp);
		game_init(gameadress,table,player1name,joueur[0].type,joueur[0].animal,player2name,joueur[1].type,joueur[1].animal);
		game=*gameadress;
		
		fread(game->data.now,sizeof(t_history),1,fp);
		fread(&historynb,sizeof(int),1,fp);
		for(i=0;i<historynb-1;i++)
		{
			newhistory = (t_history*)malloc(sizeof(t_history));
            fread(newhistory,sizeof(t_history),1,fp);
			game->data.history = g_list_append(game->data.history,newhistory);
        }
        fclose(fp);
		game->pawn[0].position.x = game->data.now->lamb.x;
		game->pawn[0].position.y = game->data.now->lamb.y;
		game->pawn[0].eventbox = game->eventbox[game->data.now->lamb.x][game->data.now->lamb.y].eventbox;
		for(i=1;i<6;i++)
		{
			game->pawn[i].position.x = game->data.now->wolf[i-1].x;
			game->pawn[i].position.y = game->data.now->wolf[i-1].y;
			game->pawn[i].eventbox = game->eventbox[game->data.now->wolf[i-1].x][game->data.now->wolf[i-1].y].eventbox;
		}
		/** - chargement des images des pions\n
	    */
	    for(i=0;i<100;i++)
	    {
            if((abs(9*game->data.orientation - i%10)+abs(9*game->data.orientation - i/10))%2==0) sprintf(path2,"%s%s",PATH,"Bcase.BMP");
			else sprintf(path2,"%s%s",PATH,"Ncase.BMP");
			gtk_container_remove(GTK_CONTAINER(game->eventbox[i%10][i/10].eventbox),(GtkWidget*)gtk_container_get_children(GTK_CONTAINER(game->eventbox[i%10][i/10].eventbox))->data);
			gtk_container_add(GTK_CONTAINER(game->eventbox[i%10][i/10].eventbox),gtk_image_new_from_file(path2));
		}
	    sprintf(path2,"%s%s",PATH,"lamb.BMP");
	    gtk_image_superimpose(game->eventbox[game->data.now->lamb.x][game->data.now->lamb.y].eventbox,path2);
	    sprintf(path2,"%s%s",PATH,"wolf.BMP");
	    for(i=0;i<5;i++)
	    {
		    gtk_image_superimpose(game->eventbox[game->data.now->wolf[i].x][game->data.now->wolf[i].y].eventbox,path2);
        }
	}
}

int save_game(t_game *game, char *path)
{
	int count,whennull = -1,i;
	FILE *fp;
	//GList *save = game->data.history;
	if(fp=fopen(path,"wb"))
	{
		fwrite(&(game->players),sizeof(t_player),2,fp);
		fwrite(&(game->data.orientation),sizeof(gboolean),1,fp);
		fwrite(game->data.player[0],sizeof(char),strlen(game->data.player[0])+1,fp);
		fwrite(game->data.player[1],sizeof(char),strlen(game->data.player[1])+1,fp);
		if(game->data.selection == NULL)
		{
			fwrite(&whennull,sizeof(int),1,fp);
			fwrite(&whennull,sizeof(int),1,fp);
		}
		else
		{
			fwrite(&(game->data.selection->position),sizeof(t_coords),1,fp);
		}
        fwrite(game->data.now,sizeof(t_history),1,fp);
		count = g_list_length(game->data.history);
		fwrite(&count,sizeof(int),1,fp);
		for(i=1;i<count;i++)
		{
			fwrite(g_list_nth_data(game->data.history,i-1),sizeof(t_history),1,fp);
		}
		fclose(fp);
	}
	else return ERR_WRITING_SAVE;
	return SUCCESS;
}
