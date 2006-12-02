#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"



void
on_agneau_radio_joueur_toggled         (gpointer         user_data,
                                        GtkToggleButton *togglebutton)
{
gtk_widget_set_sensitive((GtkWidget*)user_data,gtk_toggle_button_get_active(togglebutton) ? TRUE : FALSE);
}


void
on_agneau_radio_ordi_toggled           (gpointer         user_data,
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
on_loups_radio_ordi_toggled            (gpointer         user_data,
                                        GtkToggleButton *togglebutton)
{
gtk_widget_set_sensitive((GtkWidget*)user_data,gtk_toggle_button_get_active(togglebutton) ? FALSE : TRUE);
}

