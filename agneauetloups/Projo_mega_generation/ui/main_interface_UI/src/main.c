/*
 * Initial main.c file generated by Glade. Edit as required.
 * Glade will not overwrite this file.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "interface.h"
////#include "(null)"

int
main (int argc, char *argv[])
{
  GtkWidget *jeu;

  gtk_set_locale ();
  gtk_init (&argc, &argv);

////  add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");

  /*
   * The following code was added by Glade to create one of each component
   * (except popup menus), just so that you see something after building
   * the project. Delete any components that you don't want shown initially.
   */
  jeu = create_jeu ();
  gtk_widget_show (jeu);

  gtk_main ();
  return 0;
}

