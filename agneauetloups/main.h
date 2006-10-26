#ifndef MAINH
#define MAINH

#include <gtk/gtk.h>
#include "outils.c"

// Constantes

#define LAMB 0
#define WOLF 1

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
		int cur_player;
		bool is_human[2];
		}t_data;

typedef struct {int skin;
		       GtkWidget *button[50];
		       GdkPixbuf **images;
		       t_animation *animation;
		       GtkWidget *statusbar;
		       t_data *data;
		       GList *history;
		       }t_tout;

// Prototypes

void IA_lamb(t_tout *tout);
void IA_wolf(t_tout *tout);
void next_turn(GtkWiget *emitter,gpointer *event,t_tout *tout);
			   
#endif
