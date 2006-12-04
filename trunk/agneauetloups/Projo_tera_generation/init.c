#include "main.h"
#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)



GtkWidget*
lookup_widget                          (GtkWidget       *widget,
                                        const gchar     *widget_name)
{
  GtkWidget *parent, *found_widget;

  for (;;)
    {
      if (GTK_IS_MENU (widget))
        parent = gtk_menu_get_attach_widget (GTK_MENU (widget));
      else
        parent = widget->parent;
      if (!parent)
        parent = (GtkWidget*) g_object_get_data (G_OBJECT (widget), "GladeParentKey");
      if (parent == NULL)
        break;
      widget = parent;
    }

  found_widget = (GtkWidget*) g_object_get_data (G_OBJECT (widget),
                                                 widget_name);
  if (!found_widget)
    g_warning ("Widget not found: %s", widget_name);
  return found_widget;
}

int is_empty_string(gchar* str)
{
	int a;
	int nb_empty=0;
	int len;
	int result;
	GString* pt;

	result = str == NULL;
	len = g_utf8_strlen(str,300);

	if(!result)
	{
		for(a=0;a<len;a++)
			if(g_ascii_isspace(str[a]))
				nb_empty ++;
		
		printf("nb empty : %d, strlen : %d\n",nb_empty,len);
		result = nb_empty == len;
	}
	else printf("pointer is null\n");
	printf("is empty : %d\n",result);
	return result;
}

void game_initter(GtkWidget* emitter, GtkWidget* dialog)
{
	GtkWidget* table;
	char* nom_agneau;
	char* nom_loups;
	int agneau_is_ordi;
	int loups_is_ordi;
	int agneau_starts_bottom;
	int agneau;
	int loup;
	char* first_player;
	char* second_player;
	int first_type;
	int second_type;
	int first_animal;
	int second_animal;
	int do_run=1;
	
	table = ((*GAME)->eventbox)[0]->eventbox; //type GtkWidget*
	nom_agneau = gtk_entry_get_text(GTK_ENTRY(lookup_widget(dialog,"nom_agneau")));
	nom_loups = gtk_entry_get_text(GTK_ENTRY(lookup_widget(dialog,"nom_loups")));
	agneau_is_ordi = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(lookup_widget(dialog,"agneau_radio_ordi")));
	loups_is_ordi = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(lookup_widget(dialog,"loups_radio_ordi")));
	agneau_starts_bottom = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(lookup_widget(dialog,"pos_agneau_bas")));
	agneau = agneau_is_ordi ? ARTIFICIAL : HUMAN;
	loup = loups_is_ordi ? ARTIFICIAL : HUMAN;
	first_player = agneau_starts_bottom ? nom_agneau : nom_loups;
	second_player = agneau_starts_bottom ? nom_loups : nom_agneau;
	first_type = agneau_starts_bottom ? agneau : loup;
	second_type = agneau_starts_bottom ? loup : agneau;
	first_animal = agneau_starts_bottom ? LAMB : WOLF;
	second_animal = agneau_starts_bottom ? WOLF : LAMB;

	hide_nouvelle_partie(NULL,dialog);
	/*if(agneau == HUMAN)
		do_run = !is_empty_string(nom_agneau);
	if(loup == HUMAN)
		do_run = !is_empty_string(nom_loups);*/
	if(do_run)
	{
		printf("np\n");
		//le premier joueur des paramètres est en bas et c'est lui qui joue en premier
		game_init(GAME,table,g_strdup(first_player),first_type,first_animal,g_strdup(second_player),second_type,second_animal);
	}
	else
		printf("nothing done\n");
}

void
on_agneau_radio_ordi_toggled           (gpointer         user_data,
                                        GtkToggleButton *togglebutton)
{
gtk_widget_set_sensitive((GtkWidget*)user_data,gtk_toggle_button_get_active(togglebutton) ? FALSE : TRUE);
}


