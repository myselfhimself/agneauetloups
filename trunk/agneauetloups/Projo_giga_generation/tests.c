#include "main.h"


// /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\
// \   ce fichier ne comporte que des fonctions de tests/debuggage    /
//  \_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/

void afficher_console(t_game *game)
{
    int i,j,k,marked;
    if(OPERATING_SYSTEM == WINDOWS) system("CLS");
    else system("clear");
    for(i=9;i>=0;i--)
    {
        for(j=0;j<10;j++)
        {
            marked = 0;
            for(k=0;k<6;k++)
            {
                if(game->pawn[k].position.x == j && game->pawn[k].position.y == i)
                {
                    marked = 1;
                    if(k==0) printf("A ");
                    else printf("L ");
                }
            }
            if(marked==0) printf(". ");
        }
        printf("\n");
    }
    printf("\n\n");
}

void select(GtkWidget *eventbox,gint R,gint V,gint B)
{
    GdkPixbuf *pixbuf;
    gint w,h;
    guint rowstride, n_channels,x,y,col;
    guchar *pixels, *p;
     
    pixbuf = gtk_image_get_pixbuf(GTK_IMAGE((GtkWidget*)(gtk_container_get_children(GTK_CONTAINER(eventbox))->data)));    
    w = gdk_pixbuf_get_width(pixbuf);
    h = gdk_pixbuf_get_height(pixbuf);
    rowstride = gdk_pixbuf_get_rowstride(pixbuf);
    pixels = gdk_pixbuf_get_pixels(pixbuf);
    n_channels = gdk_pixbuf_get_n_channels(pixbuf);

    for(x=0;x<w;x++)
    {
		for(y=0;y<h;y++)
        { 
			p = pixels + y * rowstride + x * n_channels;
			//col = 0.29*p[0] + 0.7*p[1] + 0.11*p[2];
			p[0]*=R; p[1]*=V; p[2]*=B;
        }
    }
    gtk_image_set_from_pixbuf(GTK_IMAGE((GtkWidget*)(gtk_container_get_children(GTK_CONTAINER(eventbox))->data)),pixbuf);
}

t_association *changeposition(t_association pawn[6], int pawntomove,int direction)
{
	int x,y;
	x = pawn[pawntomove].position.x;
	y = pawn[pawntomove].position.y;
	if(direction == TOP_LEFT || direction == BOTTOM_LEFT) x -= 1; else x+=1;
	if(direction == TOP_LEFT || direction == TOP_RIGHT) y+=1; else y-=1;
	pawn[pawntomove].position.x = x;
	pawn[pawntomove].position.y = y;
	return pawn;
}
