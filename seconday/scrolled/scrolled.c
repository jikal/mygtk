#include <stdio.h>
#include <gtk/gtk.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
GtkTextIter start,end;
GtkWidget *window;
GtkWidget *scrolled;
GtkWidget *viewtext;
GtkWidget *button,*vbox;
GtkTextBuffer *buffer;
//GtkTextIter *iter;
const gchar *text="HOW ARE YOU !\n";
void mythread(GtkWidget *button){
	while(1){
		sleep(1);
		gdk_threads_enter();
		gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer),&start,text,strlen(text));
		gdk_threads_leave();	
	}
}
void on_button(GtkWidget *button,gpointer data){
	gtk_widget_set_sensitive(button,FALSE);
	//gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer),&start,text,strlen(text));
	g_thread_create(mythread,button,FALSE,NULL);
}

int main(int argc,char *argv[]){
	if(!g_thread_supported()){
		g_thread_init(NULL);
	}
	gtk_init(&argc,&argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window,200,100);
	g_signal_connect(GTK_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	scrolled = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled),
                                    GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
	gtk_box_pack_start(GTK_BOX(vbox),scrolled,TRUE,TRUE,2);
	buffer = gtk_text_buffer_new(NULL);
	viewtext = gtk_text_view_new_with_buffer(buffer);
	gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&start,&end);
	gtk_container_add(GTK_CONTAINER(scrolled),viewtext);
	button = gtk_button_new_with_label("1");
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,0);
	g_signal_connect(GTK_OBJECT(button),"clicked",G_CALLBACK(on_button),NULL);
	gtk_widget_show_all(window);
	gdk_threads_enter();
	gtk_main();
	gdk_threads_leave();
	return 0;	
}