void
on_loups_radio_ordi_toggled            (gpointer         user_data,
                                        GtkToggleButton *togglebutton)
{
gtk_widget_set_sensitive((GtkWidget*)user_data,gtk_toggle_button_get_active(togglebutton) ? FALSE : TRUE);
}


void
on_loups_radio_joueur_toggled          (gpointer         user_data,
                                        GtkToggleButton *togglebutton)
{
gtk_widget_set_sensitive((GtkWidget*)user_data,gtk_toggle_button_get_active(togglebutton) ? TRUE : FALSE);
}


void
on_agneau_radio_joueur_toggled         (gpointer         user_data,
                                        GtkToggleButton *togglebutton)
{
gtk_widget_set_sensitive((GtkWidget*)user_data,gtk_toggle_button_get_active(togglebutton) ? TRUE : FALSE);
}

GtkWidget*
create_jeusimple (void)
{
  GtkWidget *jeusimple;
  GtkWidget *dialog_vbox2;
  GtkWidget *fixed3;
  GtkWidget *nom_agneau_box;
  GtkWidget *label14;
  GtkWidget *nom_agneau;
  GtkWidget *nom_loups_box;
  GtkWidget *label22;
  GtkWidget *nom_loups;
  GtkWidget *label15;
  GtkWidget *label16;
  GtkWidget *label13;
  GtkWidget *label24;
  GtkWidget *label23;
  GtkWidget *pos_agneau_bas;
  GSList *pos_agneau_bas_group = NULL;
  GtkWidget *agneau_radio_ordi;
  GSList *agneau_radio_ordi_group = NULL;
  GtkWidget *loups_radio_ordi;
  GSList *loups_radio_ordi_group = NULL;
  GtkWidget *pos_agneau_haut;
  GtkWidget *loups_radio_joueur;
  GtkWidget *agneau_radio_joueur;
  GtkWidget *dialog_action_area2;
  GtkWidget *cancelbutton2;
  GtkWidget *alignment9;
  GtkWidget *hbox9;
  GtkWidget *image63;
  GtkWidget *label19;
  GtkWidget *okbutton2;
  GtkWidget *alignment8;
  GtkWidget *hbox8;
  GtkWidget *image62;
  GtkWidget *label18;

  jeusimple = gtk_dialog_new ();
  gtk_window_set_title (GTK_WINDOW (jeusimple), "Partie un ou deux joueurs");
  gtk_window_set_icon_name (GTK_WINDOW (jeusimple), "gtk-dialog-info");
  gtk_window_set_type_hint (GTK_WINDOW (jeusimple), GDK_WINDOW_TYPE_HINT_DIALOG);
  gtk_window_set_modal (GTK_WINDOW(jeusimple),TRUE);

  dialog_vbox2 = GTK_DIALOG (jeusimple)->vbox;
  gtk_widget_show (dialog_vbox2);
  gtk_widget_set_size_request (dialog_vbox2, 333, 372);

  fixed3 = gtk_fixed_new ();
  gtk_widget_show (fixed3);
  gtk_box_pack_start (GTK_BOX (dialog_vbox2), fixed3, TRUE, TRUE, 0);

  nom_agneau_box = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (nom_agneau_box);
  gtk_fixed_put (GTK_FIXED (fixed3), nom_agneau_box, 77, 85);
  gtk_widget_set_size_request (nom_agneau_box, 32, 16);

  label14 = gtk_label_new ("Surnom :");
  gtk_widget_show (label14);
  gtk_box_pack_start (GTK_BOX (nom_agneau_box), label14, FALSE, FALSE, 0);
  gtk_widget_set_size_request (label14, 64, 16);

  nom_agneau = gtk_entry_new ();
  gtk_widget_show (nom_agneau);
  gtk_box_pack_start (GTK_BOX (nom_agneau_box), nom_agneau, FALSE, FALSE, 0);
  gtk_widget_set_size_request (nom_agneau, 158, 26);

  nom_loups_box = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (nom_loups_box);
  gtk_fixed_put (GTK_FIXED (fixed3), nom_loups_box, 77, 173);
  gtk_widget_set_size_request (nom_loups_box, 32, 16);
  gtk_widget_set_sensitive (nom_loups_box, FALSE);

  label22 = gtk_label_new ("Surnom :");
  gtk_widget_show (label22);
  gtk_box_pack_start (GTK_BOX (nom_loups_box), label22, FALSE, FALSE, 0);
  gtk_widget_set_size_request (label22, 64, 16);

  nom_loups = gtk_entry_new ();
  gtk_widget_show (nom_loups);
  gtk_box_pack_start (GTK_BOX (nom_loups_box), nom_loups, FALSE, FALSE, 0);
  gtk_widget_set_size_request (nom_loups, 158, 26);

  label15 = gtk_label_new ("<b>Choisis ton camp et entre ton nom</b>");
  gtk_widget_show (label15);
  gtk_fixed_put (GTK_FIXED (fixed3), label15, 24, 8);
  gtk_widget_set_size_request (label15, 256, 24);
  gtk_label_set_use_markup (GTK_LABEL (label15), TRUE);

  label16 = gtk_label_new ("<b>Loups</b>");
  gtk_widget_show (label16);
  gtk_fixed_put (GTK_FIXED (fixed3), label16, 30, 120);
  gtk_widget_set_size_request (label16, 64, 24);
  gtk_label_set_use_markup (GTK_LABEL (label16), TRUE);

  label13 = gtk_label_new ("<b>Agneau</b>");
  gtk_widget_show (label13);
  gtk_fixed_put (GTK_FIXED (fixed3), label13, 30, 32);
  gtk_widget_set_size_request (label13, 64, 24);
  gtk_label_set_use_markup (GTK_LABEL (label13), TRUE);

  label24 = gtk_label_new ("L'agneau commence :");
  gtk_widget_show (label24);
  gtk_fixed_put (GTK_FIXED (fixed3), label24, 56, 256);
  gtk_widget_set_size_request (label24, 152, 16);

  label23 = gtk_label_new ("<b>Positionnement</b>");
  gtk_widget_show (label23);
  gtk_fixed_put (GTK_FIXED (fixed3), label23, 30, 224);
  gtk_widget_set_size_request (label23, 120, 24);
  gtk_label_set_use_markup (GTK_LABEL (label23), TRUE);

  pos_agneau_bas = gtk_radio_button_new_with_mnemonic (NULL, "en haut");
  gtk_widget_show (pos_agneau_bas);
  gtk_fixed_put (GTK_FIXED (fixed3), pos_agneau_bas, 80, 304);
  gtk_widget_set_size_request (pos_agneau_bas, 105, 21);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (pos_agneau_bas), pos_agneau_bas_group);
  pos_agneau_bas_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (pos_agneau_bas));
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (pos_agneau_bas), TRUE);

  agneau_radio_ordi = gtk_radio_button_new_with_mnemonic (NULL, "Jou\303\251 par l'ordinateur");
  gtk_widget_show (agneau_radio_ordi);
  gtk_fixed_put (GTK_FIXED (fixed3), agneau_radio_ordi, 56, 104);
  gtk_widget_set_size_request (agneau_radio_ordi, 160, 24);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (agneau_radio_ordi), agneau_radio_ordi_group);
  agneau_radio_ordi_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (agneau_radio_ordi));

  loups_radio_ordi = gtk_radio_button_new_with_mnemonic (NULL, "Jou\303\251 par l'ordinateur");
  gtk_widget_show (loups_radio_ordi);
  gtk_fixed_put (GTK_FIXED (fixed3), loups_radio_ordi, 56, 200);
  gtk_widget_set_size_request (loups_radio_ordi, 160, 24);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (loups_radio_ordi), loups_radio_ordi_group);
  loups_radio_ordi_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (loups_radio_ordi));
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (loups_radio_ordi), TRUE);

  pos_agneau_haut = gtk_radio_button_new_with_mnemonic (NULL, "en bas");
  gtk_widget_show (pos_agneau_haut);
  gtk_fixed_put (GTK_FIXED (fixed3), pos_agneau_haut, 80, 280);
  gtk_widget_set_size_request (pos_agneau_haut, 105, 21);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (pos_agneau_haut), pos_agneau_bas_group);
  pos_agneau_bas_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (pos_agneau_haut));

  loups_radio_joueur = gtk_radio_button_new_with_mnemonic (NULL, "Vrai joueur");
  gtk_widget_show (loups_radio_joueur);
  gtk_fixed_put (GTK_FIXED (fixed3), loups_radio_joueur, 56, 144);
  gtk_widget_set_size_request (loups_radio_joueur, 160, 24);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (loups_radio_joueur), loups_radio_ordi_group);
  loups_radio_ordi_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (loups_radio_joueur));

  agneau_radio_joueur = gtk_radio_button_new_with_mnemonic (NULL, "Vrai joueur");
  gtk_widget_show (agneau_radio_joueur);
  gtk_fixed_put (GTK_FIXED (fixed3), agneau_radio_joueur, 56, 56);
  gtk_widget_set_size_request (agneau_radio_joueur, 160, 24);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (agneau_radio_joueur), agneau_radio_ordi_group);
  agneau_radio_ordi_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (agneau_radio_joueur));
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (agneau_radio_joueur), TRUE);

  dialog_action_area2 = GTK_DIALOG (jeusimple)->action_area;
  gtk_widget_show (dialog_action_area2);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area2), GTK_BUTTONBOX_END);

  cancelbutton2 = gtk_button_new ();
  gtk_widget_show (cancelbutton2);
  gtk_dialog_add_action_widget (GTK_DIALOG (jeusimple), cancelbutton2, GTK_RESPONSE_CANCEL);
  GTK_WIDGET_SET_FLAGS (cancelbutton2, GTK_CAN_DEFAULT);

  alignment9 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment9);
  gtk_container_add (GTK_CONTAINER (cancelbutton2), alignment9);

  hbox9 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox9);
  gtk_container_add (GTK_CONTAINER (alignment9), hbox9);

  image63 = gtk_image_new_from_stock ("gtk-cancel", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image63);
  gtk_box_pack_start (GTK_BOX (hbox9), image63, FALSE, FALSE, 0);

  label19 = gtk_label_new_with_mnemonic ("Annuler");
  gtk_widget_show (label19);
  gtk_box_pack_start (GTK_BOX (hbox9), label19, FALSE, FALSE, 0);

  okbutton2 = gtk_button_new ();
  gtk_widget_show (okbutton2);
  gtk_dialog_add_action_widget (GTK_DIALOG (jeusimple), okbutton2, GTK_RESPONSE_OK);
  GTK_WIDGET_SET_FLAGS (okbutton2, GTK_CAN_DEFAULT);

  alignment8 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment8);
  gtk_container_add (GTK_CONTAINER (okbutton2), alignment8);

  hbox8 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox8);
  gtk_container_add (GTK_CONTAINER (alignment8), hbox8);

  image62 = gtk_image_new_from_stock ("gtk-jump-to", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image62);
  gtk_box_pack_start (GTK_BOX (hbox8), image62, FALSE, FALSE, 0);

  label18 = gtk_label_new_with_mnemonic ("C'est parti !");
  gtk_widget_show (label18);
  gtk_box_pack_start (GTK_BOX (hbox8), label18, FALSE, FALSE, 0);

  g_signal_connect_swapped ((gpointer) agneau_radio_ordi, "toggled",
                            G_CALLBACK (on_agneau_radio_ordi_toggled),
                            GTK_OBJECT (nom_agneau_box));
  g_signal_connect_swapped ((gpointer) loups_radio_ordi, "toggled",
                            G_CALLBACK (on_loups_radio_ordi_toggled),
                            GTK_OBJECT (nom_loups_box));
  g_signal_connect_swapped ((gpointer) loups_radio_joueur, "toggled",
                            G_CALLBACK (on_loups_radio_joueur_toggled),
                            GTK_OBJECT (nom_loups_box));
  g_signal_connect_swapped ((gpointer) agneau_radio_joueur, "toggled",
                            G_CALLBACK (on_agneau_radio_joueur_toggled),
                            GTK_OBJECT (nom_agneau_box));

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (jeusimple, jeusimple, "jeusimple");
  GLADE_HOOKUP_OBJECT_NO_REF (jeusimple, dialog_vbox2, "dialog_vbox2");
  GLADE_HOOKUP_OBJECT (jeusimple, fixed3, "fixed3");
  GLADE_HOOKUP_OBJECT (jeusimple, nom_agneau_box, "nom_agneau_box");
  GLADE_HOOKUP_OBJECT (jeusimple, label14, "label14");
  GLADE_HOOKUP_OBJECT (jeusimple, nom_agneau, "nom_agneau");
  GLADE_HOOKUP_OBJECT (jeusimple, nom_loups_box, "nom_loups_box");
  GLADE_HOOKUP_OBJECT (jeusimple, label22, "label22");
  GLADE_HOOKUP_OBJECT (jeusimple, nom_loups, "nom_loups");
  GLADE_HOOKUP_OBJECT (jeusimple, label15, "label15");
  GLADE_HOOKUP_OBJECT (jeusimple, label16, "label16");
  GLADE_HOOKUP_OBJECT (jeusimple, label13, "label13");
  GLADE_HOOKUP_OBJECT (jeusimple, label24, "label24");
  GLADE_HOOKUP_OBJECT (jeusimple, label23, "label23");
  GLADE_HOOKUP_OBJECT (jeusimple, pos_agneau_bas, "pos_agneau_bas");
  GLADE_HOOKUP_OBJECT (jeusimple, agneau_radio_ordi, "agneau_radio_ordi");
  GLADE_HOOKUP_OBJECT (jeusimple, loups_radio_ordi, "loups_radio_ordi");
  GLADE_HOOKUP_OBJECT (jeusimple, pos_agneau_haut, "pos_agneau_haut");
  GLADE_HOOKUP_OBJECT (jeusimple, loups_radio_joueur, "loups_radio_joueur");
  GLADE_HOOKUP_OBJECT (jeusimple, agneau_radio_joueur, "agneau_radio_joueur");
  GLADE_HOOKUP_OBJECT_NO_REF (jeusimple, dialog_action_area2, "dialog_action_area2");
  GLADE_HOOKUP_OBJECT (jeusimple, cancelbutton2, "cancelbutton2");
  GLADE_HOOKUP_OBJECT (jeusimple, alignment9, "alignment9");
  GLADE_HOOKUP_OBJECT (jeusimple, hbox9, "hbox9");
  GLADE_HOOKUP_OBJECT (jeusimple, image63, "image63");
  GLADE_HOOKUP_OBJECT (jeusimple, label19, "label19");
  GLADE_HOOKUP_OBJECT (jeusimple, okbutton2, "okbutton2");
  GLADE_HOOKUP_OBJECT (jeusimple, alignment8, "alignment8");
  GLADE_HOOKUP_OBJECT (jeusimple, hbox8, "hbox8");
  GLADE_HOOKUP_OBJECT (jeusimple, image62, "image62");
  GLADE_HOOKUP_OBJECT (jeusimple, label18, "label18");
  g_signal_connect(G_OBJECT(okbutton2),"released",G_CALLBACK(game_initter),jeusimple);
  g_signal_connect(G_OBJECT(cancelbutton2),"released",G_CALLBACK(hide_nouvelle_partie),jeusimple);

  return jeusimple;
}

