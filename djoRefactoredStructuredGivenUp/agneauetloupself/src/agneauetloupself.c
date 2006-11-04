#include "projet.h"

int main(int argc, char *argv[])
{
	t_tout* tout;
	tout = (t_tout*)malloc(sizeof(t_tout));

	gtk_init(&argc,&argv);

	interface_make(tout); // background : lie les boutons à 'tout'

	UT(SET_PLAYERS);

	gtk_main();
	return EXIT_SUCCESS;
}
