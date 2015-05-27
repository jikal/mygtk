#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h> /* the key value defines can be found here */
#include <stdio.h>

static void
on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
    switch(event->keyval)
    {
        case GDK_Escape: 
            gtk_main_quit();
            break;
        default:
            break;
    }
}
int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	/* Get the Screen Resolution */
	GdkScreen* screen;
	gint width, height;
	GdkPixbuf *pixbuf;
	GtkWidget *fixed;
	screen = gdk_screen_get_default();
	width = gdk_screen_get_width(screen);
	height = gdk_screen_get_height(screen);
	printf("screen width: %d, height: %d\n", width, height);

/* Create window and set full screen */
	GtkWidget *window;
	GtkWidget *frame;
	GtkWidget *image;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	//gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
   	gtk_window_set_default_size(GTK_WINDOW(window), width, height);
	//gtk_window_fullscreen(GTK_WINDOW(window));
	//gtk_window_maximize(GTK_WINDOW (window));
	gtk_window_set_decorated(GTK_WINDOW(window), FALSE); /* hide the title bar and the boder */ 

	//fixed = gtk_fixed_new();
  	//gtk_container_add(GTK_CONTAINER(window), fixed);
	image = gtk_image_new_from_file ("./2.jpg");
	pixbuf = gtk_image_get_pixbuf (GTK_IMAGE(image));
	pixbuf = gdk_pixbuf_scale_simple(pixbuf, gdk_screen_get_width(screen) - 1, gdk_screen_get_height(screen) - 1,GDK_INTERP_BILINEAR);
    	gtk_image_set_from_pixbuf(GTK_IMAGE(image), pixbuf);
	//gtk_fixed_put(GTK_FIXED(fixed), image, 0, 0);
	gtk_container_add(GTK_CONTAINER(window),image);
	gtk_widget_show_all(window);
	/* add key event for quit */
	g_signal_connect(G_OBJECT(window),"key-press-event",G_CALLBACK(on_key_press), NULL);
	gtk_main();

	return 0;
}
