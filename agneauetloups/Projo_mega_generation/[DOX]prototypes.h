#ifndef PROTOTYPESH
#define PROTOTYPESH

#include "[DOX]main.h"

// #################################################
// #                  dans IA.c                    #
// #################################################
/** \fn void preIA(t_game *game,int depth)
*
* Objectif(s): commander le noyau de l'IA, g�rer les choix et la difficult�
*
* \param [in,out] game structure principale
* \param [in] depth profondeur de la recherche
*
* \return aucun
*/
void preIA(t_game *game,int depth);

/** \fn int IA(int player,int depth,int lx,int ly,int w1x,int w1y,int w2x,int w2y,int w3x,int w3y,int w4x,int w4y,int w5x,int w5y)
*
* Objectif(s): �valuer la chance de gagner a partir d'un point
*
* \param [in] player joueur en cours
* \param [in] depth profondeur de la recherche
* \param [in] lx abscisse de l'agneau
* \param [in] ly ordonn�e de l'agneau 
* \param [in] w1x abscisse du loup 1
* \param [in] w1y ordonn�e du loup 1
* \param [in] w2x abscisse du loup 2
* \param [in] w2y ordonn�e du loup 2
* \param [in] w3x abscisse du loup 3
* \param [in] w3y ordonn�e du loup 3
* \param [in] w4x abscisse du loup 4
* \param [in] w4y ordonn�e du loup 4
* \param [in] w5x abscisse du loup 5
* \param [in] w5y ordonn�e du loup 5
*
* \return coefficient sur la chance de gagner
*/
int IA(int player,int depth,int lx,int ly,int w1x,int w1y,int w2x,int w2y,int w3x,int w3y,int w4x,int w4y,int w5x,int w5y);

// #################################################
// #             dans IA_utilities.c               #
// #################################################
/** \fn int importance(int depth)
*
* Objectif(s): donner un coefficient a une solution en fonction de sa profondeur
*
* \param [in] depth profondeur de la recherche
*
* \return coefficient sur la chance de gagner
*/
int importance(int depth);

/** \fn int possible_and_free(int x, int y, t_association pawn[6]);
*
* Objectif(s): �valuer si un d�placement est possible
*
* \param [in] x abcisse de l'arriv�e
* \param [in] y ordonn�e de l'arriv�e
* \param [in] pawn[6] positions des pions (animaux)
*
* \return un bool�en, 1 si possible sinon 0
*/
int possible_and_free(int x, int y, t_association pawn[6]);

/** \fn int wolves_won(t_association pawn[6])
*
* Objectif(s): tester si les loups ont gagn�s
*
* \param [in] pawn[6] positions des pions (animaux)
*
* \return un bool�en, 1 si loups vainqueurs sinon 0
*/
int wolves_won(t_association pawn[6]);

/** \fn int lamb_won(t_association pawn[6])
*
* Objectif(s): tester si l'agneau a gagn�
*
* \param [in] pawn[6] positions des pions (animaux)
*
* \return un bool�en, 1 si l'agneau vainqueur sinon 0
*/
int lamb_won(t_association pawn[6]);

/** \fn int game_is_over(t_association pawn[6])
*
* Objectif(s): tester si le jeu est termin� (1 gagnant)
*
* \param [in] pawn[6] positions des pions (animaux)
*
* \return un bool�en, 1 si le jeu est fini sinon 0
*/
int game_is_over(t_association pawn[6]);

// #################################################
// #                 dans GDK.c                    #
// #################################################
/** \fn void gtk_image_superimpose(GtkWidget *eventbox,const gchar *img)
*
* Objectif(s): superposer 2 images, le rose (#FF00FF) de img devient transparent
*
* \param [in] eventbox eventbox contenant l'image de fond
* \param [in] img nom du fichier avec l'image a superposer
*
* \return aucun
*/
void gtk_image_superimpose(GtkWidget *eventbox,const gchar *img);

// dans tests.c
t_association *changeposition(t_association pawn[6], int pawntomove,int direction);
void afficher_console(t_game *game);
void select(GtkWidget *eventbox,gint R,gint V,gint B);

// #################################################
// #                 dans game.c                   #
// #################################################
/** \fn void onclick(GtkWidget *emitter,GdkEventButton *event,t_game *game)
*
* Objectif(s): g�rer les d�placements (callback des eventbox)
*
* \param [in] GtkWidget *emitter eventbox �mettant le signal button_press_event
* \param [in] GdkEventButton *event type d'�v�nement gdk
* \param [in,out] t_game *game structure principale
*
* \return aucun
*/
void onclick(GtkWidget *emitter,GdkEventButton *event,t_game *game);

// #################################################
// #                 dans history.c                #
// #################################################
/** \fn int game_history_add(t_game *game)
*
* Objectif(s): cr�er un historique du jeu
*
* \param [in,out] t_game *game structure principale
*
* \return r�ussite de la fonction
*/
int game_history_add(t_game *game);

/** \fn void game_history_back(t_game *game, int back)
*
* Objectif(s): restaurer un historique du jeu
*
* \param [in,out] t_game *game structure principale
* \param [in,out] int back profondeur du retour arri�re
*
* \return aucun
*/
void game_history_back(t_game *game, int back);

// dans init.c
GtkWidget *window_init(GtkWidget **win);
int game_init(t_game **game,GtkWidget *table,char *player1name,gboolean player1type,gboolean player1animal,char *player2name,gboolean player2type,gboolean player2animal);

// dans OS.h
int init_OS_path();

#endif
