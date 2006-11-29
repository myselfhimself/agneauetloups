#include "main.h"

GtkWidget *window_init(GtkWidget **win)
{
	GtkWidget *table,*VBox,*MenuBar;
	GtkItemFactory *ItemFactory;
    GtkAccelGroup *Accel;
	GtkItemFactoryEntry MenuItem[] = {
    { "/_Partie", NULL, NULL, 0, "<Branch>" },
    { "/Partie/_Nouvelle Partie", NULL, NULL, 0, "<StockItem>", GTK_STOCK_NEW },
    { "/Partie/Charger Partie", "<ctrl>C", NULL, 0, "<StockItem>", GTK_STOCK_REFRESH },
    { "/Partie/Enregi_strer Partie", "<ctrl>S", NULL, 0, "<StockItem>", GTK_STOCK_SAVE },
    { "/Partie/Sep1", NULL, NULL, 0, "<Separator>" },
    { "/Partie/_Quitter", NULL, onquit, 1, "<StockItem>", GTK_STOCK_QUIT},
    { "/_Configuration", NULL, NULL, 0, "<Branch>" },
    { "/Configuration/_Choix du Theme","<ctrl>T", NULL, 0, "<StockItem>", GTK_STOCK_CLEAR },
    { "/Configuration/_Niveau de Difficulte","<ctrl>D", NULL, 0, "<StockItem>", GTK_STOCK_PREFERENCES },
    { "/_?", NULL, NULL, 0, "<Branch>" },
    { "/?/_A propos de...", "<CTRL>A", onabout, 1, "<StockItem>", GTK_STOCK_HELP}};
	/** - création de la fenetre\n
	*/
	*win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(*win),0);
	gtk_window_set_title(GTK_WINDOW(*win),"Projo giga generation");
	gtk_window_set_position(GTK_WINDOW(*win),GTK_WIN_POS_CENTER);
	gtk_widget_realize(*win);
	g_signal_connect(*win,"destroy",gtk_main_quit,NULL);
	/** - création de la table 10*10\n
	*/
    if((table = gtk_table_new(10,10,TRUE))==NULL) return NULL;
	/** - création du menu\n
	*/
	Accel = gtk_accel_group_new ();
	ItemFactory = gtk_item_factory_new(GTK_TYPE_MENU_BAR,"<main>",Accel);
	gtk_item_factory_create_items(ItemFactory,11,MenuItem,*win);
	MenuBar = gtk_item_factory_get_widget(ItemFactory,"<main>");
	gtk_window_add_accel_group(GTK_WINDOW(*win),Accel);
	/** - création d'une vertical box\n
	*/
    VBox = gtk_vbox_new(FALSE, 0);
    /** - ajout de la vertical box a la fenetre\n
	*/
    gtk_container_add(GTK_CONTAINER(*win),VBox);
    /** - ajout du menu et de la table dans la vertical box\n
	*/
	gtk_box_pack_start(GTK_BOX(VBox),MenuBar,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(VBox),table,FALSE,FALSE,0);
	/** - affichage de tout les éléments de la fenetre\n
	*/
	gtk_widget_show_all(*win);
	/** - retour de la table\n
	*/
    return table;
}

