#include "projet.h"

//cette fonction recoit les resultats de la configuration d'une nouvelle partie
//elle s'occupe de transmettre les donnees de comportement au moteur de jeu
//ainsi que de positionner de positionner les differents joueurs sur le plateau
//elle configure le joueur en cours pour que ce soit celui qui soit en bas du plateau de jeu (!= selectionne un pion)
//tente de faire selectionner l'agneau si c'est son tour en appelant players_try_detect_selection
void players_game_init(t_player player1_info, t_player player2_info, t_tout* tout)
{
	//iterateur
	int a;
	//pour le placement des pions apres, on saura mettre les loups et l'agneau en haut ou en bas
	int agneau_en_haut;

	agneau_en_haut = (player1_info.actor_type == LAMB) ? (player1_info.direction == DOWN) : (player2_info.direction == UP);

	//remplissage du comportement des joueurs dans le moteur de jeu
	tout->data.players[0] = player1_info;
	tout->data.players[1] = player2_info;

	//on remplit une element history pour l'instant present
	for(a=0;a<5;a++)
	{
		tout->data.now.loups[a].x = a*2; //atteindra 8, le max etant bien 9 (10 cases par ligne)
		//si l'agneau est en haut, les loups sont en bas, sinon ils sont en haut
		tout->data.now.loups[a].y = (agneau_en_haut) ? 9 : 0;
	}
	tout->data.now.agneau.x = 5;
	tout->data.now.agneau.y = (agneau_en_haut) ? 0 : 9;

	//on ecrit qui sera le joueur en cours : celui qui est en bas du plateau de jeu
	tout->data.current_player = (agneau_en_haut) ? WOLF : LAMB;
	
	//on vide les selections de chacun des joueurs
	players_empty_selection(tout,TRUE);
	players_try_set_selection(tout);

	//on appelle la fonction d'affichage de l'instant present
	interface_redraw_positions(tout);
}

//vide la selection de chacun des joueurs
//necessite une mise a jour graphique pour voir les changements
//si force est vrai (TRUE), ne chercher pas a changer
//l'aspect graphique des boutons et ne teste pas si les selections sont vides ou non
void players_empty_selection(t_tout* tout,gboolean force)
{
	t_coords* temp=NULL;
	int a;
	int* type=NULL;

	//on vide pour chaque joueur les choses selectionnees symbolisees par des pointeurs sur "t_coords"
	//si la selection n'etait pas vide, on change le type de la case pointe par un type non selectionne
	//cela a pour but d'avoir un affichage coordonne
	for(a=0;a<2;a++)
	{
		//si on ne force pas, on fait tout plein de tests
		//pour changer l'aspect des boutons selectionnes s'il y en a
		if(!force)
		{
			//selection est un pointeur sur t_coords
			temp = tout->data.players[a].selection;
			//si selection ne pointait pas sur rien
			if(temp != NULL)
			{
				//on chope le type de l'affichage de ce sur quoi ca pointait
				type = &memory_get_pos_from_coords(*temp,tout)->forced_type;
				//on reecrit ce type en type pas selectionne (ex: LAMB_SELECTED => LAMB)
				*type = memory_get_type_to_unselected(*type);
			}
		}
		//on peut maintenant vider la selection
		tout->data.players[a].selection = NULL;
	}
}

//essaye de selectionner l'agneau si c'est le tour du camp de l'agneau
//la selection de chacun des joueurs devrait etre videe avant
//retourne 1 si quelque chose s'est passe
int players_try_set_selection(t_tout* tout)
{
	int result=0;
	//si c'est le tour de l'agneau
	if(tout->data.current_player == LAMB)
	{
		//la selection devient un pointeur sur t_coord avec le t_coord qui est les coordonnees de l'agneau
		tout->data.players[LAMB].selection = &(tout->data.now.agneau);
		result = 1;
	}
	return result;
}