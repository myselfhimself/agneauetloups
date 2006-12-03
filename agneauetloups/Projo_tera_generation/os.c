#include "main.h"

/** - définition de la globale PATH : chemin où trouver les fichiers (dépend de l'OS)\n
*/

int init_OS_path()
{
	FILE *current_path = NULL;
	strcpy(PATH,"");
	/**  - détection du système\n
	 *      -# si windows ne rien faire\n
	 *      -# si linux envoi "pwd" dans un fichier, ouvre le fichier pour récupérer le répertoire courant, puis referme et le supprime\n
	*/
	if(OPERATING_SYSTEM == LINUX)
	{
		system("pwd > current_path");
		if((current_path = fopen("current_path","r"))==NULL) return ERR_FOPEN_PATH;
		fgets(PATH,-1,current_path);
		fclose(current_path);
		system("rm current_path");
	}
    	strcat(PATH,"themes/");
	return SUCCESS;
}
