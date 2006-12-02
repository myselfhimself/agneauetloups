#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdio.h>

#include "callbacks.h"
#include "interface.h"


void
on_radio_im_server_toggled             (gpointer         user_data,
                                        GtkToggleButton *togglebutton)
{
    FILE* fp;
    fp = fopen("txt.txt","a+");
gtk_widget_set_sensitive((GtkWidget*)user_data,gtk_toggle_button_get_active(togglebutton) ? FALSE : TRUE);
fprintf(fp,"server toggled : %d\n",gtk_toggle_button_get_active(togglebutton) ? FALSE : TRUE);
fclose(fp);
}


void
on_radio_im_not_server_toggled         (gpointer user_data,
                                         GtkToggleButton *togglebutton)
{
    FILE* fp;
    fp = fopen("txt.txt","a+");
gtk_widget_set_sensitive((GtkWidget*)user_data,gtk_toggle_button_get_active(togglebutton) ? FALSE : TRUE);
fprintf(fp,"client toggled : %d\n",gtk_toggle_button_get_active(togglebutton) ? FALSE : TRUE);
fclose(fp);
}

