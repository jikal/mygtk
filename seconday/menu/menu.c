#include <stdio.h>
#include <gtk/gtk.h>

void on_menu_activate(GtkMenuItem *item , gpointer data){
	g_printf("Menuitem %s ispressed.\n",(gchar*)data);
}

int main(int argc , char *argv[]){
	GtkWidget *window;//生成窗口指针
	GtkWidget *box;//生成盒装容器的指针
	GtkWidget *menu;//定义菜单指针
	GtkWidget *menubar;//定义菜单条指针
	GtkWidget *editmenu;//定义编辑按钮指针
	GtkWidget *helpmenu;//定义帮助按钮指针
	GtkWidget *rootmenu;//定义系统菜单指针
	GtkWidget *menuitem;//定义各个菜单下的按钮
	GtkAccelGroup *accel_group;//快捷键集指针
	gtk_init(&argc,&argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"菜单测试程序");
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	accel_group = gtk_accel_group_new();//创建快捷键集
	gtk_window_add_accel_group(GTK_WINDOW(window),accel_group);//把快捷键集加入到窗口，注意逻辑顺序
	box = gtk_vbox_new(FALSE,0);//创建盒装容器不均匀排放，无边框
	gtk_container_add(GTK_CONTAINER(window),box);//盒装容器加入到窗口
/*
*先设置一个file菜单，然后将file菜单放入菜单条中
*/
	menu = gtk_menu_new();//文件菜单
	menuitem = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW,accel_group);//系统资源创建带图像的菜单
	gtk_menu_shell_append(GTK_MENU_SHELL(menu),menuitem);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(on_menu_activate),(gpointer)("new"));
	menuitem = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN,accel_group);//每新建一个菜单都要加入到快捷键集
	gtk_menu_shell_append(GTK_MENU_SHELL(menu),menuitem);//把新建的快捷键加入到menu
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(on_menu_activate),(gpointer)("open"));
	menuitem = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE,accel_group);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu),menuitem);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(on_menu_activate),(gpointer)("save"));
	menuitem = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE_AS,accel_group);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu),menuitem);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(on_menu_activate),(gpointer)("save as"));
	


	menuitem = gtk_separator_menu_item_new();//菜单分隔符
	gtk_menu_shell_append(GTK_MENU_SHELL(menu),menuitem);
	menuitem = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT,accel_group);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu),menuitem);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(on_menu_activate),(gpointer)("exit"));
	rootmenu = gtk_menu_item_new_with_label("文件");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(rootmenu),menu);//将menu设定rootmenu的子菜单
	menubar = gtk_menu_bar_new();//设置菜单条
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar),rootmenu);//将rootmenu放在菜单条中
/*设置一个edit菜单，再将edit菜单入菜单条中*/

	rootmenu = gtk_menu_item_new_with_label("编辑");
	editmenu = gtk_menu_new();
	menuitem = gtk_image_menu_item_new_from_stock(GTK_STOCK_CUT,accel_group);
	gtk_menu_shell_append(GTK_MENU_SHELL(editmenu),menuitem);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(on_menu_activate),(gpointer)("cut"));
	menuitem = gtk_image_menu_item_new_from_stock(GTK_STOCK_COPY,accel_group);
	gtk_menu_shell_append(GTK_MENU_SHELL(editmenu),menuitem);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(on_menu_activate),(gpointer)("copy"));
	menuitem = gtk_image_menu_item_new_from_stock(GTK_STOCK_PASTE,accel_group);
	gtk_menu_shell_append(GTK_MENU_SHELL(editmenu),menuitem);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(on_menu_activate),(gpointer)("paste"));
	menuitem = gtk_image_menu_item_new_from_stock(GTK_STOCK_FIND,accel_group);
	gtk_menu_shell_append(GTK_MENU_SHELL(editmenu),menuitem);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(on_menu_activate),(gpointer)("find"));


	gtk_menu_item_set_submenu(GTK_MENU_ITEM(rootmenu),editmenu);//将editmenu菜单设置为rootmenu的字菜单
	
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar),rootmenu);


//设置帮助菜单
	rootmenu = gtk_menu_item_new_with_label("帮助");
	helpmenu = gtk_menu_new();//新建帮助菜单
	menuitem = gtk_image_menu_item_new_from_stock(GTK_STOCK_HELP,accel_group);//系统资源中创建带图像的菜单项
	gtk_menu_shell_append(GTK_MENU_SHELL(helpmenu),menuitem);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(on_menu_activate),(gpointer)("help"));


	menuitem = gtk_menu_item_new_with_label("关于。。。。");
	gtk_menu_shell_append(GTK_MENU_SHELL(helpmenu),menuitem);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(on_menu_activate),(gpointer)("about"));
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(rootmenu),helpmenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar),rootmenu);//将帮助菜单放入menubar
	gtk_box_pack_start(GTK_BOX(box),menubar,FALSE,FALSE,0);
	gtk_widget_show_all(window);
	gtk_main();
	return FALSE;
}
