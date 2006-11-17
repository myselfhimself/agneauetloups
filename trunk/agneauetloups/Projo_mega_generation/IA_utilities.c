#ifndef IA_UTILITIESH
#define IA_UTILITIESH

#include "[DOX]main.h"

int importance(int depth)
{
	int result;
	//result =(0-log((1,1 - depth / MAXDEPTH)));
	result = pow(10,depth);
	//result = (int)result;
	//printf(" %d ",result);
	return result;
}

int possible_and_free(int x, int y, t_association pawn[6])
{
	int k;
	if(0<x && 9<x) return 0;
	if(0<y && 9<y) return 0;
	for(k=0;k<6;k++)
	{
		if(pawn[k].position.x == x && pawn[k].position.y == y) return 0;
	}
	return 1;
}

int wolves_won(t_association pawn[6])
{
	int possibilities = 0,k;
	//for(k=0;k<6;k++) printf("%d:%d ",pawn[k].position.x,pawn[k].position.y);
	if(possible_and_free(pawn[0].position.x + 1,pawn[0].position.y + 1,pawn)) possibilities++;
	if(possible_and_free(pawn[0].position.x + 1,pawn[0].position.y - 1,pawn)) possibilities++;
	if(possible_and_free(pawn[0].position.x - 1,pawn[0].position.y + 1,pawn)) possibilities++;
	if(possible_and_free(pawn[0].position.x - 1,pawn[0].position.y - 1,pawn)) possibilities++;
	//if(possibilities==0) {printf("WW");sleep(1000);}
	return (possibilities==0)?1:0;
}

int lamb_won(t_association pawn[6])
{
	int line = 0;
	if(pawn[1].position.y > line ) line = pawn[1].position.y;
	if(pawn[2].position.y > line ) line = pawn[2].position.y;
	if(pawn[3].position.y > line ) line = pawn[3].position.y;
	if(pawn[4].position.y > line ) line = pawn[4].position.y;
	//if(line <= pawn[0].position.y) {printf("LW");/*sleep(1000);*/}
	if(line <= pawn[0].position.y) return 1;
	return 0;
}	

int game_is_over(t_association pawn[6])
{
	if(lamb_won(pawn) || wolves_won(pawn)) return 1;
	return 0;
}

#endif
