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
* \brief abcisse et ordonnée d'une position
*  */
typedef struct
{
	int x;/**<  abscisse */
	int y;/**<  ordonnée */
}t_coords;

/** \struct t_association
* \brief association entre une eventbox et une position
*  */
typedef struct
{
	GtkWidget *eventbox;/**< eventbox associée à la position */
	t_coords position;/**< coordonnées de l'eventbox associée */
}t_association;

/** \struct t_history
* \brief position des pions et joueur courant
*  */
typedef struct
{
	t_coords wolf[5];/**< coordonnées des loups */
	t_coords lamb;/**< coordonnées de l'agneau */
	gboolean curplayer;/**< joueur en cours */
}t_history;

/** \struct t_data
* \brief données du jeu en cours
*  */
typedef struct
{
	gboolean orientation;/**< orientation du terrain (loups/agneau en haut/bas)  */
	t_history *now;/**< état du plateau */
	GList *history;/**< historique des états du plateau */
	t_association *selection;/**< sélection en cours (pour déplacement) */
	char *player[2];/**< noms des joueurs */
}t_data;

/** \struct t_game
* \brief structure principale
*  */
typedef struct
{
	gboolean locked;/**< dit si le plateau de jeu est insensible aux clics (partie réseau notamment) */
	t_player players[2];/**< informations sur les joueurs */
	t_association eventbox[10][10];/**< associations entre les eventbox (graphique) et les positions réelles (mémoire) */
	t_data data;/**< emsemble des infos de la partie */
	t_association pawn[6];/**< emplacement des animaux */
	GtkWidget *wintheme;
}t_game;

typedef struct {int nbwords;char **word;}t_wordlist;

#endif
