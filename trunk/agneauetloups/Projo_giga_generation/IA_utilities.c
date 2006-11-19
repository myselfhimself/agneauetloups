#include "main.h"

int next_wolf_to_move_in_line(t_association pawn[6])
{
    int linemin=10,linemax=0,nextwolf=0,i,j,swap,posx[5],posy[5];
    /** - trouve si les loups doivent se déplacer de gauche à droite ou de droite à gauche\n
    * - classe les loups en ordre d'abcisses\n
    * - trouve celui qui n'a pas encore bouger\n
    * - renvoi son numéro\n
    */
    for(i=1;i<6;i++)
    {
        if(pawn[i].position.y > linemax) linemax = pawn[i].position.y;
        if(pawn[i].position.y < linemin) linemin = pawn[i].position.y;
    }
    if(linemin == linemax)
    {
        for(i=1;i<6;i++)
        {
            if(pawn[i].position.x == 9*(linemax%2)) nextwolf = i;
        }
    }
    else
    {
        for(i=0;i<5;i++) {posx[i] = pawn[i+1].position.x; posy[i] = pawn[i+1].position.y;}
        for(i=0;i<6;i++)
        {
            for(j=0;j<4;j++)
            {
                if(posx[j] > posx[j+1])
                {
                    swap = posx[j];
                    posx[j] = posx[j+1];
                    posx[j+1] = swap;
                    swap = posy[j];
                    posy[j] = posy[j+1];
                    posy[j+1] = swap;
                }
            }
        }
        j=0;
        if(linemin%2 == 0)
        {
            for(i=0;i<4;i++)
            {
                if(posy[i] > posy[i+1] && j == 0) j=posx[i];
            }
        }
        else
        {
            for(i=0;i<4;i++)
            {
                if(posy[i] < posy[i+1] && j == 0) j=posx[i+1];
            }
        }
        for(i=1;i<6;i++)
        {
            if( pawn[i].position.x == j) nextwolf = i;
        }
    }
    return nextwolf;
}

int wolves_in_line(t_association pawn[6])
{
    int result=0,linemin=10,linemax=0,i,j,swap,posx[5],posy[5];
    for(i=1;i<6;i++)
    {
        if(pawn[i].position.y > linemax) linemax = pawn[i].position.y;
        if(pawn[i].position.y < linemin) linemin = pawn[i].position.y;
    }
    /** - si les loups sont tous sur la même ligne => retourne 1\n
    * - si l'agneau bloque la progression => retourne 0\n
    * - sinon tester le positionnement :\n
    * -# il faut que les loups soient sur 2 lignes et pas plus\n
    * -# il faut qu'ils aient avancés de gauche à droite ou de droite à gauche (dépend de la ligne)\n
    * -# si vérifié retourne 1\n
    * -# sinon rentourne 0\n
    */
    if(linemin == linemax) result = 1;
    else if(linemax-linemin == 1)
    {
        result = 1;
        for(i=0;i<5;i++) {posx[i] = pawn[i+1].position.x; posy[i] = pawn[i+1].position.y;}
        for(i=0;i<6;i++)
        {
            for(j=0;j<4;j++)
            {
                if(posx[j] > posx[j+1])
                {
                    swap = posx[j];
                    posx[j] = posx[j+1];
                    posx[j+1] = swap;
                    swap = posy[j];
                    posy[j] = posy[j+1];
                    posy[j+1] = swap;
                }
            }
        }
        if(linemin%2 == 0)
        {
            for(i=0;i<4;i++)
            {
                if(posy[i] < posy[i+1]) result=0;
            }
        }
        else
        {
            for(i=0;i<4;i++)
            {
                if(posy[i] > posy[i+1]) result=0;
            }
        }
    }
    i = next_wolf_to_move_in_line(pawn);
    if(!possible_and_free(pawn[i].position.x-1,pawn[i].position.y-1,pawn) && !possible_and_free(pawn[i].position.x+1,pawn[i].position.y-1,pawn)) result = 0;
    return result;
}

int isnt_too_far(int x, int y, t_association pawn[6])
{
    int line = 10;
	if(pawn[1].position.y < line ) line = pawn[1].position.y;
	if(pawn[2].position.y < line ) line = pawn[2].position.y;
	if(pawn[3].position.y < line ) line = pawn[3].position.y;
	if(pawn[4].position.y < line ) line = pawn[4].position.y;
	if(pawn[5].position.y < line ) line = pawn[5].position.y;
	/** - si trop de lignes séparent la ligne voulue et la ligne du loup le plus proche alors retourne 0\n
	* - sinon retourne 1\n
	*/
	if(pawn[0].position.y < line - 2) return 0;
	else return 1;
}

int maxi(int a, int b, int c, int d)
{
    int result = d;
    /** - calcul le plus grand des 4 nombres envoyés et renvoi le plus grand\n
	*/
    if(a>b && a>c && a>d) result = a;
    else if(b>a && b>c && b>d) result = b;
    else if(c>a && c>b && c>d) result =c;
    return result;
}

int importance(int depth)
{
	int result;
	/** - calcul une probabilité en fonction de la profondeur de récursivité (= nombre de coups d'avances)\n
	*/
	result = pow(10,depth);
	return result;
}

int possible_and_free(int x, int y, t_association pawn[6])
{
	int k,ret = 1;
	/** - teste si la case demandée n'est pas en dehors du terrain, sinon retourne 0\n
	*/
	if(0>x || 9<x || 0>y || 9<y) ret = 0;
	/** - teste si la case demandée n'est pas déjà prise par un autre pion, sinon retourne 0"
	* - sinon retourne 1;
	*/
	for(k=0;k<6;k++)
	{
		if(pawn[k].position.x == x && pawn[k].position.y == y) ret = 0;
	}
	return ret;
}

int wolves_won(t_association pawn[6])
{
	int possibilities = 0,k;
	/** - teste et compte les possibilités de déplacement de l'agneau\n
	* - si aucune possibilités retourne 1\n
	* - sinon retourne 0\n
	*/
	if(possible_and_free(pawn[0].position.x + 1,pawn[0].position.y + 1,pawn)) possibilities++;
	if(possible_and_free(pawn[0].position.x + 1,pawn[0].position.y - 1,pawn)) possibilities++;
	if(possible_and_free(pawn[0].position.x - 1,pawn[0].position.y + 1,pawn)) possibilities++;
	if(possible_and_free(pawn[0].position.x - 1,pawn[0].position.y - 1,pawn)) possibilities++;
	return (possibilities==0)?1:0;
}

int lamb_won(t_association pawn[6])
{
	int line = 0,ret=0;
	if(pawn[1].position.y > line ) line = pawn[1].position.y;
	if(pawn[2].position.y > line ) line = pawn[2].position.y;
	if(pawn[3].position.y > line ) line = pawn[3].position.y;
	if(pawn[4].position.y > line ) line = pawn[4].position.y;
	if(pawn[5].position.y > line ) line = pawn[5].position.y;
	/** - calcul de la plus haute ligne occupée par un loup\n
	* - si cette ligne est plus petite ou égale à celle de l'agneau c'est gagné => retourne 1\n
	* - sinon retourne 0\n
	*/
	if(line <= pawn[0].position.y) ret = 1;
	return ret;
}	

int game_is_over(t_association pawn[6])
{
	int ret=0;
	/** - si un gagnant retourne 1\n
	* - sinon retourne 0\n
	*/
    if(lamb_won(pawn) || wolves_won(pawn)) ret = 1;
	return ret;
}
