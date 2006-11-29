#ifndef STRUCTURESH
#define STRUCTURESH

#include "[DOX]main.h"

/** \struct t_player
*  */
typedef struct
{
	gboolean type;/**< type du joueur : humain / machine */
	gboolean animal;/**< animal du joueur : loup / agneau */
}t_player;

/** \struct  t_coords
*  */
typedef struct
{
	int x;/**<  abscisse */
	int y;/**<  ordonn�e */
}t_coords;

/** \struct t_association
*  */
typedef struct
{
	GtkWidget *eventbox;/**< eventbox associ�e � la position */
	t_coords position;/**< coordonn�es de l'eventbox associ�e */
}t_association;

/** \struct t_history
*  */
typedef struct
{
	t_coords wolf[5];/**< coordonn�es des loups */
	t_coords lamb;/**< coordonn�es de l'agneau */
	gboolean curplayer;/**< joueur en cours */
}t_history;

/** \struct t_data
*  */
typedef struct
{
	gboolean orientation;/**< orientation du terrain (loups/agneau en haut/bas)  */
	t_history *now;/**< �tat du plateau */
	GList *history;/**< historique des �tats du plateau */
	t_association *selection;/**< s�lection en cours (pour d�placement) */
	char *player[2];/**< noms des joueurs */
}t_data;

/** \struct t_game
*  */
typedef struct
{
	t_player players[2];/**< informations sur les joueurs */
	t_association eventbox[10][10];/**< associations entre les eventbox (graphique) et les positions r�elles (m�moire) */
	t_data data;/**< emsemble des infos de la partie */
	t_association pawn[6];/**< emplacement des animaux */
}t_game;

#endif