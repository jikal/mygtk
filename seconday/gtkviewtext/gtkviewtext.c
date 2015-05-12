#include <gtk/gtk.h>
   	GtkWidget *window;
    	GtkWidget *view;
    	GtkWidget *vbox,*button;
    	GtkWidget *fix;
	GtkWidget *scrolled;
    	GtkTextBuffer *buffer;
    	GtkTextIter start,end;
    	GtkTextIter iter;

void mythread(GtkWidget *button){
	while(1){
		sleep(1);
		gdk_threads_enter();
		gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
		gtk_text_buffer_insert(buffer, &iter, "Plain text\n", -1);
		gdk_threads_leave();
		
	}
}
void on_button(GtkWidget *button,gpointer data){
	g_thread_create(mythread,button,FALSE,NULL);
}
int main( int argc, char *argv[])
{
	if(!g_thread_supported()){
		g_thread_init(NULL);
	}    
	gtk_init(&argc, &argv);
    	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    	gtk_window_set_default_size(GTK_WINDOW(window), 250, 200);
    	gtk_window_set_title(GTK_WINDOW(window), "TextView");
    	gtk_container_set_border_width(GTK_CONTAINER(window), 5);
    	GTK_WINDOW(window)->allow_shrink = TRUE;

    	vbox = gtk_vbox_new(FALSE, 0);
    	gtk_widget_set_size_request (vbox, 200, 200);

    	//fix = gtk_fixed_new ();
    	//gtk_widget_set_name (fix, "fix");
    	//gtk_widget_show (fix);
    	//gtk_container_add (GTK_CONTAINER (vbox), fix);    

    	
    	//gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 0);
	view = gtk_text_view_new();
	scrolled = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled),GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
	gtk_box_pack_start(GTK_BOX(vbox),scrolled,TRUE,TRUE,2);
	gtk_container_add(GTK_CONTAINER(scrolled),view);
	
    	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
/*
    // 创建文本格式类型
     	gtk_text_buffer_create_tag(buffer, "gap",
        	"pixels_above_lines", 30, NULL);

    // 左边距
     	gtk_text_buffer_create_tag(buffer, "lmarg", 
        	"left_margin", 5, NULL);

    // 水平居中
    	gtk_text_buffer_create_tag(buffer, "jCenter", 
        	"justification", GTK_JUSTIFY_CENTER, NULL);

    // 前景
     	gtk_text_buffer_create_tag(buffer, "blue_fg", 
        	"foreground", "blue",  NULL);   

    // 字体背景
     	gtk_text_buffer_create_tag(buffer, "gray_bg", 
        	"background", "gray", NULL); 

    // 斜体
     gtk_text_buffer_create_tag(buffer, "italic", 
        "style", PANGO_STYLE_ITALIC, NULL);

    // 粗体
     	gtk_text_buffer_create_tag(buffer, "bold", 
        	"weight", PANGO_WEIGHT_BOLD, NULL);

    // 字体
     	gtk_text_buffer_create_tag (buffer, "font1",
        	"font", "[Consolas][PANGO_STYLE_OBLIQUE | PANGO_WEIGHT_BOLD][28]",
        	NULL); 
*/
    // 自动换行
    //gtk_text_buffer_create_tag(buffer, "wrap_word","wrap-mode", GTK_WRAP_WORD_CHAR, NULL);

    // 设置到起始位置
     	//gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
	
    // 插入文本
     	//gtk_text_buffer_insert(buffer, &iter, "Plain text\n", -1);
/*
    	gtk_text_buffer_insert_with_tags_by_name(buffer, &iter, 
        	"Colored Text\n", -1, "blue_fg", "lmarg", "wrap_word", NULL);

    	gtk_text_buffer_insert_with_tags_by_name (buffer, &iter, 
        	"Text with colored background\n", -1, "lmarg", "gray_bg", "jCenter", NULL);

    	gtk_text_buffer_insert_with_tags_by_name (buffer, &iter, 
        "Text in italics\n", -1, "italic", "lmarg", NULL);

    	gtk_text_buffer_insert_with_tags_by_name (buffer, &iter, 
        	"Bold text\n", -1, "bold", "lmarg", NULL);
*/
    	gtk_container_add(GTK_CONTAINER(window), vbox);

    // 未激活
     //gtk_widget_set_sensitive(view, FALSE);
	button = gtk_button_new_with_label("1");
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,0);
	g_signal_connect(GTK_OBJECT(button),"clicked",G_CALLBACK(on_button),NULL);

    	g_signal_connect_swapped(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), G_OBJECT(window));

    	gtk_widget_show_all(window);
	gdk_threads_enter();
    	gtk_main();
	gdk_threads_leave();
    	return 0;
}
