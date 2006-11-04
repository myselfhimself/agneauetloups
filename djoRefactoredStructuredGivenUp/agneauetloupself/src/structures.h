#ifndef STRUCTH
#define STRUCTH

//types de positions (quoi comme nature pour une case ? quoi y afficher ?)
//et types de camps

//<=> not terrain == 0 pour pouvoir faire un test pour renseigner sur
#define NONE 0
#define LAMB 1
#define WOLF 2
//<=> terrain ou l'on peut mettre un pion
#define TERRAIN 3
#define LAMB_SELECTED 4
#define WOLF_SELECTED 5

//directions d'avancement pour les pions
#define UP -1
#define DOWN 1

//comment le joueur jouera (actor_type)
#define IA 0
#define USER 1


//coordonnees correspondantes pour un bouton
typedef struct
{
	int x,y;
}t_coords;

//structure réunissant GUI et data pour un bouton
//l'ensemble de ces structures pour chaque bouton
//doit permettre de mettre a jour l'affichage du jeu d'un coup
//ce n'est pas ici qu'il faut chercher des informations, on ne se contentera que de lire
//ce qu'il y a dans cette structure pour pouvoir mettre a jour le bouton correspondant
typedef struct
{
	GtkWidget* bouton;
	int main_type;
	int forced_type; //prioritaire sur le main type si != NONE
}t_position;

//but : dire qui est qui
//sachant que les loups et l'agneau peuvent partir de l'un ou l'autre cote du plateau
typedef struct
{
	int direction; //ex:UP/DOWN
	int actor_type; //ex:USER/IA
	t_coords* selection;
}t_player;

typedef struct
{
	t_coords loups[5];
	t_coords agneau;
}t_history;

//structure sauvegardable donnant
//on peut aussi y lire l'état du jeu à un certain instant
typedef struct
{
	//---Parties variables----
	t_history now; //donne les coordonnees des differents pions a l'instant present
	int current_player; //ex:LAMB/WOLF
	GList* history; //liste chainee contenant des mayons pointant chacun sur un t_history

	//----Partie fixee-------
	//infos sur les joueurs, leur type, la direction de deplacement de leurs pions (UP/DOWN)
	t_player players[2]; //l'index des cases de ce tableau<=> LAMB/WOLF
}t_data;

typedef struct
{
	t_position positions[10][10]; //ensemble des cases [x][y] ; elles doivent seules permettre l'affichage
	t_data data;//sauvegardable : represente la partie et son historique
	GtkWidget* status_bar;
	GtkWidget* menu;
}t_tout;





#endif