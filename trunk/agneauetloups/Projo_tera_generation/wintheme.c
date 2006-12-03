#include "main.h"

void wintheme()
{
  gtk_widget_show_all(GTK_WINTHEME);
}

void uwintheme()
{
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
     gchar *txt = gtk_combo_box_get_active_text(GTK_COMBO_BOX((GtkWidget*) g_list_nth_data(widgets, 6)));
     if(strcmp(txt,"") != 0)
     {
         init_OS_path();
         strcat(PATH,txt);
         strcat(PATH,"/");
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

GtkWidget* lookup_widget(GtkWidget *widget, const gchar *widget_name)
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
      fichier->word[i][strlen(fichier->word[i])-7] = '\0';
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

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (window1, window1, "window1");
  GLADE_HOOKUP_OBJECT (window1, table1, "table1");
  GLADE_HOOKUP_OBJECT (window1, combobox, "combobox");
  GLADE_HOOKUP_OBJECT (window1, image3, "image3");
  GLADE_HOOKUP_OBJECT (window1, image1, "image1");
  GLADE_HOOKUP_OBJECT (window1, image4, "image4");
  GLADE_HOOKUP_OBJECT (window1, image2, "image2");
  GLADE_HOOKUP_OBJECT (window1, refresh, "refresh");
  GLADE_HOOKUP_OBJECT (window1, close, "close");
  
  return window1;
}

