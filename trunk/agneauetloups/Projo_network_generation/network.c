#include "main.h"

//toutes les fonctions ici ne nécessitent d'être encadrées par des threads
//elles prennent un certains temps pour s'exécuter sans pour autant être bloquantes
//la fonction network_main lance elle même un thread puis se termine en gardant ce thread allumé
//la fonction network_exit s'occupe de détruire ce thread de nettoyer les variables du côté réseau du jeu

//threads : http://yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html#BASICS

//cr�� et envoie un paquet
void packet_send(int type, void* content)
{
     network_send(packet_make(type,content));
}

///affiche le contenu d'un paquet
void packet_display(t_packet* packet)
{
	int success;
	success = packet != NULL;
	if(!success)
		printf("packet_display : content == NULL. Abandon\n");
	else
	{
		//printf("type:%d\n",packet->type);
		switch(packet->type)
		{
			//CHAT et NAME : on affiche des chaînes de caractères, pas de problème
			case CHAT:
				printf("packet_display : CHAT : %s\n",packet->content);
				break;
			case NAME:
				printf("packet_display : NAME : %s\n",packet->content);
				break;
			case NEW_POS:
				printf("packet_display : NEW_POS : x=%d, y=%d, curplayer=%d\n",((t_history*)packet->content)->lamb.x,((t_history*)packet->content)->lamb.y,((t_history*)packet->content)->curplayer);
				break;
			case PLEASE_CHOOSE:
				printf("packet_display : PLEASE_CHOOSE : tu as ete designe pour choisir ton camp\n");
				break;
			case WHAT_YOU_ARE:
				printf("packet_display : WHAT_YOU_ARE : tu feras tel joueur : %d\n",((int*)(packet->content))[0]);
				break;
			case YOU_DONT_PLAY:
				printf("packet_display : YOU_DONT_PLAY : l'autre va jouer\n");
				break;
			default:
				printf("packet_display : packet->type : type inconnu : %d\n",packet->type);
		}
	}
}

///crée un paquet alloué et y insère les données des paramètres fournis
///met le paquet en network byte order directement
t_packet* packet_make(int type, void* content)
{
	t_packet* packet;
	//utilisation de calloc pour remplir avec des 0
	packet = (t_packet*)calloc(1,sizeof(t_packet));
	packet->type = type;
	//memcpy(dest,src,size)
	//packet->content est un char*, pas de déférencement supplémentaire
	memcpy(packet->content,content,CONTENT_SIZE);
	return packet;
}

//fct callback : ne doit pas figurer ici
int callback_fct(t_packet* data)
{
	int success;
	//t_history temp;
	char* temp;

	success = data != NULL;
	if(!success)
		printf("callback_fct : data == NULL : rien de fait\n");
	else
		packet_display(data);
	return 1;
}

t_network* _net=NULL;
t_game* _game=NULL;
pthread_t _pid = {NULL,0};

///active le mode réseau, initialise des variables réseau
void network_init(t_game* game)
{
	//variables globales pour cette librairie seulement
	_net = &(game->network);
	_game = game;

	_game->use_network = TRUE;
	_net->server.state = NETWORK_CLOSED;
	_net->client.state = NETWORK_CLOSED;
	_net->im_server = FALSE;
}

///tente de rendre un socket réutilisable sur une même machine
///utile dans les cas où un socket n'avait pas été fermé mais est bloqué quand même
///retourne 1 si succès ou 0 sinon
int network_reuse_socket(int sockfd)

{
	int success;
	int yes;	

    #ifndef _WIN32
	success = (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) != -1);
    #else
    success = (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,(char*)&yes,sizeof(int)) != 0);
    #endif

	if (!success)
	{
		printf("n'a pas pu permettre la reutilisation de socket\n");
		#ifndef _WIN32
		perror("setsockopt");
	    #endif
    }
	return success;
}

///ferme/nettoie une connectino qui ne nous sert plus
///retourne 1 si succès, 0 si rien à faire
int network_connection_close(t_connection* connection)
{
	int success;
	success = (connection->state == NETWORK_OPEN);
	if(success)
	{
		#ifdef LINUX
		close(connection->socket);
		#else
		#ifdef WINDOWS
		closesocket(connection->socket);
		#endif
		#endif
		connection->state = NETWORK_CLOSED;
		free(connection->address);
	}
}

