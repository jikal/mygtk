#include <stdio.h>
#include <gtk/gtk.h>

void on_menu_activate(GtkMenItem *item , gpointer data){
	g_printf("Menuitem %s ispressed.\n",(gchar*)data);
}

int main(int argc , char *argv[]){
	GtkWidget *window;
	GtkWidget *box;
	GtkWidget *menubar;
	GtkWidget *editmenu;
	GtkWidget *helpmenu;
	GtkWidget *rootmenu;
	GtkWidget *menuitem;
	GtkAccelGroup* accel_group;
	gtk_init(&argc,&argv);
	window = gtk_window_new(G_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"菜单测试程序")；
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	accel_group = gtk_accel_group_new();//创建快捷键集并加入到窗口
	gtk_window_add_accel_group(GTK_WINDOW(window),accel_group);//
	box = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),box);
	menu = gtk_menu_new();//文件菜单
	menuitem = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW,accel_group);//系统资源创建带图像的菜单
	gtk_menu_shell_append(GTK_MENU_SHELL(menu),menuitem);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(on_menu_activate),FALSE,(gpointer)("new"));
	menuitem = gtk_image_menu_item_new_from_stock(GTK_STCOK_OPEN,accel_group);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu),menuitem);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(on_menu_activate),FALSE,(gpointer)("open"));
	menuitem = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE,accel_group);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu),menuitem);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(on_menu_activate),FALSE,(gpointer)("save"));
	menuitem = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE_AS,accel_group);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu),menuitem);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(on_menu_activate),FALSE,(gpointer)("save as"));
	

}
