#include <stdio.h>
#include <gtk/gtk.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <gdk/gdkkeysyms.h>
GtkTextIter start,end;
GtkWidget *window;
GtkWidget *scrolled;
GtkWidget *viewtext;
GtkWidget *button,*vbox;
GtkTextBuffer *buffer;
GtkTextIter *iter;
GtkTextMark *mark;
//const gchar *text="hello!\n";
gchar text[1024];

void mythread(GtkWidget *button){
	int n = 0;
	while(1){
		sleep(1);
		sprintf(text,"hello %d\n",n++);
		gdk_threads_enter();
		gtk_text_buffer_get_end_iter (buffer, &start);
		gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer),&start,text,strlen(text));
		gtk_text_buffer_get_end_iter (buffer, &end);
		mark = gtk_text_buffer_create_mark (buffer, NULL, &end, TRUE);
		gtk_text_view_scroll_mark_onscreen(GTK_TEXT_VIEW (viewtext),mark);
		gdk_threads_leave();	
	}
}


void on_button(GtkWidget *button,GdkEventKey *event){
	if(GDK_Return == event->keyval){
		//gtk_widget_set_sensitive(button,FALSE);
		g_thread_create(mythread,button,FALSE,NULL);
	}
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
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled),GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
	gtk_box_pack_start(GTK_BOX(vbox),scrolled,TRUE,TRUE,2);
	
	viewtext = gtk_text_view_new();
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(viewtext));
	gtk_container_add(GTK_CONTAINER(scrolled),viewtext);

	button = gtk_button_new_with_label("1");
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,0);
	gtk_window_set_focus(GTK_WINDOW(window),button);
	g_signal_connect_swapped(GTK_OBJECT(button),"key_press_event",G_CALLBACK(on_button),NULL);
	gtk_widget_show_all(window);

	gdk_threads_enter();
	gtk_main();
	gdk_threads_leave();
	return 0;	
}
