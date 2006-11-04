#include "projet.h"

//fonction de test d'unites
void UT(int testId,t_tout* tout)
{
	switch(testId)
	{
		case SET_PLAYERS:
			UT_set_players(tout);
			break;
		default:
			printf("UT : no corresponding constant");
	}
}

//invente des placements de joueurs et leurs camp
//utilise la fonction game_init qui place ces joueurs dans les donnees et met a jour l'interface
void UT_set_players(t_tout* tout)
{
	int a,b;
	//joueurs un et deux
	t_player p1;
	t_player p2;

	//a represente les valeurs d'actor_type (IA/USER)
	for(a=0;a<2;a++)
	{
		//b represente les valeurs des directions (UP/DOWN)
		for(b=-1;b<2;b+=2)
		{
			p1.direction = b;
			p2.direction = (b == -1) ? 1 : -1;
			p1.actor_type = a;
			p2.actor_type = 1-a;
			players_game_init(p1,p2,tout);
		}
	}
}