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

void clicked(GtkWidget *emitter, t_tout* tout);

/// structure regroupant les informations necessaires a l'affichage d'une animation
typedef struct {
		/// date actuelle en millisecondes dans l'animation
		int time;
		/// duree en millisecondes de l'animation
		int timemax;
		/// index de l'image acutellement affichee de l'animation
		int index;
		/// plus haut index possible pour une image de l'animation
		int indexmax;
		/// tableau de pointeurs sur les images chargees en memoire
		GdkPixbuf **images;
		}t_animation;

/// structure decrivant l'etat d'un agneau
typedef struct {/// index de la case ou est situe l'agneau
		int position;
		/// tableau regroupant les 4 positions autorisees au tour suivant
		int poss[4];
		}t_lamb;

/// structure decrivant l'etat d'un loup
typedef struct {/// index de la case ou est situe le loup
		int position;
		/// tableau regroupant les deux positions autorisees au tour suivant
		int poss[2];
		}t_wolf;

/// structure regroupant les informations des loups et de l'agneau a un instant du jeu
/**
* cette structure est redefinie en memoire a chaque tour. Elle est utilisee lors de la sauvegarde de la partie
* ainsi que lors du rechargement d'une partie sauvegardee.
*/
typedef struct {/// position et deplacements possibles de l'agneau
		t_lamb lamb;
		/// position et deplacements possibles des cinq loups
		t_wolf wolf[5];
		/// index du joueur devant jouer
		int cur_player;
		/// informations sur les deux joueurs : pour chacun s'il est gere par un utilisateur ou par l'ordinateur
		int is_human[2];
		}t_data;

/// structure groupant les donnees necessaire aux fonctionnement du programme
/** 
* l'unique instance de t_tout est pointee par un pointeur appele "tout".
* Cette structure regroupe les pointeurs vers les widgets de la fenetre, les graphiques charges en memoire, l'historique de la partie,
* ainsi que les donnees concernant la situation des pions des differents joueurs a l'instant present
*/

typedef struct {
	/// index du skin en utilisation
	int skin;
	/// tableau de pointeurs sur les boutons
	GtkWidget *button[50];
	/// tableau de pointeurs sur les images fixes
	GdkPixbuf **images;
	/// tableau de pointeurs sur animations
	t_animation *animation;
	/// pointeur sur la barre de status
	GtkWidget *statusbar;
	/// pointeur sur les donnees du jeu a cet instant
	t_data *data;
	/// ancre de la liste chainee d'historique de la partie
	GList *history;
	}t_tout;


			   
#endif