///à utiliser dans les différentes fonctions d'écriture : regarde si network_init a été exécuté
///regarde si la structure pointée par le t_connection* est bien inutilisée
///met une erreur dans la console si ce n'est pas le cas
int network_check_unused(t_connection* connection)
{
	int success;
	//regarde si network_init a été lancé
	success = _game != NULL && _net != NULL;
	if(!success)
             printf("network_check_unused : lancer network_init en premier\n");
	else
	{
		//regarde si l'option use_network est bien activée
		success = _game->use_network != FALSE;
		if(!success)
			printf("network_check_unused : erreur : _game->use_network == FALSE\n");
		else
		{
			//si le pointeur passé ne vaut pas NULL
			if(connection != NULL)
			{
				//on regarde si la connection était bien fermée (en vue d'être réutilisée)
				success = connection->state != NETWORK_OPEN;
				if(!success)
					printf("network_check_unused : connection ouverte ou qui vaut une valeur aléatoire\n");
				//si la connection était bien fermée, on regarde si on n'est pas déjà serveur alors qu'on veut faire client
				//et vice versa
				else
				{
					//Etude de l'adresse de la connection passée
					//si c'est pour le serveur
					if(connection == &(_net->server))
						//on regarde si le client est fermé
						success = _net->client.state == NETWORK_CLOSED;
					//si c'est pour le client
					else
					if(connection == &(_net->client))
						//on regarde si le serveur est fermé
						success = _net->server.state == NETWORK_CLOSED;
					else
						printf("network_check_unused : parametre connection passe bizarre. Continuation\n");
					if(!success)
						printf("network_check_unused : l'autre connection est en cours d'utilisation ;\npas de travail possible sur cette connection\n");
				}
			}//sinon : c'est qu'on ne voulait pas tester si loin
		}
	}
	return success;
}

///les champs du pointeur t_connection* donné
void network_connection_fill(t_connection* connection,int sockfd,struct sockaddr_in* addr)
{
	connection->socket = sockfd;
	connection->address = addr;
	connection->state = NETWORK_OPEN;
}


//retravaillé du projet happycoders/libsocket
///essaye d'allouer et remplir une structure d'adresse inet correspondante aux host et port
///retourne le pointeur sur cette structure ou NULL si le domaine host n'est pas reconnu
struct sockaddr_in* network_make_address(char* host, char* port)
{
	struct hostent      *he;
	struct sockaddr_in*  addr=NULL; //NULL : resultat si echec
    int i_port;
	char host2[15];

	//on réécrit host 
	if(host == NULL)
	{
		strcpy(host2,"localhost");
		host = host2;
	}
	//chope une structure qui contient des infos sur l'host (ip etc..)
	he = gethostbyname(host);
	i_port = atoi(port);
	//s'il y a eu une erreur pour convertir le port en char ou pour trouver l'adresse correspondante au string donné
	if (!he || !port)
	{
		printf("make_addr : mauvaise adresse ou port : %s:%s\n",host,port);
		#ifndef _WIN32
		herror("gethostbyname");
	    #endif
    }
	//si pas eu de problème pour trouver une correspondance aux adresse:port données
	else
	{
		//allocation et remplissage avec des zéros
		addr = (struct sockaddr_in*)calloc(1,sizeof(struct sockaddr_in));

		
		//remplissage des champs
		//Remarque : prend la première adresse dans la liste des adresses proposées pour l'hôte
		addr->sin_addr = *((struct in_addr *)he->h_addr); //in_addr existe sous windows
		addr->sin_port = htons(i_port);
		addr->sin_family = AF_INET;
	}
	return addr;
}

