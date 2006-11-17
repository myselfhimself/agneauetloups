#ifndef IAC
#define IAC

#include "[DOX]main.h"

void preIA(t_game *game,int depth)
{
	int topleft,topright,bottomleft[5],bottomright[5];
	int player = game->data.now->curplayer;
	t_association *pawn=game->pawn;
	int lx  = pawn[0].position.x;    int ly  = pawn[0].position.y;
    int w1x = pawn[1].position.x;    int w1y = pawn[1].position.y;
    int w2x = pawn[2].position.x;    int w2y = pawn[2].position.y;
    int w3x = pawn[3].position.x;    int w3y = pawn[3].position.y;
    int w4x = pawn[4].position.x;    int w4y = pawn[4].position.y;
    int w5x = pawn[5].position.x;    int w5y = pawn[5].position.y;
	if(player == LAMB)
	{
		if(possible_and_free(lx-1,ly+1,pawn))
			topleft = IA(LAMB,depth,lx-1,ly+1,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
		else
			topleft = 0;
		if(possible_and_free(lx+1,ly+1,pawn))
			topright = IA(LAMB,depth,lx+1,ly+1,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
		else
			topright = 0;
		if(possible_and_free(lx-1,ly-1,pawn))
			bottomleft[0] = IA(LAMB,depth,lx-1,ly-1,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
		else
			bottomleft[0] = 0;
		if(possible_and_free(lx+1,ly-1,pawn))
			bottomright[0] = IA(LAMB,depth,lx+1,ly-1,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
		else
			bottomright[0] = 0;
	}
	printf("%d  %d\n%d  %d\n\n",topleft,topright,bottomleft[0],bottomright[0]);
}

int IA(int player,int depth,int lx,int ly,int w1x,int w1y,int w2x,int w2y,int w3x,int w3y,int w4x,int w4y,int w5x,int w5y)
{
	int count = 0,k;
	t_association pawn[6]={{NULL,{lx,ly}},{NULL,{w1x,w1y}},{NULL,{w2x,w2y}},{NULL,{w3x,w3y}},{NULL,{w4x,w4y}},{NULL,{w5x,w5y}}};
	//printf("mouton %d:%d , loups : %d:%d %d:%d %d:%d %d:%d %d:%d\n",lx,ly,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
	if(game_is_over(pawn))
	{
		if(lamb_won(pawn))
		{
			return importance(depth);
		}
		else
		{
			return (-1 * importance(depth));
		}
	}
	if(depth == 0) return 0;
	if(player == LAMB)
	{
		if(possible_and_free(lx+1,ly+1,pawn))
			count += IA(WOLF,depth - 1,lx+1,ly+1,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
		if(possible_and_free(lx+1,ly-1,pawn))
			count += IA(WOLF,depth - 1,lx+1,ly-1,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
		if(possible_and_free(lx-1,ly+1,pawn))
			count += IA(WOLF,depth - 1,lx-1,ly+1,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
		if(possible_and_free(lx-1,ly-1,pawn))
			count += IA(WOLF,depth - 1,lx-1,ly-1,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
	}
	else
	{
		for(k=1;k<6;k++)
		{
			if(possible_and_free(pawn[k].position.x+1,pawn[k].position.y-1,pawn))
			{
				switch(k)
				{
					case 1: count += IA(LAMB,depth - 1,lx,ly,w1x+1,w1y-1,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
							break;
					case 2: count += IA(LAMB,depth - 1,lx,ly,w1x,w1y,w2x+1,w2y-1,w3x,w3y,w4x,w4y,w5x,w5y);
							break;
					case 3: count += IA(LAMB,depth - 1,lx,ly,w1x,w1y,w2x,w2y,w3x+1,w3y-1,w4x,w4y,w5x,w5y);
							break;
					case 4: count += IA(LAMB,depth - 1,lx,ly,w1x,w1y,w2x,w2y,w3x,w3y,w4x+1,w4y-1,w5x,w5y);
							break;
					case 5: count += IA(LAMB,depth - 1,lx,ly,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x+1,w5y-1);
							break;
				}
			}
			if(possible_and_free(pawn[k].position.x-1,pawn[k].position.y-1,pawn))
			{
				switch(k)
				{
					case 1: count += IA(LAMB,depth - 1,lx,ly,w1x-1,w1y-1,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
							break;
					case 2: count += IA(LAMB,depth - 1,lx,ly,w1x,w1y,w2x-1,w2y-1,w3x,w3y,w4x,w4y,w5x,w5y);
							break;
					case 3: count += IA(LAMB,depth - 1,lx,ly,w1x,w1y,w2x,w2y,w3x-1,w3y-1,w4x,w4y,w5x,w5y);
							break;
					case 4: count += IA(LAMB,depth - 1,lx,ly,w1x,w1y,w2x,w2y,w3x,w3y,w4x-1,w4y-1,w5x,w5y);
							break;
					case 5: count += IA(LAMB,depth - 1,lx,ly,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x-1,w5y-1);
							break;
				}
			}
		}
	}
	return count;
}

#endif
