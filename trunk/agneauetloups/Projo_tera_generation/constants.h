#ifndef CONSTANTSH
#define CONSTANTSH

#include "main.h"

/** - [OLD] constantes pour int importance(int depth)\n
*/
#define MAXDEPTH      8
#define MAXDEPTHVALUE 100

/** - constantes pour le renvoi des erreurs\n
*/
#define SUCCESS             1
#define ERR_FOPEN_PATH      0
#define ERR_ALLOC_GAME     -1
#define ERR_ALLOC_EVENTBOX -2
#define ERR_ALLOC_NOW      -3
#define ERR_ALLOC_NAME1    -4
#define ERR_ALLOC_NAME2    -5
#define ERR_COMPATIBILITY  -6
#define ERR_ALLOC_HISTORY  -7
#define ERR_WRITING_SAVE   -8

/** - constantes pour expliciter le code\n
*/
#define LAMB         0
#define WOLF         1
#define HUMAN        0
#define ARTIFICIAL   1
#define TOP_LEFT     0
#define TOP_RIGHT    1
#define BOTTOM_LEFT  2
#define BOTTOM_RIGHT 3

/** - constantes pour la gestion des plateformes\n
*/
#define LINUX 0
#define WINDOWS 1

/** - globale pour stocker le chemin d'acc�s aux fichiers\n
*/
char PATH[128];

/** - d�finition du syst�me\n
*/

#ifdef _WIN32
#define OPERATING_SYSTEM WINDOWS
#endif

#ifndef _WIN32
#define OPERATING_SYSTEM LINUX
#endif

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)
  
#include "structures.h"
  
GtkWidget *GTK_WINTHEME;
t_game **GAME;

#endif
