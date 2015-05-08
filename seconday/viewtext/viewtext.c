#include<stdio.h>
#include<gtk/gtk.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
GtkWidget *window;
GtkWidget *view;
GtkTextBuffer *buffer;
GtkTextIter *iter;
GtkWidget *button;
GtkWidget *box;
GtkWidget *button2;

void button_event(GtkWidget *widget, gpointer *data);
void button_event2(GtkWidget *widget, gpointer *data);

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window,200,200);
    gtk_signal_connect(GTK_OBJECT(window),
            "destroy",
            G_CALLBACK(gtk_main_quit),
            NULL);


    box = gtk_vbox_new(FALSE,0);
    gtk_widget_show(box);

    buffer = gtk_text_buffer_new(NULL);
    view = gtk_text_view_new_with_buffer(buffer);
    gtk_box_pack_start(GTK_BOX(box),view,TRUE,TRUE,10);
    gtk_widget_set_size_request(view,200,150);

    button = gtk_button_new_with_label("enter");
    gtk_signal_connect(GTK_OBJECT(button),
            "clicked",
            GTK_SIGNAL_FUNC(button_event),
            NULL);
    gtk_box_pack_start(GTK_BOX(box),button,TRUE,TRUE,10);
    gtk_widget_show(button);

    button2 = gtk_button_new_with_label("change");
    gtk_signal_connect(GTK_OBJECT(button2),
            "clicked",
            GTK_SIGNAL_FUNC(button_event2),
            NULL);
    gtk_box_pack_start(GTK_BOX(box),button2,FALSE,FALSE,10);
    gtk_widget_show(button2);

    gtk_container_add(GTK_CONTAINER(window),box);
    gtk_widget_show(view);
   
    gtk_widget_show(window);
    gtk_main();
    return 0;
}

void button_event(GtkWidget *widget,gpointer *data)
{
    const gchar *text="HOW ARE YOU !\n";
    GtkTextIter start,end;
    //获得缓冲区开始和结束位置的Iter
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&start,&end);
    //插入文本到缓冲区
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer),&start,text,strlen(text));
}

void button_event2(GtkWidget *widget, gpointer *data)
{
    gchar *text2;
    const gchar *text3="I AM HERE FOR YOU ! \n";
    GtkTextIter start,end;
   
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&start,&end);
    const GtkTextIter s=start,e=end;
    text2 = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer),&s,&e,FALSE);
    g_print("%s \n",text2);

    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer),text3,20);

}
