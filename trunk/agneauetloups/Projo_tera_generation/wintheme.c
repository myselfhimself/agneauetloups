#include "main.h"



void wintheme()
{
  /** - affiche la fenetre pour le choix des thèmes\n
  */
  gtk_widget_show_all(GTK_WINTHEME);
}

void uwintheme()
{
  /** - cache la fenetre pour le choix des thèmes\n
  */
  gtk_widget_hide(GTK_WINTHEME);
}

void activetheme(GtkWidget *widget)
{
     GtkWidget *table;
     GList *widgets;
     char img[128];
     int i,j;
     table = gtk_widget_get_parent(widget);
     widgets = gtk_container_get_children(GTK_CONTAINER(table));
     /** - récupère le texte sélectionné\n
     */
     gchar *txt = gtk_combo_box_get_active_text(GTK_COMBO_BOX((GtkWidget*) g_list_nth_data(widgets, 6)));
     if(strcmp(txt,"") != 0)
     {
         /** - redéfini le chemin des images en fonction du thème\n
         */
         init_OS_path();
         strcat(PATH,txt);
         strcat(PATH,"/");
         /** - si le jeu est créé, pour chaque case :\n
         * -# retire l'ancienne GtkImage\n
         * -# défini par quelle case elle doit être remplacée\n
         * -# recréé un GtkImage avec la nouvelle image\n
         * -# affiche l'image\n
         * - si le jeu est créé, pour chaque position des pions :\n
         * -# superpose l'image du pion sur l'image du terrain\n
         * -# affiche l'image\n
         * - redimensionne la fenetre à la taille des images\n
         */
         if(*GAME != NULL)
         {
             for(i=0;i<10;i++)
             {
                 for(j=0;j<10;j++)
                 {
                     gtk_container_remove(GTK_CONTAINER((*GAME)->eventbox[i][j].eventbox),(GtkWidget*)gtk_container_get_children(GTK_CONTAINER((*GAME)->eventbox[i][j].eventbox))->data);
                     if((i+j+(*GAME)->data.orientation)%2) sprintf(img,"%sBcase.bmp",PATH);
                     else sprintf(img,"%sNcase.bmp",PATH);
                     gtk_container_add(GTK_CONTAINER((*GAME)->eventbox[i][j].eventbox),gtk_image_new_from_file(img));
                     gtk_widget_show_all((*GAME)->eventbox[i][j].eventbox);
                 }
             }
             for(i=0;i<6;i++)
             {
                 if(i==0) sprintf(img,"%slamb.bmp",PATH);
                 else sprintf(img,"%swolf.bmp",PATH);
                 gtk_image_superimpose((*GAME)->eventbox[(*GAME)->pawn[i].position.x][(*GAME)->pawn[i].position.y].eventbox,img);
                 gtk_widget_show_all((*GAME)->eventbox[(*GAME)->pawn[i].position.x][(*GAME)->pawn[i].position.y].eventbox);
             }
             gtk_window_resize(GTK_WINDOW(gtk_widget_get_parent(gtk_widget_get_parent(gtk_widget_get_parent((*GAME)->eventbox[0][0].eventbox)))),2,2);
         }
     }
}

