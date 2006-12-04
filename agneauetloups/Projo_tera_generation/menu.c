#include "main.h"

//change le texte dans la barre de status
//question d'avoir un pointeur sur la barre de status
void set_status_text(char* format_str,char* str)
{
	char temp[100];
	if(str != NULL)
		sprintf(temp,format_str,str);
	else
		sprintf(temp,format_str);
// 	//manque plus qu'à insérer ce texte quelque part
}

void onquit(gpointer data, guint callback_action,GtkWidget *widget)
{
    GtkWidget *Question;
    /** - création de la fenêtre de dialogue\n
    */
    Question = gtk_message_dialog_new(GTK_WINDOW(data),GTK_DIALOG_MODAL,GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO,"Voulez vous vraiment\nquitter le jeu ?");
    /** - affichage de la fenètre de dialogue\n
    * -# si réponse positive : appelle le gtk_main_quit()\n
    * -# si réponse négative : détruit seulement le widget\n
    */
    switch(gtk_dialog_run(GTK_DIALOG(Question)))
    {
        case GTK_RESPONSE_YES: gtk_main_quit();
             break;
        case GTK_RESPONSE_NONE:
        case GTK_RESPONSE_NO: gtk_widget_destroy(Question);
    }
}

void onabout(gpointer data, guint callback_action,GtkWidget *widget)
{
    GtkWidget *About;
    /** - création de la fenêtre de dialogue\n
    */
    About = gtk_message_dialog_new (GTK_WINDOW(data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Agneau et loups\nProjet info 2006\n\nJordane   GUILLOT\nStephane REGNIER\nJonathan SCHRODER");
    /** - affichage de la fenètre de dialogue\n
    */
    gtk_dialog_run(GTK_DIALOG(About));
    /** - à sa sortie détruire le widget\n
    */
    gtk_widget_destroy(About);
}
