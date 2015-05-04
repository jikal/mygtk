#include <stdio.h>
#include <gtk/gtk.h>
GtkWidget *create_button(char *filename){
	GtkWidget *image;
	GtkWidget *button;
	image = gtk_image_new_from_file(filename);
	gtk_widget_show(image);
	button = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(button),image);
	return button;
}

int main(int argc , char *argv[]){
	GtkWidget *window;
	GtkWidget *box;
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *box1;
	GtkWidget *handle;
	GtkWidget *handle1;
	GtkWidget *menubar;
	GtkWidget *button1;
	GtkWidget *button2;
	GtkWidget *button3;
	GtkWidget *button4;
	GtkWidget *menu;
	GtkWidget *menuitem;
	GtkWidget *rootmenu;
	GtkTooltips *button_tips;//提示信息指针
	gtk_init(&argc,&argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"浮动的工具条和菜单");
	gtk_container_set_border_width(GTK_CONTAINER(window),5);
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	hbox = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,5);
	handle = gtk_handle_box_new();
	gtk_box_pack_start(GTK_BOX(hbox),handle,FALSE,FALSE,5);
	box = gtk_hbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(handle),box);
	button1 = create_button("new.gif");
	gtk_box_pack_start(GTK_BOX(box),button1,FALSE,FALSE,3);
	button2 = create_button("open.gif");
	gtk_box_pack_start(GTK_BOX(box),button2,FALSE,FALSE,3);
	button3 = create_button("save.gif");
	gtk_box_pack_start(GTK_BOX(box),button3,FALSE,FALSE,3);
	button4 = create_button("quit.gif");
	gtk_box_pack_start(GTK_BOX(box),button4,FALSE,FALSE,3);
	button_tips = gtk_tooltips_new();
	gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips),button1,"创建一个新文件","new");
	gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips),button2,"打开文件","open");
	gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips),button3,"保存当前编辑的文件","save");
	gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips),button4,"退出次程序","quit");
	handle = gtk_handle_box_new();
	gtk_box_pack_start(GTK_BOX(hbox),handle,FALSE,FALSE,5);
	box1 = gtk_hbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(handle),box1);
	menubar = gtk_menu_bar_new();
	gtk_box_pack_start(GTK_BOX(box1),menubar,FALSE,FALSE,5);
	menu = gtk_menu_new();
	menuitem = gtk_menu_item_new_with_label("菜单项1");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu),menuitem);
	menuitem = gtk_menu_item_new_with_label("菜单项2");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu),menuitem);
	rootmenu = gtk_menu_item_new_with_label("文件");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(rootmenu),menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar),rootmenu);
	gtk_widget_show_all(window);
	gtk_main();
	return FALSE;
}