void refreshpreview(GtkWidget *widget, GtkWidget *table)
{
     GtkWidget *img1,*img2,*img3,*img4;
     GList *widgets;
     char img[128];
     widgets = gtk_container_get_children(GTK_CONTAINER(table));
     /** - récupère le texte sélectionné\n
     * - supprime les anciennes images d'aperçues\n
     * - charge les nouvelles images\n
     * - attache les images à la table de la fenetre\n
     * - affiche le tout\n
     */
     gchar *txt = gtk_combo_box_get_active_text(GTK_COMBO_BOX(widget));
     if(strcmp(txt,"") != 0)
     {
         img1 = (GtkWidget*) g_list_nth_data(widgets, 3);
         img2 = (GtkWidget*) g_list_nth_data(widgets, 2);
         img3 = (GtkWidget*) g_list_nth_data(widgets, 1);
         img4 = (GtkWidget*) g_list_nth_data(widgets, 0);
         
         gtk_container_remove(GTK_CONTAINER(table),img1);
         gtk_container_remove(GTK_CONTAINER(table),img2);
         gtk_container_remove(GTK_CONTAINER(table),img3);
         gtk_container_remove(GTK_CONTAINER(table),img4);
         
         sprintf(img,"%s%s%s/Bcase.bmp",PATH,"../",txt);
         img1 = gtk_image_new_from_file(img);
         sprintf(img,"%s%s%s/wolf.bmp",PATH,"../",txt);
         img2 = gtk_image_new_from_file(img);
         sprintf(img,"%s%s%s/lamb.bmp",PATH,"../",txt);
         img3 = gtk_image_new_from_file(img);
         sprintf(img,"%s%s%s/Ncase.bmp",PATH,"../",txt);
         img4 = gtk_image_new_from_file(img);
         
         gtk_table_attach(GTK_TABLE(table),img1, 4, 7, 0, 3, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
         gtk_table_attach(GTK_TABLE(table),img2, 7, 10, 0, 3, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
         gtk_table_attach(GTK_TABLE(table),img3, 4, 7, 3, 6, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
         gtk_table_attach(GTK_TABLE(table),img4, 7, 10, 3, 6, GTK_EXPAND |GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
         
         gtk_widget_show_all(table);
     }
}

GtkWidget *create_wintheme()
{
  GtkWidget *window1;
  GtkWidget *table1;
  GtkWidget *combobox;
  GtkWidget *image3;
  GtkWidget *image1;
  GtkWidget *image4;
  GtkWidget *image2;
  GtkWidget *refresh;
  GtkWidget *close;
  gint i;
  t_wordlist *fichier;
  
  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window1), ("Choix du theme"));
  g_signal_connect(G_OBJECT(window1), "delete_event", G_CALLBACK(uwintheme), NULL);

  table1 = gtk_table_new (1, 1, TRUE);
  gtk_container_add (GTK_CONTAINER (window1), table1);

  combobox = gtk_combo_box_entry_new_text ();
  g_signal_connect(G_OBJECT(combobox),"changed",G_CALLBACK(refreshpreview),table1);
  gtk_table_attach (GTK_TABLE (table1), combobox, 0, 4, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
  fichier = get_themes_files("theme");
  for(i=0;i<fichier->nbwords;i++)
  {
      fichier->word[i][strlen(fichier->word[i])-6-(OPERATING_SYSTEM==WINDOWS)] = '\0';
      gtk_combo_box_append_text (GTK_COMBO_BOX(combobox), fichier->word[i]);
      free(fichier->word[i]);
  }
  free(fichier->word);
  free(fichier);
  
  refresh = gtk_button_new_with_mnemonic (("Appliquer"));
  g_signal_connect(G_OBJECT(refresh),"clicked", G_CALLBACK(activetheme), NULL);
  gtk_table_attach (GTK_TABLE (table1), refresh, 6, 10, 6, 7,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);

  close = gtk_button_new_with_mnemonic (("Fermer"));
  g_signal_connect(G_OBJECT(close), "clicked", G_CALLBACK(uwintheme), NULL);
  gtk_table_attach (GTK_TABLE (table1), close, 0, 4, 6, 7,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);
  
  image1 = gtk_image_new();
  gtk_table_attach (GTK_TABLE (table1), image1, 4, 7, 0, 3,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);
                    
  image2 = gtk_image_new();
  gtk_table_attach (GTK_TABLE (table1), image2, 7, 10, 0, 3,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);

  image3 = gtk_image_new();
  gtk_table_attach (GTK_TABLE (table1), image3, 4, 7, 3, 6,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);

  image4 = gtk_image_new();
  gtk_table_attach (GTK_TABLE (table1), image4, 7, 10, 3, 6,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);

  return window1;
}

