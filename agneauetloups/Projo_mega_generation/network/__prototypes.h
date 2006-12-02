#include "projet.h"

//toutes les fonctions ici ne nécessitent d'être encadrées par des threads
//elles prennent un certains temps pour s'exécuter sans pour autant être bloquantes
//la fonction network_main lance elle même un thread puis se termine en gardant ce thread allumé
//la fonction network_exit s'occupe de détruire ce thread de nettoyer les variables du côté réseau du jeu

// TODO : threads : http://yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html#BASICS
// TODO : rendre network_server_accept threadé

t_network* _net=NULL;
t_game* _game=NULL;
int _pid=0;

///active le mode réseau, initialise des variables réseau
void network_init(t_game* game)

///tente de rendre un socket réutilisable sur une même machine
///utile dans les cas où un socket n'avait pas été fermé mais est bloqué quand même
///retourne 1 si succès ou 0 sinon
int network_reuse_socket(int sockfd)

///ferme/nettoie une connectino qui ne nous sert plus
///retourne 1 si succès, 0 si rien à faire
int network_connection_close(t_connection* connection)

///à utiliser dans les différentes fonctions d'écriture : regarde si network_init a été exécuté
///regarde si la structure pointée par le t_connection* est bien inutilisée
///met une erreur dans la console si ce n'est pas le cas
int network_check_unused(t_connection* connection)

///les champs du pointeur t_connection* donné
void network_connection_fill(t_connnection* connection,int sockdf,struct sockaddr_in* addr)

//retravaillé du projet happycoders/libsocket
///essaye d'allouer et remplir une structure d'adresse inet correspondante aux host et port
///retourne le pointeur sur cette structure ou NULL si le domaine host n'est pas reconnu
struct sockaddr_in* network_make_address(char* host, char* port)

//----------------------FONCTIONS CLIENT------------------------------
///tente de se connecter à un serveur
int network_client_run(char* ip,char* port)

//code utilisé du tutoriel sur les sockets de "beej"
///envoie une donnée à l'autre partie
///s'occupe d'envoyer tout le contenu en gérant les cas où les envois ne peuvent se faire en une fois(problème matériel)
///renvoie 1 si le transfert a marché ou 0 s'il y a eu des erreurs
int network_send(void* data, int size)

///cette fonction ne doit pas être lancée par la main. Voir network_main qui crée un thread pour elle.
///reçoit en paramètre un pointeur sur la fonction à appeler quand réception d'un paquet en lui passant le paquet en paramètre
void* network_receive(void (on_recv*) (void*))

///lance un thread qui se charge d'écouter les réceptions et se quitte (sans quitter le thread)
///le premier paramètre est un pointeur sur la fonction callback à appeler quand une donnée est reçue
//la fct callback doit retourner un void* parce que pthread n'accepte que des fonctions avec un tel prototype
int network_main(void* (on_recv*) (void*))

int network_exit()

//----------------------FONCTIONS SERVEUR-----------------------------

///initialise un serveur : ouvre un port local
///retourne succes : 1, echec : 0
///network_init doit avoir été lancé
int network_server_run(char* port)

int network_server_shutdown()

///une fois network_server_init lancé, écoute les connections sur le socket ouvert et en établit une seule
void* network_server_accept(void * none)
