#ifndef STRUCTURESH
#define STRUCTURESH

#include "main.h"

/** \struct t_player
* \brief type et animal d'un joueur
*  */
typedef struct
{
	gboolean type;/**< type du joueur : humain / machine */
	gboolean animal;/**< animal du joueur : loup / agneau */
}t_player;

/** \struct  t_coords
* \brief abcisse et ordonn�e d'une position
*  */
typedef struct
{
	int x;/**<  abscisse */
	int y;/**<  ordonn�e */
}t_coords;

/** \struct t_association
* \brief association entre une eventbox et une position
*  */
typedef struct
{
	GtkWidget *eventbox;/**< eventbox associ�e � la position */
	t_coords position;/**< coordonn�es de l'eventbox associ�e */
}t_association;

/** \struct t_history
* \brief position des pions et joueur courant
*  */
typedef struct
{
	t_coords wolf[5];/**< coordonn�es des loups */
	t_coords lamb;/**< coordonn�es de l'agneau */
	gboolean curplayer;/**< joueur en cours */
}t_history;

/** \struct t_data
* \brief donn�es du jeu en cours
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
* \brief structure principale
*  */
typedef struct
{
	gboolean locked;/**< dit si le plateau de jeu est insensible aux clics (partie r�seau notamment) */
	t_player players[2];/**< informations sur les joueurs */
	t_association eventbox[10][10];/**< associations entre les eventbox (graphique) et les positions r�elles (m�moire) */
	t_data data;/**< emsemble des infos de la partie */
	t_association pawn[6];/**< emplacement des animaux */
	GtkWidget *wintheme;
}t_game;

typedef struct {int nbwords;char **word;}t_wordlist;

#endif
