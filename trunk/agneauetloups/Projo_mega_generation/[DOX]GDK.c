#ifndef GDKC
#define GDKC

#include "[DOX]main.h"

void gtk_image_superimpose(GtkWidget *eventbox,const gchar *img)
{
	gint w,h;
    guint rowstride1,rowstride2,n_channels1,n_channels2,x,y,col;
    guchar *pixels1,*pixels2, *p1,*p2;
	/** - modification du pixbuf\n
	*     - récupération du pixbuf1 a partir de l'eventbox\n
	*     - récupération du pixbuf2 a partir du chemin d'accès img\n
	*     - récupération pour chacun des pixbufs de données pour calculer les emplacements des pixels\n
	*     - parcours des images (sont sensées être de tailles égales)\n
	*     -# si pixel du pixbuf2 = ROSE (#FF00FF) alors c'est le pixel du pixbuf1 qui reste\n
	*     -# si pixel du pixbuf2 != ROSE alors le pixel du pixbuf1 est remplacé par celui du pixbuf2\n
	*     - modification de l'image de l'eventbox en y injectant le pixbuf1\n
	*/
    GdkPixbuf *pixbuf1 = gtk_image_get_pixbuf(GTK_IMAGE((GtkWidget*)(gtk_container_get_children(GTK_CONTAINER(eventbox))->data)));   
	GdkPixbuf *pixbuf2 = NULL;
	pixbuf2 = gdk_pixbuf_new_from_file(img,NULL); 
	if(pixbuf2 == NULL) {printf("err ouverture de %s",img);sleep(5000);}
	w = gdk_pixbuf_get_width(pixbuf1);
    h = gdk_pixbuf_get_height(pixbuf1);
    rowstride1 = gdk_pixbuf_get_rowstride(pixbuf1);
    rowstride2 = gdk_pixbuf_get_rowstride(pixbuf2);
    pixels1 = gdk_pixbuf_get_pixels(pixbuf1);
    pixels2 = gdk_pixbuf_get_pixels(pixbuf2);
    n_channels1 = gdk_pixbuf_get_n_channels(pixbuf1);
	n_channels2 = gdk_pixbuf_get_n_channels(pixbuf2);
	
	for(x=0;x<w;x++)
    {
        for(y=0;y<h;y++)
        {
			p1 = pixels1 + y * rowstride1 + x * n_channels1;
			p2 = pixels2 + y * rowstride2 + x * n_channels2;
			
			if(p2[0]!=255 || p2[1]!=0 || p2[2]!=255)
			{
				p1[0]=p2[0];
				p1[1]=p2[1];
				p1[2]=p2[2];
			}
		}
	}
	gtk_image_set_from_pixbuf(GTK_IMAGE((GtkWidget*)(gtk_container_get_children(GTK_CONTAINER(eventbox))->data)),pixbuf1);
}

#endif