//----------------------FONCTIONS CLIENT------------------------------
///tente de se connecter à un serveur
int network_client_run(char* ip,char* port)
{
	int success;
	int client_sockfd;
	struct sockaddr_in* client_addr;

	success = network_check_unused(&(_net->client));
	
	if(!success)
		printf("network_client_run : connection deja ouverte. Annulation.\n");
	else
	{
		//ouverture de socket
		client_sockfd = socket(PF_INET,SOCK_STREAM,0);
		
		//écriture en bits de l'adresse à contacter
		client_addr = network_make_address(ip,port);
	
		success = (client_addr != NULL);
		//si n'a pas pu trouver une adresse correspondante aux strings données
		if(!success)
			printf("network_client_run : impossible d'etablir l'adresse correspondante : %s:%s\n",ip,port);
		//sinon : si on a pu trouver une adresse
		else
		{
			//remarque : l'affichage des erreurs est déjà fait dans network_reuse_socket ; cette fonction renvoie 0 ou 1 comme on l'attend
			//essaye de rendre réutilisable le socket
			success = network_reuse_socket(client_sockfd);
			if(success)
			{
				//tentative de connection au serveur
				//client_addr est juste utilisée en lecture par connect
				success = connect(client_sockfd,(struct sockaddr*)client_addr,sizeof(struct sockaddr)) != -1;
				
				if(!success)
				{
					printf("network_client_run : erreur de connection à %s:%s\n",ip,port);
					perror("connect");
				}
				else
				{
					//remplissage des informations dans la structure network
					_net->client.state = NETWORK_OPEN;
					_net->client.address = client_addr;
					_net->client.socket = client_sockfd;
					printf("connection etablie : %s:%s\n",ip,port);
					network_main(callback_fct);
				}
			}
		}
	}
	return success;
}

void network_simple_chat()
{
	char txt[100];
	t_packet* packet;
	txt[0] = '\0';
	while(strcmp(txt,"/quit") != 0)
	{
		printf(">");
		fgets(txt,CONTENT_SIZE,stdin);
		packet = packet_make(CHAT,txt);
		network_send(packet);
	}
}

//code utilisé du tutoriel sur les sockets de "beej"
///envoie une donnée à l'autre partie
///s'occupe d'envoyer tout le contenu en gérant les cas où les envois ne peuvent se faire en une fois(problème matériel)
///renvoie 1 si le transfert a marché ou 0 s'il y a eu des erreurs
int network_send(t_packet* packet)
{
	int total=0;
	int n;
	int success;
	
	//vérifie que la taille du paquet a bien été fournie et que la connection pour envoyer est initalisée
	success = packet != NULL && _net->client.state == NETWORK_OPEN;
	if(!success)
		printf("network_send : arg 2 : taille du packet nulle ou incorrecte ou connection client non encore ouverte\n");
	else
		while(total < PACKET_SIZE)
		{
			//n prend ce que retourne send : le nombre bits envoyés avec succès
			n = send(_net->client.socket,(char*)packet+total,PACKET_SIZE-total,0);
			//si erreur dans l'envoi
			success = (n!=-1);
			if(!success)
			{
				//affichage de l'erreur donnée par le système
				perror("send");
				break;
			}
			total += n;
		}
	return success;
}

