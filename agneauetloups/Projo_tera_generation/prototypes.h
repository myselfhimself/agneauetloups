#ifndef PROTOTYPESH
#define PROTOTYPESH

#include "main.h"

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
/** \fn int next_wolf_to_move_in_line(t_association pawn[6])
*
* Objectif(s): donner le prochain loup � bouger (cas d'une formation ligne)
*
* \param [in] t_association pawn[6] positions des pions
*
* \pre il faut que les loups soient en formation ligne
*
* \return num�ro du loup � d�placer
*/
int next_wolf_to_move_in_line(t_association pawn[6]);
/** \fn int wolves_in_line(t_association pawn[6])
*
* Objectif(s): tester si les loups sont en formation ligne
*
* \param [in] t_association pawn[6] positions des pions
*
* \return si loups en formation ligne ou non
*/
int wolves_in_line(t_association pawn[6]);
/** \fn int isnt_too_far(int x, int y, t_association pawn[6])
*
* Objectif(s): d�cider si un d�placement agneau est jug� utile pour le calcul des probabilit�s
*
* \param [in] int x abcisse voulue
* \param [in] int y ordonn�e voulue
* \param [in] t_association pawn[6] positions des pions
*
* \return si trop loin ou non
*/
int isnt_too_far(int x, int y, t_association pawn[6]);
/** \fn int maxi(int a, int b, int c, int d)
*
* Objectif(s): calculer le maximum dans un lot de 4 nombres
*
* \param [in] int a premier nombre � comparer
* \param [in] int b deuxi�me nombre � comparer
* \param [in] int c troisi�me nombre � comparer
* \param [in] int d quatri�me nombre � comparer
*
* \return le maximum des 4 nombres
*/
int maxi(int a, int b, int c, int d);
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
/** \fn void make_movement(t_game *game,int x1,int y1,int x2,int y2)
*
* Objectif(s): d�placer un pion
*
* \param [in,out] t_game *game structure principale
* \param [in] int x1 abcisse de d�part
* \param [in] int y1 ordonn�e de d�part
* \param [in] int x2 abcisse d'arriv�e
* \param [in] int y2 ordonn�e d'arriv�e
*
* \return aucun
*/
void make_movement(t_game *game,int x1,int y1,int x2,int y2);

void onrelease(GtkWidget *emitter,GdkEventButton *event,t_game *game);

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

// #################################################
// #                  dans menu.c                  #
// #################################################
/** \fn void onquit(gpointer data, guint callback_action,GtkWidget *widget)
*
* Objectif(s): g�rer le bouton quitter du menu
*
* \param [in] gpointer data non utilis�
* \param [in] guint callback_action non utilis�
* \param [in] GtkWidget *widget non utilis�
*
* \return aucun
*/
void onquit(gpointer data, guint callback_action,GtkWidget *widget);

/** \fn void onabout(gpointer data, guint callback_action,GtkWidget *widget)
*
* Objectif(s): g�rer le bouton about du menu
*
* \param [in] gpointer data non utilis�
* \param [in] guint callback_action non utilis�
* \param [in] GtkWidget *widget non utilis�
*
* \return aucun
*/
void onabout(gpointer data, guint callback_action,GtkWidget *widget);

//change le texte dans la barre de status
/** \fn void set_status_text(char* format_str,char* str)
*
* Objectif(s): changer le texte de la barre de status
*
* \param [in] cha�ne de formattage
* \param [in] cha�ne �ventuellement utilis�e dans la cha�ne de formattage
*
* \return aucun
*/
void set_status_text(char* format_str,char* str);

// #################################################
// #                                                          dans init.c                                                                  #
// #################################################
/** \fn GtkWidget *window_init(GtkWidget **win)
*
* Objectif(s): cr�er l'interface graphique
*
* \param [in] GtkWidget **win adresse du pointeur sur la fen�tre
*
* \return adresse de la table de jeu
*/
GtkWidget *window_init(GtkWidget **win,t_game **game);
/** \fn int game_init(t_game **game,GtkWidget *table,char *player1name,gboolean player1type,gboolean player1animal,char *player2name,gboolean player2type,gboolean player2animal)
*
* Objectif(s): cr�er et initialiser le jeu(structures et terrain)
*
* \param [in,out] t_game **game adresse du pointeur de la structure principale
* \param [in] GtkWidget *table pointeur sur la table de jeu
* \param [in] char *player1name nom du premier joueur
* \param [in] gboolean player1type type du premier joueur (IA/humain)
* \param [in] gboolean player1animal animal du premier joueur (loup/agneau)
* \param [in] char *player2name nom du second joueur
* \param [in] gboolean player2type type du second joueur (IA/humain)
* \param [in] gboolean player2animal animal du second joueur (loup/agneau)
*
* \return succ�s de l'op�ration
*/
int game_init(t_game **game,GtkWidget *table,char *player1name,gboolean player1type,gboolean player1animal,char *player2name,gboolean player2type,gboolean player2animal);

// #################################################
// #                   dans OS.c                   #
// #################################################
/** \fn int init_OS_path()
*
* Objectif(s): g�rer le multiplateforme
*
* \return succ�s de l'op�ration
*/
int init_OS_path();

int save_game(t_game *game, char *path);
t_wordlist *get_themes_files(char *extension);
GtkWidget* create_wintheme();
GtkWidget* lookup_widget(GtkWidget *widget, const gchar *widget_name);
void wintheme();
void go_back(GtkWidget *emitter, gpointer null);
void go_save(GtkWidget *emitter, t_game *game);

#endif
