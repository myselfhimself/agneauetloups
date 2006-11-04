#include "projet.h"

//petits utilitaires pour ne pas avoir a reflechir quand on veut acceder une information

//retourne un pointeur sur la position de la table de jeu, de coordonnes "coords"
t_position* memory_get_pos_from_coords(t_coords coords,t_tout* tout)
{
	return &(tout->positions[coords.x][coords.y]);
}

//retourne la constante non selectionne de la constante donnee
int memory_get_type_to_unselected(int type)
{
	int result = type;
	switch(type)
	{
		case LAMB_SELECTED:
		case WOLF_SELECTED:
			result = type-3;
			break;
		default:
			break;
	}
	return result;
}