///cette fonction ne doit pas être lancée par la main. Voir network_main qui crée un thread pour elle.
///reçoit en paramètre un pointeur sur la fonction à appeler quand réception d'un paquet en lui passant le paquet en paramètre
///le callback doit renvoyer 0 pour signifier qu'il faut arrêter de recevoir des données
void* network_receive(void* on_recv)
{
	//structure ou la donnée écrite sera reçue avant de l'envoyer au callback on_recv
	t_packet* data;
	int pleaseStop=0;
	int recv_return;	

	printf("network_receive\n");
	while(1)
	{
		data = (t_packet*)calloc(1,PACKET_SIZE);
		//recoit une donnée et l'écrit dans *data; MSG_WAITALL force l'attente que toute la taille précisée ait été reçue
		recv_return = recv(_net->client.socket,(char*)data,PACKET_SIZE,0);
		//appel du callback en lui envoyant la donnée qu'on vient de recevoir
		//on doit caster le pointeur en pointeur sur fonction pour pouvoir l'utiliser
		//si recv a reçu quelque chose != 0 (pas une déconnection du client distant)
		switch(recv_return)
		{
			case -1:
				printf("erreur de reception\n");
				perror("recv");
				pleaseStop  =1;
				break;
			case 0:
				printf("le client distant a ferme la connection\n");
				//fin de la boucle de réception :
				pleaseStop = 1;
				break;
			default:
				//printf("paquet recu : recv_return=%d, content : %c, is null : %d\n",recv_return,*(char*)data,data==NULL);
				//appel du callback et réception du retour de l'appel
				pleaseStop = !((int (*) (t_packet*)) on_recv) (data);
		}
		//si on a reçu l'information comme quoi il faut s'arrêter par l'appel de la fonction callback
		if(pleaseStop)
			break;
			//pthread_exit(NULL);
	}
	printf("fin de la reception\n");
	
	//il n'y a plus rien de lancé, il vaut mieux tout fermer ; les structures seront réécrites
	network_exit();

	//se termine soi même
	//pthread_exit(NULL); //pas nécessaire : network_exit() s'en occupera
}
///lance un thread qui se charge d'écouter les réceptions et se quitte (sans quitter le thread)
///le premier paramètre est un pointeur sur la fonction callback à appeler quand une donnée est reçue
//la fct callback doit retourner un void* parce que pthread n'accepte que des fonctions avec un tel prototype
/*    int pthread_create(pthread_t * thread, 
                       const pthread_attr_t * attr,
                       void * (*start_routine)(void *), 
                       void *arg);
*/
int network_main(int (*on_recv) (t_packet*))
{
	int success;
	success = on_recv != NULL;
	if(!success)
		printf("network_main : pas de fonction callback donnee ! Annulation\n");
	else
		success = !pthread_create((pthread_t*)&_pid,NULL,network_receive,on_recv);
		//si le thread a été créé
		if(success)
			//on fait que quand il se terminera, on pourra réutiliser la mémoire et le cpu utilisé
			pthread_detach((pthread_t)_pid);
	return success;
}



int network_exit()
{
	_game->use_network = FALSE;
	network_server_shutdown();
	network_client_shutdown();
	_net->im_server = FALSE;
	printf("fin du reseau\n");
}

//----------------------FONCTIONS SERVEUR-----------------------------

///initialise un serveur : ouvre un port local
///retourne succes : 1, echec : 0
///network_init doit avoir été lancé
int network_server_run(char* port)
{
	//socket local qui sera lié à un port ouvert local
	int local_sockfd;
	//attention : c'est un pointeur !
	struct sockaddr_in* local_addr;
	int yes=1; // pour setsockopt
	#ifdef _WIN32
	WSADATA WSAData;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    #endif
	//succes dans l'exécution du programme
	int success;

	//vérifie qu'on n'est pas en train de relancer un serveur
		//succès si le serveur était "fermé" (au lieu d'ouvert)
	success = network_check_unused(&(_net->server));
	if(!success)
		printf("network_server_run : serveur deja initialise : abandon, lancer network_server_shutdown pour l'eteindre\n");
	else
	{		
		//ouverture d'un socket pour internet en TCP (pas besoin d'envoyer l'adresse du destinataire à chaque fois)
		//support IPV4 seulement
		local_sockfd = socket(PF_INET,SOCK_STREAM,0);
		
		#ifdef _WIN32
        success = (local_sockfd != INVALID_SOCKET);
        #else
		success = (local_sockfd != 0);
		#endif
        //si erreur d'ouverture de socket
		if(!success)
		{
			printf("network_server_run : erreur d'ouverture de socket\n");
            #ifndef _WIN32
			perror("socket");
			#endif
		}
		//sinon
		else
		{
			//les erreurs sont déjà gérées dans network_resuse_socket
			//essaye de rendre réutilisable le socket
			success = network_reuse_socket(local_sockfd);
			if(success)
			{
					//on essaye de lier le socket à un port local
				//remplit une structure sockaddr_in
				local_addr = network_make_address("localhost",port);
				
				//si on n'a pas réussi à écrire la structure adresse ("localhost" n'existe pas..)
				success = (local_addr != NULL);
				if(!success)
					//make_address s'est déjà chargé de dire quel est le port qui pose probleme
					printf("network_server_run : echec : localhost est indefini ?\n");
				//si c'est bon, "localhost" existe
				else
				{
					//liage du port à l'adresse locale
					success = bind(local_sockfd,(struct sockaddr*)local_addr,sizeof(struct sockaddr));
					//réussite du bind, si son retour n'est pas négatif
					success = !(success < 0);
					if(!success)
					{
						printf("network_server_run : n'a pas pu lier le socket au port local : %s\n",port);
						perror("bind");
					}
					else
					{
						//on recopie les infos dans la structure _net->server du jeu
						network_connection_fill(&(_net->server),local_sockfd,local_addr);
						_net->im_server = TRUE;
					}
				}
			}
		}
	}
	//si tout a bien marché
	if(success)
	{
		printf("network_server_run : succes dans le binding\n");
		//lancement d'un thread pour network_server_accept()
		success = !pthread_create((pthread_t *)&_pid,NULL,network_server_accept,NULL);
		if(!success)
			printf("network_server_run : succes dans la creation de thread pour network_server_accept\n");
		else
		{
			printf("network_server_run : network_server_accept() lance\n");
			//permettre de la réutilisation de la mémoire et du cpu utilisé par le thread quand il se quittera
			pthread_detach((pthread_t)_pid);
		}
	}
	return success;
}

