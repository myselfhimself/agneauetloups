#ifndef IAC
#define IAC

#include "[DOX]main.h"

void preIA(t_game *game,int depth)
{
	time_t t0,t;
    int topleft,topright,bottomleft[5],bottomright[5],sum,i;
	int player = game->data.now->curplayer;
	t_association *pawn=game->pawn;
	int lx  = pawn[0].position.x;    int ly  = pawn[0].position.y;
    int w1x = pawn[1].position.x;    int w1y = pawn[1].position.y;
    int w2x = pawn[2].position.x;    int w2y = pawn[2].position.y;
    int w3x = pawn[3].position.x;    int w3y = pawn[3].position.y;
    int w4x = pawn[4].position.x;    int w4y = pawn[4].position.y;
    int w5x = pawn[5].position.x;    int w5y = pawn[5].position.y;
    t0 = time(NULL);
	if(player == LAMB)
	{
		if(possible_and_free(lx-1,ly+1,pawn) && isnt_too_far(lx-1,ly+1,pawn))
			topleft = IA(LAMB,depth,lx-1,ly+1,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
		else
			topleft = 0;
		if(possible_and_free(lx+1,ly+1,pawn) && isnt_too_far(lx+1,ly+1,pawn))
			topright = IA(LAMB,depth,lx+1,ly+1,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
		else
			topright = 0;
		if(possible_and_free(lx-1,ly-1,pawn) && isnt_too_far(lx-1,ly-1,pawn))
			bottomleft[0] = IA(LAMB,depth,lx-1,ly-1,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
		else
			bottomleft[0] = 0;
		if(possible_and_free(lx+1,ly-1,pawn) && isnt_too_far(lx+1,ly-1,pawn))
			bottomright[0] = IA(LAMB,depth,lx+1,ly-1,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
		else
			bottomright[0] = 0;
	
	    t = time(NULL);
	    printf("%d  %d\n%d  %d\n%ld sec\n",topleft,topright,bottomleft[0],bottomright[0],t-t0);
	    sum = topleft + topright + bottomleft[0] + bottomright[0];
	    /*topleft = topleft * 1000 / sum;
	    topright = topright * 1000 / sum;
	    bottomleft[0] = bottomleft[0] * 1000 / sum;
        bottomright[0] = bottomright[0] * 1000 / sum;*/
	    if(abs(sum)< 4000)
	    {
            if(possible_and_free(lx+1,ly+1,pawn) && possible_and_free(lx-1,ly+1,pawn)) make_movement(game,lx,ly,9-lx,ly+1);
            else if(possible_and_free(lx-1,ly+1,pawn)) make_movement(game,lx,ly,lx-1,ly+1);
            else if(possible_and_free(lx+1,ly+1,pawn)) make_movement(game,lx,ly,lx+1,ly+1);
            else if(possible_and_free(lx-1,ly-1,pawn)) make_movement(game,lx,ly,lx-1,ly-1);
            else if(possible_and_free(lx+1,ly-1,pawn)) make_movement(game,lx,ly,lx+1,ly-1);
        }
        else if(sum>=199999900)
        {
            if(possible_and_free(lx-1,ly+1,pawn)) make_movement(game,lx,ly,lx-1,ly+1);
            else if(possible_and_free(lx+1,ly+1,pawn)) make_movement(game,lx,ly,lx+1,ly+1);
            else if(possible_and_free(lx-1,ly-1,pawn)) make_movement(game,lx,ly,lx-1,ly-1);
            else if(possible_and_free(lx+1,ly-1,pawn)) make_movement(game,lx,ly,lx+1,ly-1);
        }
        else
        {
             if(maxi(topleft,topright,bottomleft[0],bottomright[0])== topleft && possible_and_free(lx-1,ly+1,pawn)) make_movement(game,lx,ly,lx-1,ly+1);
             else if(maxi(topleft,topright,bottomleft[0],bottomright[0])== topright && possible_and_free(lx+1,ly+1,pawn)) make_movement(game,lx,ly,lx+1,ly+1);
             else if(maxi(topleft,topright,bottomleft[0],bottomright[0])== bottomleft[0] && possible_and_free(lx-1,ly-1,pawn)) make_movement(game,lx,ly,lx-1,ly-1);
             else if(maxi(topleft,topright,bottomleft[0],bottomright[0])== bottomright[0] && possible_and_free(lx+1,ly-1,pawn)) make_movement(game,lx,ly,lx+1,ly-1);
             else if(possible_and_free(lx-1,ly+1,pawn)) make_movement(game,lx,ly,lx-1,ly+1);
             else if(possible_and_free(lx+1,ly+1,pawn)) make_movement(game,lx,ly,lx+1,ly+1);
             else if(possible_and_free(lx-1,ly-1,pawn)) make_movement(game,lx,ly,lx-1,ly-1);
             else if(possible_and_free(lx+1,ly-1,pawn)) make_movement(game,lx,ly,lx+1,ly-1);
        }
        game->data.now->curplayer = !game->data.now->curplayer;
    }
    else
    {
        if(wolves_in_line(game->pawn))
        {
            i = next_wolf_to_move_in_line(game->pawn);
            if(possible_and_free(game->pawn[i].position.x-1,game->pawn[i].position.y-1,pawn)) make_movement(game,game->pawn[i].position.x,game->pawn[i].position.y,game->pawn[i].position.x-1,game->pawn[i].position.y-1);
            else make_movement(game,game->pawn[i].position.x,game->pawn[i].position.y,game->pawn[i].position.x+1,game->pawn[i].position.y-1);
            game->data.now->curplayer = !game->data.now->curplayer;
        }
        else
        {
            for(i=1;i<6;i++)
            {
                if(possible_and_free(pawn[i].position.x-1,pawn[i].position.y-1,pawn))
			    bottomleft[i] = IA(WOLF,depth,pawn[i].position.x-1,pawn[i].position.y-1,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
		        else bottomleft[i] = 0;
		        if(possible_and_free(pawn[i].position.x+1,pawn[i].position.y-1,pawn))
			    bottomright[i] = IA(WOLF,depth,pawn[i].position.x+1,pawn[i].position.y-1,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
		        else bottomright[i] = 0;
		        printf("[%d][%d]     ",bottomleft[i],bottomright[i]);
            }
        }
    }
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
		if(possible_and_free(lx+1,ly+1,pawn) && isnt_too_far(lx+1,ly+1,pawn))
			count += IA(WOLF,depth - 1,lx+1,ly+1,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
		if(possible_and_free(lx+1,ly-1,pawn) && isnt_too_far(lx+1,ly-1,pawn))
			count += IA(WOLF,depth - 1,lx+1,ly-1,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
		if(possible_and_free(lx-1,ly+1,pawn) && isnt_too_far(lx-1,ly+1,pawn))
			count += IA(WOLF,depth - 1,lx-1,ly+1,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
		if(possible_and_free(lx-1,ly-1,pawn) && isnt_too_far(lx-1,ly-1,pawn))
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
