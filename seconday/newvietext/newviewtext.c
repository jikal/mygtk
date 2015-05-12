#include <stdio.h>
#include <gtk/gtk.h>

GtkWidget *window;
GtkWidget *view;
GtkTextBuffer *buffer;
GtkTextIter *iter;
//GtkWidget *button;
GtkWidget *scrolled;
GtkWidget *vbox;
GtkTextMark *mark;
gchar *text = "hello my name is xxx!\n";
static void LogMsg(const char* pMsg,int iLength)
{
	buffer = gtk_text_view_get_buffer(view);
	gtk_text_buffer_get_end_iter(buffer,&iter);
	gtk_text_buffer_insert(buffer,&iter,pMsg,iLength);
	gtk_text_buffer_get_end_iter(buffer,&iter);
	gtk_text_view_scroll_to_iter(view,&iter,0.0,TRUE,0.0,1.0);
	while (gtk_events_pending ()){
		gtk_main_iteration();
	}

}
int main(int argc , char *argv[]){
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window,200,200);
	gtk_signal_connect(GTK_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	scrolled = gtk_scrolled_window_new(NULL,NULL);
	gtk_box_pack_start(GTK_BOX(vbox),scrolled,TRUE,TRUE,2);

	view = gtk_text_view_new();
	buffer = gtk_text_view_get_buffer((GtkTextView*)view);
       gtk_text_buffer_get_end_iter(buffer,&iter);

       mark= gtk_text_buffer_create_mark(buffer,NULL,&iter,1);
	gtk_text_buffer_insert(buffer,&iter,text,-1);
       gtk_text_view_set_buffer((GtkTextView*)view,buffer);
	gtk_container_add(GTK_CONTAINER(scrolled),view);
       gtk_text_buffer_move_mark(buffer,mark,&iter);
       gtk_text_view_scroll_to_mark(GTK_TEXT_VIEW(view),mark,0,1,1,1);

	gtk_widget_show_all(window);
	gtk_main();
	return FALSE;
}
