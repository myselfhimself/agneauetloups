#ifndef STRUCTURESH
#define STRUCTURESH

#include "main.h"


typedef struct
{
	int socket;
	//attention c'est un pointeur !
	struct sockaddr_in* address;
	int state;
}
t_connection;

typedef struct
{
	int im_server;
	//connection de type serveur, pour écouter une unique connection. Sera fermée une fois une connection trouvée
	t_connection server;
	//connection de type client/client utilisée dans tous les cas
	t_connection client;
}
t_network;

#define PACKET_SIZE 100*sizeof(char)
#define CONTENT_SIZE PACKET_SIZE-sizeof(int)
//packet d'une taille max de 100*sizeof(char), avec sizeof(char) = 1
typedef struct
{
	int type;// int <=> 4 octets (sizeof) <=> unsigned int <=> long : utiliser htonl
	char content[CONTENT_SIZE]; //max de 96 octets ici ; char <=> 1 octet
	//remarque : content est de type char*
}
t_packet;

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
	gboolean use_network;
	t_network network;
	t_player players[2];/**< informations sur les joueurs */
	t_association eventbox[10][10];/**< associations entre les eventbox (graphique) et les positions réelles (mémoire) */
	t_data data;/**< emsemble des infos de la partie */
	t_association pawn[6];/**< emplacement des animaux */
	GtkWidget *wintheme;
}t_game;

/** \struct t_wordlist
* \brief structure de stockage de mots
*  */
typedef struct
{
	int nbwords;/**< nombre de mots présents*/
	char **word;/**< tableau des mots présents*/
}t_wordlist;

#endif
