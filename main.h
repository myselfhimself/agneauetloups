#ifndef MAINH
#define MAINH

#include <gtk/gtk.h>

// structures

typedef struct {int time;
		int timemax;
		int index;
		int indexmax;
		GdkPixbuf **images;
		}t_animation;
		
typedef struct {int position;
		int poss[4];
		}t_lamb;

typedef struct {int position;
		int poss[2];
		}t_wolf;
		
typedef struct {t_lamb lamb;
		t_wolf wolf[5];
		}t_data;

typedef struct {int skin;
		       GtkWidget *button[50];
		       GdkPixbuf **images;
		       t_animation *animation;
		       GtkWidget *statusbar;
		       t_data *data;
		       GList *history;
		       }t_tout;

#endif
