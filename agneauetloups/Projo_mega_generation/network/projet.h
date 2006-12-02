#ifndef PROJETH
#define PROJETH

#define LINUX

#include <stdio.h>
#include <string.h> //strcpy

#include <sys/socket.h> //bind() socket() accept() struct sockaddr
#include <netinet/in.h> //pour struct sockaddr_in
#include <netdb.h> //pour hostent, struct hostent* gethostbyname(char*)
#include <arpa/inet.h> //char *inet_ntoa(struct in_addr in); (done l'ip string d'une adresse bits)
#include <stdlib.h> //calloc
#include <unistd.h> //close(fd) pour fermer un socket, sleep(nbseconds)
#include <pthread.h> //threads : pthread_create, pthread_exit. Utiliser -lpthread dans la compilation
#include <signal.h> //pour kill(pid,signal) http://forums.devshed.com/c-programming-42/c-kill-402555.html

/**ordre des commandes :
* client et serveur :
* network_init(t_game* game);
* puis serveur seulement :
* network_server_init(char* port);
* network_server_accept();
* ou client seulement :
* network_client_connect(char* ip,char* port);
*/

//TODO : check de l'état OPEN CLOSE dans network_server_bind
//TODO : network_server_accept

//STRUCTURES DE DONNEES

//defines des state de t_connection
enum{NETWORK_OPEN,NETWORK_CLOSED};
enum{FALSE,TRUE};
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


typedef struct
{
	int use_network;
	t_network network;
}
t_game;

typedef struct
{
	int x;
	int y;
	int curplayer;
}
t_history;

///types de packets
//new_pos. info en + : t_history
//chat. info en + : le message str (char*)
//choice_request : quel joueur tu veux faire ?
//choice : tu feras tel joueur (dans un deuxième temps). info en + : int du camp qu'on doit jouer
//you_dont_play : c'est à moi de jouer, tu ne joues pas
//game_over : fin de de jeu. info en + : int : si c'est le récepteur du packet qui a gagné.
//play_again : dis au joueur auquel on envoit le paquet qu'on veut rejouer
enum{NEW_POS,CHAT,NAME,CHOICE_REQUEST,WHAT_YOU_ARE,YOU_DONT_PLAY,GAME_OVER,PLAY_AGAIN};
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



//PROTOTYPES


///active le mode réseau, initialise des variables réseau
void network_init(t_game* game);

///tente de rendre un socket réutilisable sur une même machine
///utile dans les cas où un socket n'avait pas été fermé mais est bloqué quand même
///retourne 1 si succès ou 0 sinon
int network_reuse_socket(int sockfd);

///ferme/nettoie une connectino qui ne nous sert plus
///retourne 1 si succès, 0 si rien à faire
int network_connection_close(t_connection* connection);

///à utiliser dans les différentes fonctions d'écriture : regarde si network_init a été exécuté
///regarde si la structure pointée par le t_connection* est bien inutilisée
///met une erreur dans la console si ce n'est pas le cas
int network_check_unused(t_connection* connection);

///les champs du pointeur t_connection* donné
void network_connection_fill(t_connection* connection,int sockdf,struct sockaddr_in* addr);

//retravaillé du projet happycoders/libsocket
///essaye d'allouer et remplir une structure d'adresse inet correspondante aux host et port
///retourne le pointeur sur cette structure ou NULL si le domaine host n'est pas reconnu
struct sockaddr_in* network_make_address(char* host, char* port);

//----------------------FONCTIONS CLIENT------------------------------
///tente de se connecter à un serveur
int network_client_run(char* ip,char* port);

//code utilisé du tutoriel sur les sockets de "beej"
///envoie une donnée à l'autre partie
///s'occupe d'envoyer tout le contenu en gérant les cas où les envois ne peuvent se faire en une fois(problème matériel)
///renvoie 1 si le transfert a marché ou 0 s'il y a eu des erreurs
int network_send(t_packet*);

///cette fonction ne doit pas être lancée par la main. Voir network_main qui crée un thread pour elle.
///reçoit en paramètre un pointeur sur la fonction à appeler quand réception d'un paquet en lui passant le paquet en paramètre
void* network_receive(void* on_recv);

///lance un thread qui se charge d'écouter les réceptions et se quitte (sans quitter le thread)
///le premier paramètre est un pointeur sur la fonction callback à appeler quand une donnée est reçue
//la fct callback doit retourner un void* parce que pthread n'accepte que des fonctions avec un tel prototype
int network_main(int (*on_recv) (t_packet*));

void network_simple_chat();

t_packet* packet_make(int type, void* content);
void packet_diplay(t_packet*);

int network_exit();

//----------------------FONCTIONS SERVEUR-----------------------------

///initialise un serveur : ouvre un port local
///retourne succes : 1, echec : 0
///network_init doit avoir été lancé
int network_server_run(char* port);

int network_server_shutdown();

///une fois network_server_init lancé, écoute les connections sur le socket ouvert et en établit une seule
void* network_server_accept(void * none);


#endif 
