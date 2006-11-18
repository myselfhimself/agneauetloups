#ifndef OSH
#define OSH

#include "[DOX]main.h"

/** - d�finition du syst�me\n
*/

#ifdef _WIN32
#define OPERATING_SYSTEM WINDOWS
#endif

#ifndef _WIN32
#define OPERATING_SYSTEM LINUX
#endif

/** - d�finition de la globale PATH : chemin o� trouver les fichiers (d�pend de l'OS)\n
*/

int init_OS_path()
{
	FILE *current_path = NULL;
	strcpy(PATH,"");
	/**  - d�tection du syst�me\n
	 *      -# si windows ne rien faire\n
	 *      -# si linux envoi "pwd" dans un fichier, ouvre le fichier pour r�cup�rer le r�pertoire courant, puis referme et le supprime\n
	*/
	if(OPERATING_SYSTEM == LINUX)
	{
		system("pwd > /current_path");
		if((current_path = fopen("/current_path","r"))==NULL) return ERR_FOPEN_PATH;
		fgets(PATH,-1,current_path);
		fclose(current_path);
		system("rm /current_path");
	}
    strcat(PATH,"console/");
	return SUCCESS;
}

#endif
