#include <stdio.h>
#include <gtk/gtk.h>

void on_button_clicked(GtkButton *button,gpointer data){
	g_print("你点击的按钮是 %s\n",(gchar*)data);
}

int main(int argc , char *argv[]){
	GtkWidget *window;
	GtkWidget *box;
	GtkWidget *toolbar;//工具条指针
	GtkWidget *entry;//
	GtkWidget *label;
	gtk_init(&argc,&argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"添加工具条");
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	box = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),box);
	toolbar = gtk_toolbar_new();
/*
	gtk_toolbar_instert 向工具栏中插入系统固有资源项目，第一个参数指出要添加控件的工具条，第二个参数指出系统固有资源项目，第三/四个参数指出按钮可用和不可用时的信息，第五个参数指出回调函数，第六个参数指出传给回调函数的参数，最后一个参数指出按钮的位置-1表示最后
*/
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_NEW,"新建一个文件","新建",GTK_SIGNAL_FUNC(on_button_clicked),(gpointer)("新建"),-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_OPEN,"打开一个文件","打开",GTK_SIGNAL_FUNC(on_button_clicked),(gpointer)("打开"),-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_SAVE,"保存当前文件","保存",GTK_SIGNAL_FUNC(on_button_clicked),(gpointer)("保存"),-1);


	gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));//向工具条中添加竖线间隔
	label = gtk_label_new("文件名");
	gtk_toolbar_append_widget(GTK_TOOLBAR(toolbar),label,"这是一个标签","标签");//向工具条中添加自己创建的控件
	entry = gtk_entry_new();//创建文本框
	gtk_toolbar_append_widget(GTK_TOOLBAR(toolbar),entry,"这是一个录入条","录入");
	gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_CUT,"剪切","剪切",GTK_SIGNAL_FUNC(on_button_clicked),(gpointer)("剪切"),-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_COPY,"复制","复制",GTK_SIGNAL_FUNC(on_button_clicked),(gpointer)("复制"),-1);
	gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_QUIT,"退出","退出",GTK_SIGNAL_FUNC(on_button_clicked),(gpointer)("退出"),-1);
	gtk_toolbar_set_style(GTK_TOOLBAR(toolbar),GTK_TOOLBAR_ICONS);//设定工具条的外观
	gtk_toolbar_set_icon_size(GTK_TOOLBAR(toolbar),GTK_ICON_SIZE_SMALL_TOOLBAR);//设定工具条中图标的大小
	gtk_box_pack_start(GTK_BOX(box),toolbar,FALSE,FALSE,0);
	gtk_widget_show_all(window);
	gtk_main();
	return FALSE;
}
