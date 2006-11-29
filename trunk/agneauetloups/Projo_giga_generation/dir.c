#define WINDOWS 1
#define LINUX 0

#ifdef _WIN32
#define OPERATING_SYSTEM WINDOWS
#endif
#ifndef _WIN32
#define OPERATING_SYSTEM LINUX
#endif

#include <stdio.h>

int main()
{
	FILE *fp;
	char buffer[2048];
	char buffer2[2048];
	char car = 'A';
	int i=0,j=0,end,start,write=1;
	system("dir /B /A:-D > fichiers.list");
	fp=fopen("fichiers.list","rb");
	car = fgetc(fp);
	while(!feof(fp))
	{
		if(write) buffer[i] = car;
		i++;
		car = fgetc(fp);
	}
	buffer[i]='\0';
	fclose(fp);
	//printf("%s",buffer);
	i=0;
	while(i<strlen(buffer))
	{
		if(i == 0 || buffer[i-1] == '\n') start = i;
		if(buffer[i+0] == '.' &&
			buffer[i+1] == 't' &&
			buffer[i+2] == 'x' &&
			buffer[i+3] == 't')
		{
			end = i-1;
			while(start <= end)
			{
				buffer2[j] = buffer[start];
				start++;
				j++;
			}
			buffer2[j] = '\n';
			j++;
			i += 4;
		}
		i++;
	}
	buffer2[j] = '\0';
	system("cls");
	printf("%s",buffer2);
}

