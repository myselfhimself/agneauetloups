/********************
 *  Implementation
 ********************/

#include <gtk/gtk.h>
#include <stdlib.h>

void on_click(GtkWidget* emitter, gpointer data)
{
    gtk_widget_set_sensitive(emitter,FALSE);
}    


int main(int argc, char **argv)
{
	GtkWidget *pWindow;
    GtkWidget* pButton;

	gtk_init(&argc, &argv);

	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	pButton = gtk_button_new_with_label("test");
    g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(on_click), NULL);
    gtk_container_add(GTK_CONTAINER(pWindow),pButton);

	gtk_widget_show_all(pWindow);

	gtk_main();

	return EXIT_SUCCESS;
}