//le thread en question à quitter est network_receive
int network_client_shutdown()
{
	int success;
	success = _net->client.state == NETWORK_OPEN;
	//si on était client
	if(success)
	{
		printf("network_client_shutdown : _net->client.state == NETWORK_OPEN : client potentiellement lance\n");
		network_connection_close(&(_net->server));

		printf("network_client_shutdown : network_server_accept pas termine; fermeture forcee\n");
		#ifndef _WIN32
        kill(_pid,SIGTERM);
	    #else
	    pthread_kill(_pid,SIGTERM);
	    #endif
     }
	return success;
}


//le thread en question à quitter est network_server_accept()
int network_server_shutdown()
{
	int success;
	success = _net->im_server && _net->server.state == NETWORK_OPEN;
	//si on était serveur
	if(success)
	{
		printf("network_server_shutdown : _net->im_server VRAI : serveur potentiellement lance\n");
		_net->im_server = FALSE;
		network_connection_close(&(_net->server));

			printf("network_server_shutdown : network_server_accept pas termine; fermeture forcee\n");
			#ifndef _WIN32
            kill(_pid,SIGTERM);
		    #else
		    pthread_kill(_pid,SIGTERM);
		    #endif
}
	return success;
}

///une fois network_server_init lancé, écoute les connections sur le socket ouvert et en établit une seule
void* network_server_accept(void * none)
{
	int success;
	int remote_sockfd;
	struct sockaddr_in* remote_addr;
	int remote_addr_size;
	
	//doit contenir la taille de la structure remote_addr que accept() réécrira
	remote_addr_size = sizeof(struct sockaddr);

	printf("accepting\n");
	//si la connection n'était pas ouverte
	success = _net->server.state == NETWORK_OPEN;
	if(!success)
		printf("network_server_accept : connection non ouverte, utiliser network_server_init\n");
	//sinon, on peut travailler
	else
	{
		//alloue et remplit l'adresse avec des zéros
		remote_addr = (struct sockaddr_in*)calloc(1,sizeof(struct sockaddr_in));
		
		//configuration du nombre de connections maximal en attente
		listen(_net->server.socket,1);

		//attend des connection, une fois une trouvée, 
			//crée un socket connecté, retourne son file descripteur->remote_sockfd, remplit l'adresse
		printf("network_server_accept : accepting connections\n");
		remote_sockfd = accept(_net->server.socket,(struct sockaddr*)remote_addr,&remote_addr_size);
		
		//si la connection qui devait s'établir a échoué
		success = (remote_sockfd != -1);
		if(!success)
		{
			printf("network_server_accept : probleme d'acception de connection\n");
			perror("accept");
		}
		else
		{		//si la connection a bien marché
			//remplit les champs pour la connection de type _net->/_net->
			network_connection_fill(&(_net->client),remote_sockfd,remote_addr);
			
			//ferme la connection d'écoute / nettoie les structures
			network_connection_close(&(_net->server));
		
			//dit l'adresse de l'ordinateur avec lequel on vient d'établir une connection
			printf("connection etablie avec : %s\n",inet_ntoa(remote_addr->sin_addr));
			network_main(callback_fct);
		}
	}
	//pas de retour
	//cette fonction où on est, est un thread. On le ferme.
	pthread_exit(NULL);
}
