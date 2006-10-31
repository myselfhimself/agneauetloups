#include "projet.h"

#ifndef MAINH
#define MAINH

// Constantes

#define LAMB 0
#define WOLF 1

// structures

typedef struct {
	GtkWidget *lastone;
	}t_movement;

void make_movement(GtkWidget *newone,t_movement *move);

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
		int is_human[2];
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
