#include <stdio.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
static void key_button(GtkWidget *button,GdkEventKey *event){
	switch(event->keyval) {
		case GDK_Up:
			g_print("你按的时向上键\n");
			break;
		case GDK_Left:
			g_print("你按的是向左键\n");
			break;
		case GDK_Right:
			g_print("你按的是向右键\n");
			break;
		case GDK_Down:
			g_print("你按的是向下键\n");
			break;
		case GDK_Return:
			g_printf("你按的是回车键!\n");
			break;
		case GDK_Escape:
			g_printf("你按的是退出键!\n");
			break;
	}
}


int main(int argc,char *argv[]){
	GtkWidget *window;
	GtkWidget *button;

	gtk_init(&argc,&argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 100,100);
	gtk_window_set_title(GTK_WINDOW(window), "键盘触发界面");
	gtk_container_set_border_width(GTK_CONTAINER(window),20);
	g_signal_connect(GTK_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);

	button = gtk_button_new_with_label("按键");
	gtk_container_add(GTK_CONTAINER(window),button);
	g_signal_connect_swapped(GTK_OBJECT(button),"key_press_event",G_CALLBACK(key_button),NULL);
	gtk_widget_show_all(window);
	gtk_main();
	return FALSE;
}