void hide_nouvelle_partie(GtkWidget* emitter, gpointer what)
{
     gtk_widget_destroy(what);
}

void nouvelle_partie()
{
     GtkWidget* dialog = create_jeusimple();
     gtk_widget_show(dialog);
     g_signal_connect(dialog,"destroy",G_CALLBACK(hide_nouvelle_partie),dialog);
}

GtkWidget *window_init(GtkWidget **win,t_game **game)
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
    { "/Configuration/_Choix du Theme","<ctrl>T", wintheme, 0, "<StockItem>", GTK_STOCK_CLEAR},
    { "/Configuration/_Niveau de Difficulte","<ctrl>D", NULL, 0, "<StockItem>", GTK_STOCK_PREFERENCES },
    { "/Retour",NULL, NULL, 0, "<Branch>" },
    { "/Retour/_Retour","<ctrl>R", go_back, 0, "<StockItem>", GTK_STOCK_MEDIA_REWIND },
    { "/_?", NULL, NULL, 0, "<Branch>" },
    { "/?/_A propos de...", "<CTRL>A", onabout, 1, "<StockItem>", GTK_STOCK_HELP}};
	/** - cr�tion de la fenetre\n
	*/
	*win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(*win),0);
	gtk_window_set_title(GTK_WINDOW(*win),"Projo tera generation");
	//gtk_window_set_gravity(GTK_WINDOW(*win),GDK_GRAVITY_CENTER);
	gtk_window_set_position(GTK_WINDOW(*win),GTK_WIN_POS_CENTER_ALWAYS);
	gtk_widget_realize(*win);
	g_signal_connect(*win,"destroy",gtk_main_quit,NULL);
	/** - cr�tion de la table 10*10\n
	*/
    if((table = gtk_table_new(10,10,TRUE))==NULL) return NULL;
	/** - cr�tion du menu\n
	*/
	Accel = gtk_accel_group_new ();
	ItemFactory = gtk_item_factory_new(GTK_TYPE_MENU_BAR,"<main>",Accel);
	gtk_item_factory_create_items(ItemFactory,13,MenuItem,*win);
	MenuBar = gtk_item_factory_get_widget(ItemFactory,"<main>");
	gtk_window_add_accel_group(GTK_WINDOW(*win),Accel);
	/** - cr�tion d'une vertical box\n
	*/
    VBox = gtk_vbox_new(FALSE, 0);
    /** - ajout de la vertical box a la fenetre\n
	*/
    gtk_container_add(GTK_CONTAINER(*win),VBox);
    /** - ajout du menu et de la table dans la vertical box\n
	*/
	gtk_box_pack_start(GTK_BOX(VBox),MenuBar,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(VBox),table,FALSE,FALSE,0);
	/** - affichage de tout les ��ents de la fenetre\n
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
	strcat(PATH,"normal/");
	/** - cr�tion de la structure principale\n
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
	
	/** - sensibilit�du terrain aux clics\n
	*/
	thegame->locked = FALSE;
	/** - utilisation du r�eau
	*/
	
	/** - initialisation du terrain\n
	* -# cr�tion des eventbox
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
    /** - m�orisation du nom des joueurs\n
	*/
	if((thegame->data.player[0] = (char*) malloc((strlen(player1name)+1)*sizeof(char))) == NULL) return ERR_ALLOC_NAME1;
	strcpy(thegame->data.player[0],player1name);
	if((thegame->data.player[1] = (char*) malloc((strlen(player2name)+1)*sizeof(char))) == NULL) return ERR_ALLOC_NAME2;
	strcpy(thegame->data.player[1],player2name);
	
	/** - initialisation des coordonn�s des pions\n
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
	
	/** - initialisation des coordonn�s des pions (acc� rapide)\n
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
	thegame->wintheme = create_wintheme();
	GTK_WINTHEME = thegame->wintheme;
	
	return SUCCESS;
}
