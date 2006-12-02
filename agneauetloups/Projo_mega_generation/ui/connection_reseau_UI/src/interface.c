/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
//#include "(null)"

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)

GtkWidget*
create_connection_setup (void)
{
  GtkWidget *connection_setup;
  GtkWidget *dialog_vbox1;
  GtkWidget *fixed1;
  GtkWidget *nom_joueur_entry;
  GtkWidget *server_hbox;
  GtkWidget *port_server_label;
  GtkWidget *port_server_entry;
  GtkWidget *nom_joueur_label;
  GtkWidget *client_vbox;
  GtkWidget *client_hbox1;
  GtkWidget *ip_client_label;
  GtkWidget *client_ip_entry;
  GtkWidget *client_hbox2;
  GtkWidget *port_client_label;
  GtkWidget *port_client_entry;
  GtkWidget *radio_im_server;
  GSList *radio_im_server_group = NULL;
  GtkWidget *radio_im_not_server;
  GtkWidget *dialog_action_area1;
  GtkWidget *cancelbutton1;
  GtkWidget *alignment2;
  GtkWidget *hbox2;
  GtkWidget *image56;
  GtkWidget *label5;
  GtkWidget *okbutton1;
  GtkWidget *alignment1;
  GtkWidget *hbox1;
  GtkWidget *image55;
  GtkWidget *label4;

  connection_setup = gtk_dialog_new ();
  gtk_widget_set_size_request (connection_setup, 276, 301);
  gtk_window_set_title (GTK_WINDOW (connection_setup), "Partie R\303\251seau");
  gtk_window_set_resizable (GTK_WINDOW (connection_setup), FALSE);
  gtk_window_set_destroy_with_parent (GTK_WINDOW (connection_setup), TRUE);
  //gtk_window_set_icon_name (GTK_WINDOW (connection_setup), "gtk-dialog-info");
  gtk_window_set_type_hint (GTK_WINDOW (connection_setup), GDK_WINDOW_TYPE_HINT_DIALOG);

  dialog_vbox1 = GTK_DIALOG (connection_setup)->vbox;
  gtk_widget_show (dialog_vbox1);

  fixed1 = gtk_fixed_new ();
  gtk_widget_show (fixed1);
  gtk_box_pack_start (GTK_BOX (dialog_vbox1), fixed1, TRUE, TRUE, 0);

  nom_joueur_entry = gtk_entry_new ();
  gtk_widget_show (nom_joueur_entry);
  gtk_fixed_put (GTK_FIXED (fixed1), nom_joueur_entry, 72, 49);
  gtk_widget_set_size_request (nom_joueur_entry, 158, 26);
  gtk_entry_set_text (GTK_ENTRY (nom_joueur_entry), "Bob");

  server_hbox = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (server_hbox);
  gtk_fixed_put (GTK_FIXED (fixed1), server_hbox, 37, 122);
  gtk_widget_set_size_request (server_hbox, 32, 16);

  port_server_label = gtk_label_new ("Port");
  gtk_widget_show (port_server_label);
  gtk_box_pack_start (GTK_BOX (server_hbox), port_server_label, FALSE, FALSE, 0);
  gtk_widget_set_size_request (port_server_label, 36, 18);

  port_server_entry = gtk_entry_new ();
  gtk_widget_show (port_server_entry);
  gtk_box_pack_start (GTK_BOX (server_hbox), port_server_entry, FALSE, FALSE, 0);
  gtk_widget_set_size_request (port_server_entry, 158, 26);
  gtk_entry_set_text (GTK_ENTRY (port_server_entry), "5010");

  nom_joueur_label = gtk_label_new ("<b>Mon nom de joueur :</b>");
  gtk_widget_show (nom_joueur_label);
  gtk_fixed_put (GTK_FIXED (fixed1), nom_joueur_label, 16, 16);
  gtk_widget_set_size_request (nom_joueur_label, 152, 26);
  gtk_label_set_use_markup (GTK_LABEL (nom_joueur_label), TRUE);

  client_vbox = gtk_vbox_new (FALSE, 29);
  gtk_widget_show (client_vbox);
  gtk_fixed_put (GTK_FIXED (fixed1), client_vbox, 36, 197);
  gtk_widget_set_size_request (client_vbox, 16, 32);
  gtk_widget_set_sensitive (client_vbox, FALSE);

  client_hbox1 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (client_hbox1);
  gtk_box_pack_start (GTK_BOX (client_vbox), client_hbox1, TRUE, FALSE, 0);
  gtk_widget_set_size_request (client_hbox1, 32, 16);

  ip_client_label = gtk_label_new ("IP");
  gtk_widget_show (ip_client_label);
  gtk_box_pack_start (GTK_BOX (client_hbox1), ip_client_label, FALSE, FALSE, 0);
  gtk_widget_set_size_request (ip_client_label, 36, 18);

  client_ip_entry = gtk_entry_new ();
  gtk_widget_show (client_ip_entry);
  gtk_box_pack_start (GTK_BOX (client_hbox1), client_ip_entry, FALSE, FALSE, 0);
  gtk_widget_set_size_request (client_ip_entry, 158, 26);

  client_hbox2 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (client_hbox2);
  gtk_box_pack_start (GTK_BOX (client_vbox), client_hbox2, TRUE, FALSE, 0);
  gtk_widget_set_size_request (client_hbox2, 32, 16);

  port_client_label = gtk_label_new ("Port");
  gtk_widget_show (port_client_label);
  gtk_box_pack_start (GTK_BOX (client_hbox2), port_client_label, FALSE, FALSE, 0);
  gtk_widget_set_size_request (port_client_label, 36, 18);

  port_client_entry = gtk_entry_new ();
  gtk_widget_show (port_client_entry);
  gtk_box_pack_start (GTK_BOX (client_hbox2), port_client_entry, FALSE, FALSE, 0);
  gtk_widget_set_size_request (port_client_entry, 158, 26);
  gtk_entry_set_text (GTK_ENTRY (port_client_entry), "5010");

  radio_im_server = gtk_radio_button_new_with_mnemonic (NULL, "J'h\303\251berge la partie");
  gtk_widget_show (radio_im_server);
  gtk_fixed_put (GTK_FIXED (fixed1), radio_im_server, 32, 89);
  gtk_widget_set_size_request (radio_im_server, 152, 22);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radio_im_server), radio_im_server_group);
  radio_im_server_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radio_im_server));
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radio_im_server), TRUE);

  radio_im_not_server = gtk_radio_button_new_with_mnemonic (NULL, "Je me connecte chez quelqu'un");
  gtk_widget_show (radio_im_not_server);
  gtk_fixed_put (GTK_FIXED (fixed1), radio_im_not_server, 32, 160);
  gtk_widget_set_size_request (radio_im_not_server, 240, 22);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radio_im_not_server), radio_im_server_group);
  radio_im_server_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radio_im_not_server));

  dialog_action_area1 = GTK_DIALOG (connection_setup)->action_area;
  gtk_widget_show (dialog_action_area1);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area1), GTK_BUTTONBOX_END);

  cancelbutton1 = gtk_button_new ();
  gtk_widget_show (cancelbutton1);
  gtk_dialog_add_action_widget (GTK_DIALOG (connection_setup), cancelbutton1, GTK_RESPONSE_CANCEL);
  GTK_WIDGET_SET_FLAGS (cancelbutton1, GTK_CAN_DEFAULT);

  alignment2 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment2);
  gtk_container_add (GTK_CONTAINER (cancelbutton1), alignment2);

  hbox2 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox2);
  gtk_container_add (GTK_CONTAINER (alignment2), hbox2);

  image56 = gtk_image_new_from_stock ("gtk-cancel", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image56);
  gtk_box_pack_start (GTK_BOX (hbox2), image56, FALSE, FALSE, 0);

  label5 = gtk_label_new_with_mnemonic ("Annuler");
  gtk_widget_show (label5);
  gtk_box_pack_start (GTK_BOX (hbox2), label5, FALSE, FALSE, 0);

  okbutton1 = gtk_button_new ();
  gtk_widget_show (okbutton1);
  gtk_dialog_add_action_widget (GTK_DIALOG (connection_setup), okbutton1, GTK_RESPONSE_OK);
  GTK_WIDGET_SET_FLAGS (okbutton1, GTK_CAN_DEFAULT);

  alignment1 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment1);
  gtk_container_add (GTK_CONTAINER (okbutton1), alignment1);

  hbox1 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox1);
  gtk_container_add (GTK_CONTAINER (alignment1), hbox1);

  image55 = gtk_image_new_from_stock ("gtk-goto-last", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image55);
  gtk_box_pack_start (GTK_BOX (hbox1), image55, FALSE, FALSE, 0);

  label4 = gtk_label_new_with_mnemonic ("C'est parti !");
  gtk_widget_show (label4);
  gtk_box_pack_start (GTK_BOX (hbox1), label4, FALSE, FALSE, 0);

  g_signal_connect_swapped ((gpointer) radio_im_server, "toggled",
                            G_CALLBACK (on_radio_im_server_toggled),
                            GTK_OBJECT (client_vbox));
  g_signal_connect_swapped ((gpointer) radio_im_not_server, "toggled",
                            G_CALLBACK (on_radio_im_not_server_toggled),
                            GTK_OBJECT (server_hbox));

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (connection_setup, connection_setup, "connection_setup");
  GLADE_HOOKUP_OBJECT_NO_REF (connection_setup, dialog_vbox1, "dialog_vbox1");
  GLADE_HOOKUP_OBJECT (connection_setup, fixed1, "fixed1");
  GLADE_HOOKUP_OBJECT (connection_setup, nom_joueur_entry, "nom_joueur_entry");
  GLADE_HOOKUP_OBJECT (connection_setup, server_hbox, "server_hbox");
  GLADE_HOOKUP_OBJECT (connection_setup, port_server_label, "port_server_label");
  GLADE_HOOKUP_OBJECT (connection_setup, port_server_entry, "port_server_entry");
  GLADE_HOOKUP_OBJECT (connection_setup, nom_joueur_label, "nom_joueur_label");
  GLADE_HOOKUP_OBJECT (connection_setup, client_vbox, "client_vbox");
  GLADE_HOOKUP_OBJECT (connection_setup, client_hbox1, "client_hbox1");
  GLADE_HOOKUP_OBJECT (connection_setup, ip_client_label, "ip_client_label");
  GLADE_HOOKUP_OBJECT (connection_setup, client_ip_entry, "client_ip_entry");
  GLADE_HOOKUP_OBJECT (connection_setup, client_hbox2, "client_hbox2");
  GLADE_HOOKUP_OBJECT (connection_setup, port_client_label, "port_client_label");
  GLADE_HOOKUP_OBJECT (connection_setup, port_client_entry, "port_client_entry");
  GLADE_HOOKUP_OBJECT (connection_setup, radio_im_server, "radio_im_server");
  GLADE_HOOKUP_OBJECT (connection_setup, radio_im_not_server, "radio_im_not_server");
  GLADE_HOOKUP_OBJECT_NO_REF (connection_setup, dialog_action_area1, "dialog_action_area1");
  GLADE_HOOKUP_OBJECT (connection_setup, cancelbutton1, "cancelbutton1");
  GLADE_HOOKUP_OBJECT (connection_setup, alignment2, "alignment2");
  GLADE_HOOKUP_OBJECT (connection_setup, hbox2, "hbox2");
  GLADE_HOOKUP_OBJECT (connection_setup, image56, "image56");
  GLADE_HOOKUP_OBJECT (connection_setup, label5, "label5");
  GLADE_HOOKUP_OBJECT (connection_setup, okbutton1, "okbutton1");
  GLADE_HOOKUP_OBJECT (connection_setup, alignment1, "alignment1");
  GLADE_HOOKUP_OBJECT (connection_setup, hbox1, "hbox1");
  GLADE_HOOKUP_OBJECT (connection_setup, image55, "image55");
  GLADE_HOOKUP_OBJECT (connection_setup, label4, "label4");

  gtk_widget_grab_focus (okbutton1);
  gtk_widget_grab_default (okbutton1);
  return connection_setup;
}

