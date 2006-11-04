#include "projet.h"

//---------------INITIALISATION----DES-----FENETRES------------------

void interface_make(t_tout* tout)
{
	GtkWidget* pWindow;
	GtkWidget* pVbox;
	GtkWidget* status_bar;
	
	//fenetre
	pWindow = interface_make_window();
	
	//vBox
	pVbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(pWindow),GTK_WIDGET(pVbox));
	
	//boutons
	interface_make_table_and_buttons_attach_and_link_them(pVbox,tout);

	//barre status
	status_bar = gtk_statusbar_new();
	gtk_box_pack_start(GTK_BOX(pVbox),status_bar,FALSE,FALSE,0);
	tout->status_bar = status_bar;

	//menu
	tout->menu = NULL;

	//affichage du tout	
	gtk_widget_show_all(pWindow);
	
}

//cree la fenetre vide configuree et la retourne. Fonction ecrite pour alleger interface_make qui l'utilise
GtkWidget* interface_make_window()
{
	GtkWidget* pWindow;
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(pWindow),300,300);
	gtk_window_set_position(GTK_WINDOW(pWindow),GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(pWindow),"titre");
	g_signal_connect(G_OBJECT(pWindow),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	return pWindow;
}

//cree une table et la lie au pointeur de vbox donne
//cree les boutons, crees les structures devant englober les boutons, attache a la table, attache a 'tout'
void interface_make_table_and_buttons_attach_and_link_them(GtkWidget* pVbox,t_tout* tout)
{
	int x,y;
	GtkWidget* pTable;

	//table
	pTable = gtk_table_new(10,10,TRUE);
	
	//insertion dans vbox
	gtk_box_pack_start(GTK_BOX(pVbox),pTable,TRUE,TRUE,0);

	//creer boutons
	//et attacher dans la table
	
	//pour chaque ligne
	for(y=0;y<10;y++)
	{
		//pour chaque colonne
		for(x=0;x<10;x++)
		{
			tout->positions[x][y].bouton = gtk_button_new_with_label(" ");
			gtk_button_set_label(GTK_BUTTON(tout->positions[x][y].bouton),"prout");
			gtk_table_attach_defaults(GTK_TABLE(pTable),tout->positions[x][y].bouton,x,x+1,y,y+1);
			tout->positions[x][y].main_type = (x%2==0) ? TERRAIN : NONE;
			tout->positions[x][y].forced_type = NONE;
		}
	}
}

//---------------------MISE--A--JOUR----DU----JEU---------

//enleve toutes les informations de pions sur les cases du jeu sans mettre a jour l'affichage
void interface_clear_players(t_tout* tout)
{
	int x;
	int y;

	for(x=0;x<10;x++) for(y=0;y<10;y++)
		tout->positions[x][y].forced_type = NONE;
}

//change l'affichage de tout le plateau selon l'element t_history nomme tout->data.now
//une fonction interface_redraw_button est en fait appelee pour chaque bouton
//remarque : ici on ne se soucie pas de savoir a qui appartiennent les differents pions
void interface_redraw_positions(t_tout* tout)
{
	int x;
	int y;
	t_coords temp_pos;
	t_position temp_case;
	GtkWidget* temp_btn;

	//on enleve toute trace des pions sur le jeu
	interface_clear_players(tout);
	
	//on accede aux differents boutons dont les coordonees figurent dans le t_history "now"
	//on ecrit la trace des differents pions
	//on change l'aspect du bouton correspondant en consequence
	
	//LOUPS
	//x n'est qu'un simple iterateur ici
	for(x=0;x<5;x++)
	{
		temp_pos = tout->data.now.loups[x];
		temp_case = *memory_get_pos_from_coords(temp_pos,tout);
		temp_case.forced_type = WOLF;
	}

	//AGNEAU
	temp_pos = tout->data.now.agneau;
	temp_case = *memory_get_pos_from_coords(temp_pos,tout);
	temp_case.forced_type = LAMB;

	for(x=0;x<10;x++) for(y=0;y<10;y++)
		interface_redraw_button(tout->positions[x][y]);
}

//change l'aspect d'un bouton selon les types d'affichage precises dans l'element t_position donne
void interface_redraw_button(t_position position)
{
	//le widget
	GtkWidget* bouton=NULL;
	//l'identifiant d'aspect que devra prendre le widget
	int type_affichage;

	//Differents aspects :
	//le texte a mettre dans le bouton
	char* pion_normal = " ";
	char* pion_selectionne = "[ ]";

	//initialisations
	//recuperation des informations necessaires pour travailler sur le bouton
	bouton = position.bouton;
	type_affichage = (position.forced_type == NONE) ? position.main_type : position.forced_type;
	
	switch(type_affichage)
	{
		case NONE:
			pion_normal[0] = '#';
			break;
		case TERRAIN:
			pion_normal[0] = ' '; //pas de changement en fait
			break;
		case LAMB:
			pion_normal[0] = 'A';
			break;
		case WOLF:
			pion_normal[0] = 'L';
			break;
		case LAMB_SELECTED:
			pion_selectionne[1] = 'A';
			break;
		case WOLF_SELECTED:
			pion_selectionne[1] = 'L';
			break;
		default:
			printf("interface_redraw_button : switch : missed a constant");
	}
	
	if(type_affichage != LAMB_SELECTED && type_affichage != WOLF_SELECTED)
		gtk_button_set_label(GTK_BUTTON(position.bouton),pion_normal);
	else
		gtk_button_set_label(GTK_BUTTON(position.bouton),pion_selectionne);	
}