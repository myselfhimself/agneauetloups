#include "projet.h"

int main(int argc, char* argv[])
{
	t_game game;
	int success;
	t_history temp;
	temp.x = 3;
	temp.y = 4;

	if(argc < 3)
		printf("usage : %s addresse port\n",argv[0]);
	else
	{
		network_init(&game);
		success = network_client_run(argv[1],argv[2]);
		printf("success : %d\n",success);
		if(success)
		{
			sleep(3);
			//network_send(&temp,sizeof(t_history));
			network_simple_chat();
		}
		network_exit();
	}
	return 0;
}