#ifndef OUTILSC
#define OUTILSC

#include <gtk/gtk.h>
#include "main.h"

void next_turn(GtkWidget *emitter,gpointer *event,t_tout *tout)
{
	// Si le tour est à l'IA : lancer l'IA correspondante
	if(tout->data->is_human[tout->data->cur_player])
	{
		if(tout->data->cur_player == LAMB )
			IA_lamb(tout);
		else
			IA_wolf(tout);
	}
	// Sinon retour au gtk_main et attends click du joueur
}

void IA_lamb(t_tout *tout){;}
void IA_wolf(t_tout *tout){;}






























#endif

