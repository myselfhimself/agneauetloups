#include "projet.h"

int main(int argc, char* argv[])
{
	t_game game;
	int success;
	
	if(argc < 2)
		printf("usage : %s port\n",argv[0]);
	else
	{
		network_init(&game);
		success = network_server_run(argv[1]);
		printf("success : %d\n", success);
		network_simple_chat();
		network_exit();
	}
	return 0;
}
