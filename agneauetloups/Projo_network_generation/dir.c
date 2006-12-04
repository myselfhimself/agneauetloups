#include "main.h"

t_wordlist *get_themes_files(char *extension)
{
	FILE *fp;
	char buffer[2048],buffer2[2048],car,command[128],path[128];
	t_wordlist *wordlist;
	int i=0,j=0;
	int word=0,nbword=0;
	
	sprintf(path,"cd %s/themes",PATH);
	system(path);
	if(OPERATING_SYSTEM == WINDOWS)
	{
		sprintf(command,"dir /B /A:-D themes\\*.%s > fichiers.list",extension);
	}
	else
	{
		sprintf(command,"ls  themes | grep .%s > fichiers.list",extension);
	}
	system(command);
	fp=fopen("fichiers.list","rb");
	car = fgetc(fp);
	while(!feof(fp))
	{
		buffer[i] = car;
		if(car == '\n') nbword++;
		i++;
		car = fgetc(fp);
	}
	buffer[i]='\0';
	fclose(fp);
	wordlist = (t_wordlist*)malloc(sizeof(t_wordlist));
	wordlist->nbwords = nbword;
	wordlist->word = (char**)malloc(nbword*sizeof(char*));
	for(i=0;i<strlen(buffer);i++)
	{
		car = buffer[i];
		if(car != '\n')
		{
			buffer2[j] = car;
			j++;
		}
		else
		{
			buffer2[j]='\0';
			wordlist->word[word] = (char*)malloc((strlen(buffer2)+1)*sizeof(char));
			strcpy(wordlist->word[word],buffer2);
			word++;
			j = 0;
		}
	}
	if(OPERATING_SYSTEM == WINDOWS)
	{
		system("del fichiers.list");
	}
	else
	{
		system("rm fichiers.list");
	}
	printf("%d fichier%s correspondant%s\n",wordlist->nbwords,(wordlist->nbwords>1)?"s":"",(wordlist->nbwords>1)?"s":"");
	for(i=0;i<nbword;i++) printf("%s\n",wordlist->word[i]);
	return wordlist;
}

