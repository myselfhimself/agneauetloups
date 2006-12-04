#ifndef CONSTANTSH
#define CONSTANTSH

#include "main.h"

/** - [OLD] constantes pour int importance(int depth)\n
*/
#define MAXDEPTH      8
#define MAXDEPTHVALUE 100

/** - constantes pour le renvoi des erreurs\n
*/
#define SUCCESS             1
#define ERR_FOPEN_PATH      0
#define ERR_ALLOC_GAME     -1
#define ERR_ALLOC_EVENTBOX -2
#define ERR_ALLOC_NOW      -3
#define ERR_ALLOC_NAME1    -4
#define ERR_ALLOC_NAME2    -5
#define ERR_COMPATIBILITY  -6
#define ERR_ALLOC_HISTORY  -7
#define ERR_WRITING_SAVE   -8

/** - constantes pour expliciter le code\n
*/
#define LAMB         0
#define WOLF         1
#define HUMAN        0
#define ARTIFICIAL   1
//pour l'IA (valeur retournée pas IA)
#define TOP_LEFT     0
#define TOP_RIGHT    1
#define BOTTOM_LEFT  2
#define BOTTOM_RIGHT 3

/** - constantes pour la gestion des plateformes\n
*/
#define LINUX 0
#define WINDOWS 1

/** - globale pour stocker le chemin d'accès aux fichiers\n
*/
char PATH[128];

/** - définition du système\n
*/

#ifdef _WIN32
#define OPERATING_SYSTEM WINDOWS
#endif

#ifndef _WIN32
#define OPERATING_SYSTEM LINUX
#endif

#include "structures.h"
GtkWidget *GTK_WINTHEME;
t_game **GAME;

//defines des state de t_connection
enum{NETWORK_OPEN,NETWORK_CLOSED};


enum{NEW_POS,CHAT,NAME,PLEASE_CHOOSE,WHAT_YOU_ARE,YOU_DONT_PLAY,GAME_OVER,PLAY_AGAIN};
///types de packets
//new_pos. info en + : t_history
//chat. info en + : le message str (char*)
//please_choose : quel joueur tu veux faire ?
//what_you_are : tu feras tel joueur (dans un deuxième temps). info en + : int du camp qu'on doit jouer
//you_dont_play : c'est à moi de jouer, tu ne joues pas
//game_over : fin de de jeu. info en + : int : si c'est le récepteur du packet qui a gagné.
//play_again : dis au joueur auquel on envoit le paquet qu'on veut rejouer

#endif
