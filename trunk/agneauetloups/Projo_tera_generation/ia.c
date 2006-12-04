#include "main.h"

void preIA(t_game *game,int depth)
{
	time_t t0,t;
    int topleft,topright,bottomleft[5],bottomright[5],sum,i,min=0,minplace=0;
	int player = game->data.now->curplayer;
	t_association *pawn=game->pawn;
	int lx  = pawn[0].position.x;    int ly  = pawn[0].position.y;
    int w1x = pawn[1].position.x;    int w1y = pawn[1].position.y;
    int w2x = pawn[2].position.x;    int w2y = pawn[2].position.y;
    int w3x = pawn[3].position.x;    int w3y = pawn[3].position.y;
    int w4x = pawn[4].position.x;    int w4y = pawn[4].position.y;
    int w5x = pawn[5].position.x;    int w5y = pawn[5].position.y;
    t0 = time(NULL);
	/** si agneau :\n
	* - si possible et pas trop éloigné lancé l'IA sur l'emplacement en haut à gauche\n
	* - si possible et pas trop éloigné lancé l'IA sur l'emplacement en haut à droite\n
	* - si possible et pas trop éloigné lancé l'IA sur l'emplacement en bas à gauche\n
	* - si possible et pas trop éloigné lancé l'IA sur l'emplacement en bas à droite\n
	*/
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
	    /** - si la somme des probabilités est jugée trop petite pour avoir de l'importance\n
		* -# avancer aléatoirement, sur le devant si possible\n
		*/
		if(abs(sum)< 4000)
	    {
            if(possible_and_free(lx+1,ly+1,pawn) && possible_and_free(lx-1,ly+1,pawn)) make_movement(game,lx,ly,9-lx,ly+1);
            else if(possible_and_free(lx-1,ly+1,pawn)) make_movement(game,lx,ly,lx-1,ly+1);
            else if(possible_and_free(lx+1,ly+1,pawn)) make_movement(game,lx,ly,lx+1,ly+1);
            else if(possible_and_free(lx-1,ly-1,pawn)) make_movement(game,lx,ly,lx-1,ly-1);
            else if(possible_and_free(lx+1,ly-1,pawn)) make_movement(game,lx,ly,lx+1,ly-1);
        }
		/** - si la somme des probabilités est très grande alors la solution est évidente et proche\n
		* -# soit elle est en haut à gauche => essai d'y aller\n
		* -# soit elle est en haut à droite => essai d'y aller\n
		*/
        else if(sum>=199999900)
        {
            if(possible_and_free(lx-1,ly+1,pawn)) make_movement(game,lx,ly,lx-1,ly+1);
            else if(possible_and_free(lx+1,ly+1,pawn)) make_movement(game,lx,ly,lx+1,ly+1);
            else if(possible_and_free(lx-1,ly-1,pawn)) make_movement(game,lx,ly,lx-1,ly-1);
            else if(possible_and_free(lx+1,ly-1,pawn)) make_movement(game,lx,ly,lx+1,ly-1);
        }
        else
		/** - sinon allez vers la plus grande des possibilités\n
		*/
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
		/** - puis changer de joueur\n
		*/
    }
    else
    {
        /** si loups :\n
		* - si loups en formation ligne\n
		* -# trouver le prochain loup à déplacer\n
		* -# le déplacer\n
		*/
		if(wolves_in_line(game->pawn))
        {
            i = next_wolf_to_move_in_line(game->pawn);
            if(possible_and_free(game->pawn[i].position.x-1,game->pawn[i].position.y-1,pawn)) make_movement(game,game->pawn[i].position.x,game->pawn[i].position.y,game->pawn[i].position.x-1,game->pawn[i].position.y-1);
            else make_movement(game,game->pawn[i].position.x,game->pawn[i].position.y,game->pawn[i].position.x+1,game->pawn[i].position.y-1);
        }
        else
        {
            /** - sinon se déplacer vers la plus basse probabilité\n
		    */
            for(i=1;i<6;i++)
            {
                if(possible_and_free(pawn[i].position.x-1,pawn[i].position.y-1,pawn))
			    bottomleft[i] = IA(LAMB,depth,pawn[i].position.x-1,pawn[i].position.y-1,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
		        else bottomleft[i] = 0;
		        if(possible_and_free(pawn[i].position.x+1,pawn[i].position.y-1,pawn))
			    bottomright[i] = IA(LAMB,depth,pawn[i].position.x+1,pawn[i].position.y-1,w1x,w1y,w2x,w2y,w3x,w3y,w4x,w4y,w5x,w5y);
		        else bottomright[i] = 0;
		    }
		    min = pow(2,sizeof(int)*8-1)-2;
		    for(i=1;i<6;i++)
            {
                if((min > bottomleft[i]) && possible_and_free(pawn[i].position.x-1,pawn[i].position.y-1,pawn)) {min = bottomleft[i];minplace = i;}
                if((min > bottomright[i]) && possible_and_free(pawn[i].position.x+1,pawn[i].position.y-1,pawn)) {min = bottomright[i];minplace = 10*i;}
            }
            if(minplace < 10) make_movement(game,game->pawn[minplace].position.x,game->pawn[minplace].position.y,game->pawn[minplace].position.x-1,game->pawn[minplace].position.y-1);
            else make_movement(game,game->pawn[minplace/10].position.x,game->pawn[minplace/10].position.y,game->pawn[minplace/10].position.x+1,game->pawn[minplace/10].position.y-1);
        }
        /** - changer de joueur\n
        */
        game->data.now->curplayer = !game->data.now->curplayer;
    }
}

int IA(int player,int depth,int lx,int ly,int w1x,int w1y,int w2x,int w2y,int w3x,int w3y,int w4x,int w4y,int w5x,int w5y)
{
	int count = 0,k;
	t_association pawn[6]={{NULL,{lx,ly}},{NULL,{w1x,w1y}},{NULL,{w2x,w2y}},{NULL,{w3x,w3y}},{NULL,{w4x,w4y}},{NULL,{w5x,w5y}}};
	/** - si le jeu est terminé\n
	* -# si l'agneau a gagné retourner un coefficient d'issue positif\n
	* -# si les loups ont gagnés retourner un coefficient d'issue négatif\n
	*/
	if(game_is_over(pawn))
	{
		if(lamb_won(pawn))
		{
			count = importance(depth);
		}
		else
		{
			count = (-1 * importance(depth));
		}
	}
	/** - si la profondeur maximale a été atteinte retourner zéro\n
	*/
	else if(depth == 0) count = 0;
	/** - si le joueur est agneau : rapeller l'IA récursivement sur les 4 positions possibles\n
	*/
	else if(player == LAMB)
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
	/** - si le joueur est loup : rapeller l'IA récursivement sur les 10 positions possibles\n
	*/
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
