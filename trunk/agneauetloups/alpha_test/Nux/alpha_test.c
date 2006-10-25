#include <stdlib.h>
#include <gtk/gtk.h>

typedef struct {GtkWidget *lastone;}t_movement;
void make_movement(GtkWidget *newone,t_movement *move);

int main (int argc, char *argv[])
{
  GtkWidget *win = NULL;
  GtkWidget *button[50];
  GtkWidget *imgzone[50];
  GtkWidget *table;
  t_movement move;
  gint i;
  /* Initialize GTK+ */
  gtk_init(&argc,&argv);
  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(win),"Sheep run - alpha test");
  gtk_window_set_position(GTK_WINDOW(win),GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(win),300,300);
  g_signal_connect(win,"destroy",gtk_main_quit,NULL);
  
  table = gtk_table_new(10,10,TRUE);
  gtk_container_add(GTK_CONTAINER(win),GTK_WIDGET(table));
  
  move.lastone = NULL;
  
  for(i=0;i<50;i++)
  {
      button[i] = gtk_button_new();
      gtk_table_attach_defaults(GTK_TABLE(table),button[i],2*(i%5)+1-(i%10-i%5)/5,2*(i%5)+1-(i%10-i%5)/5+1,2*(i-i%10)/10+(i%10-i%5)/5,2*(i-i%10)/10+(i%10-i%5)/5+1);
      imgzone[i] = gtk_image_new_from_file("images/Bighorn Sheep small.gif");
      gtk_container_add(GTK_CONTAINER(button[i]),GTK_WIDGET(imgzone[i]));
  }
  /*
  for(i=0;i<5;i++) gtk_button_set_label(GTK_BUTTON(button[i]),"L");
  gtk_button_set_label(GTK_BUTTON(button[47]),"A");
  */
  for(i=0;i<50;i++) g_signal_connect(G_OBJECT(button[i]),"clicked",G_CALLBACK(make_movement),&move);
  
  gtk_widget_show_all(win);
  gtk_main ();
  return 0;
}

void make_movement(GtkWidget *newone,t_movement *move)
{
  gchar *animal;
  if(move->lastone == NULL)
  {
    move->lastone = newone;
  }
  else
  {
    animal = gtk_button_get_label(GTK_BUTTON(move->lastone));
    gtk_button_set_label(GTK_BUTTON(newone),animal);
    gtk_button_set_label(GTK_BUTTON(move->lastone),"");
    move->lastone = NULL;
  }
}