int game_init(t_game **game,GtkWidget *table,char *player1name,gboolean player1type,gboolean player1animal,char *player2name,gboolean player2type,gboolean player2animal)
 {
	int i,j;
    t_game *thegame = NULL;
	gchar path[128];
	/** - création de la structure principale\n
	*/
	thegame = (t_game *) malloc(sizeof(t_game));
	if(thegame == NULL) return ERR_ALLOC_GAME;
	*game = thegame;
	
    /** - initialisation des joueurs\n
	*/
	thegame->players[0].type = player1type;
	thegame->players[0].animal = player1animal;
	thegame->players[1].type = player2type;
	thegame->players[1].animal = player2animal;
	if(player1animal == player2animal) return ERR_COMPATIBILITY;
	
	/** - initialisation du terrain\n
	* -# création des eventbox
	* -# chargement des images
	*/
	thegame->data.orientation = (player1animal == LAMB);
	for(j=0;j<10;j++)
	{
		for(i=0;i<10;i++)
		{
			if((thegame->eventbox[i][j].eventbox = gtk_event_box_new())==NULL) return ERR_ALLOC_EVENTBOX;
			gtk_table_attach_defaults(GTK_TABLE(table),thegame->eventbox[i][j].eventbox,i,i+1,abs(9*thegame->data.orientation - j),abs(9*thegame->data.orientation - j)+1);
			gtk_signal_connect(GTK_OBJECT(thegame->eventbox[i][j].eventbox), "button_press_event", GTK_SIGNAL_FUNC(onclick),thegame);
			gtk_signal_connect(GTK_OBJECT(thegame->eventbox[i][j].eventbox), "button_release_event", GTK_SIGNAL_FUNC(onrelease),thegame);
			thegame->eventbox[i][j].position.x = i;
			thegame->eventbox[i][j].position.y = j;
			if((abs(9*thegame->data.orientation - i)+abs(9*thegame->data.orientation - j))%2==0) sprintf(path,"%s%s",PATH,"Bcase.BMP");
			else sprintf(path,"%s%s",PATH,"Ncase.BMP");
			gtk_container_add(GTK_CONTAINER(thegame->eventbox[i][j].eventbox),gtk_image_new_from_file(path));
		}
	}
	
	/** - initialisation de l'historique\n
	*/
	if((thegame->data.now = (t_history*) malloc(sizeof(t_history)))==NULL) return ERR_ALLOC_NOW;
	thegame->data.history = NULL;
	/** - initialisation de la selection\n
	*/
    thegame->data.selection = NULL;
    /** - mémorisation du nom des joueurs\n
	*/
	if((thegame->data.player[0] = (char*) malloc((strlen(player1name)+1)*sizeof(char))) == NULL) return ERR_ALLOC_NAME1;
	strcpy(thegame->data.player[0],player1name);
	if((thegame->data.player[1] = (char*) malloc((strlen(player2name)+1)*sizeof(char))) == NULL) return ERR_ALLOC_NAME2;
	strcpy(thegame->data.player[1],player2name);
	
	/** - initialisation des coordonnées des pions\n
	*/
	thegame->data.now->lamb.x = 4;
	thegame->data.now->lamb.y = 0;
	for(i=0;i<5;i++)
	{
		thegame->data.now->wolf[i].x = 2*i + 1;
		thegame->data.now->wolf[i].y = 9;
	}
	/** - initialisation du premier joueur\n
	*/
	thegame->data.now->curplayer = player1animal;
	
	/** - initialisation des coordonnées des pions (accès rapide)\n
	*/
	thegame->pawn[0].position.x = thegame->data.now->lamb.x;
	thegame->pawn[0].position.y = thegame->data.now->lamb.y;
	thegame->pawn[0].eventbox = thegame->eventbox[thegame->data.now->lamb.x][thegame->data.now->lamb.y].eventbox;
	/** - chargement des images des pions\n
	*/
	sprintf(path,"%s%s",PATH,"lamb.BMP");
	gtk_image_superimpose(thegame->eventbox[thegame->data.now->lamb.x][thegame->data.now->lamb.y].eventbox,path);
	sprintf(path,"%s%s",PATH,"wolf.BMP");
	for(i=0;i<5;i++)
	{
		thegame->pawn[i+1].position.x = thegame->data.now->wolf[i].x;
		thegame->pawn[i+1].position.y = thegame->data.now->wolf[i].y;
		thegame->pawn[i+1].eventbox = thegame->eventbox[thegame->data.now->wolf[i].x][thegame->data.now->wolf[i].x].eventbox;
		gtk_image_superimpose(thegame->eventbox[thegame->data.now->wolf[i].x][thegame->data.now->wolf[i].y].eventbox,path);
	}
	return SUCCESS;
}
