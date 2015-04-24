#include <stdio.h>
#include <gtk/gtk.h>


/*
关于结构体GtkItemFactoryEntry参数了解
typedef struct {
gchar *path;                      菜单项的路径
gchar *accelerator;               菜单项对应的快捷键
GtkItemFactoryCallback callback; 回调函数
guint callback_action;            传递给回调函数的gpointer参数

gchar *item_type;
// item_type的可能取值:
* NULL -> "<Item>"
* "" -> "<Item>"
* "<Title>" -> create a title item
* "<Item>" -> create a simple item
* "<ImageItem>" -> create an item holding an image
* "<StockItem>" -> create an item holding a stock image
* "<CheckItem>" -> create a check item
* "<ToggleItem>" -> create a toggle item
* "<RadioItem>" -> create a radio item
* <path> -> path of a radio item to link against
* "<Separator>" -> create a separator
* "<Tearoff>" -> create a tearoff separator
* "<Branch>" -> create an item to hold sub items
* "<LastBranch>" -> create a right justified item to hold sub items
*Extra data for some item types:
* ImageItem -> pointer to inlined pixbuf stream
* StockItem -> name of stock item
gconstpointer extra_data;
} GtkItemFactoryEntry;
*/
void on_menu_activate(GtkMenuItem *item , gpointer data);
static GtkItemFactoryEntry menu_items[] = {
	{"/文件 (_F)",NULL,NULL,0,"<Branch>"},
	{"/文件 (_F) /新建",NULL,on_menu_activate,(guint)"新建","<StockItem>",GTK_STOCK_NEW},
	{"/文件 (_F) /打开",NULL,on_menu_activate,(guint)"打开","<StockItem>",GTK_STOCK_OPEN},
	{"/文件 (_F) /保存",NULL,on_menu_activate,(guint)"保存","<StockItem>",GTK_STOCK_SAVE},
	{"/文件 (_F) /另存为",NULL,on_menu_activate,(guint)"另存为","<StockItem>",GTK_STOCK_SAVE_AS},
	{"/文件 (_F) /-",NULL,NULL,0,"<Separator>"},
	{"/文件 (_F) /退出",NULL,on_menu_activate,(guint)"退出","<StockItem>",GTK_STOCK_QUIT},
	{"/编辑 (_E)",NULL,NULL,0,"<Branch>"},	
	{"/编辑 (_E) /剪切",NULL,on_menu_activate,(guint)"剪切","<StockItem>",GTK_STOCK_CUT},
	{"/编辑 (_E) /复制",NULL,on_menu_activate,(guint)"复制","<StockItem>",GTK_STOCK_COPY},
	{"/编辑 (_E) /粘贴",NULL,on_menu_activate,(guint)"粘贴","<StockItem>",GTK_STOCK_PASTE},
	{"/编辑 (_E) /查找",NULL,on_menu_activate,(guint)"查找","<StockItem>",GTK_STOCK_FIND},
	{"/帮助 (_H)",NULL,NULL,0,"<LastBranch>"},
	{"/帮助 (_H) /帮助",NULL,on_menu_activate,(guint)"帮助","<StockItem>",GTK_STOCK_HELP},
	{"/帮助 (_H) /关于...",NULL,on_menu_activate,(guint)"关于","<StockItem>",GTK_STOCK_HELP}
};

void on_menu_activate(GtkMenuItem *item,gpointer data){
	g_print("Menu item %s is pressed.\n",(gchar*)data);
}

int main(int argc , char *argv[]){
	GtkWidget *window;//窗口指针
	GtkWidget *box;//盒装容器指针
	GtkWidget *menubar;//菜单条指针
	GtkAccelGroup *accel_group;//快捷键集指针
	GtkItemFactory *item_factory;//
	gint n = 15;
	gtk_init(&argc,&argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"添加菜单的快捷方法");
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	accel_group = gtk_accel_group_new();//快捷键菜单集
	box = gtk_vbox_new(FALSE,0);//盒装容器
	gtk_container_add(GTK_CONTAINER(window),box);
	gtk_widget_show(box);
	item_factory = gtk_item_factory_new(GTK_TYPE_MENU_BAR,"<main>",accel_group);
	gtk_item_factory_create_items(item_factory,n,menu_items,NULL);
	gtk_window_add_accel_group(GTK_WINDOW(window),accel_group);
	menubar = gtk_item_factory_get_widget(item_factory,"<main>");
	gtk_box_pack_start(GTK_BOX(box),menubar,FALSE,FALSE,0);
	gtk_widget_show(menubar);
	gtk_widget_show(window);
	gtk_main();
	return FALSE;
}
