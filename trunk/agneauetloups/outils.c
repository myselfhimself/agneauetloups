#ifndef OUTILSC
#define OUTILSC

#include <gtk/gtk.h>
#include "main.h"

void next_turn(GtkWiget *emitter,gpointer *event,t_tout *tout)
{
	// Si le tour est à l'IA : lancer l'IA correspondante
	if(tout->is_human[tout->cur_player])
	{
		if(tout->cur_player == LAMB )
			IA_lamb(tout);
		else
			IA_WOLF(tout);
	}
	// Sinon retour au gtk_main et attends click du joueur
}






























#endif

