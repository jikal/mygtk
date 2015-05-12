#include <stdio.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
GtkWidget *window;
gboolean Key_Control(GtkWidget *widget, GdkEventKey *event, gpointer data);


int main(int argc , char *argv[]){
	
	gtk_init(&argc,&argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window,200,100);
	g_signal_connect_swapped(G_OBJECT(window), "key_press_event", G_CALLBACK(Key_Control), NULL);
	gtk_widget_show_all(window);
	gtk_main();
	return FALSE;
}


gboolean Key_Control(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	if ( GDK_Return == event->keyval){
		gtk_main_quit();
	}
}

