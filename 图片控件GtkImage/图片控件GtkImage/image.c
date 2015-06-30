#include <gtk/gtk.h>	// 头文件

int main(int argc, char *argv[]) 
{ 
    gtk_init(&argc, &argv); 	// 初始化
	
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);    // 创建窗口
	g_signal_connect(GTK_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);


	GtkWidget *hbox = gtk_hbox_new(TRUE, 10);       // 创建水平布局容器
	gtk_container_add(GTK_CONTAINER(window), hbox); // 把水平布局容器放入窗口
	
	// 创建图片控件，这种方法创建以图片默认大小来显示，不能修改
	GtkWidget *image_one =  gtk_image_new_from_file("./image/1.bmp");
	gtk_container_add(GTK_CONTAINER(hbox), image_one);// 添加到布局里
	
	
	// 下面借助GdkPixbuf来修改图片的大小，注意接口以gdk_开头，不属于控件类
	// 创建pixbuf，需要占用资源，使用完，需要人为释放
	GdkPixbuf *src = gdk_pixbuf_new_from_file("./image/1.bmp", NULL);// 读取原图片	
	GdkPixbuf *dst = gdk_pixbuf_scale_simple(src,100, 100, GDK_INTERP_BILINEAR);	// 修改图片大小(100, 100), 保存在dst
	
	GtkWidget *image_two = gtk_image_new_from_pixbuf(dst);	// 通过pixbuf创建图片控件
	g_object_unref(src);	// pixbuf使用完，需要人为释放资源
	g_object_unref(dst);
	gtk_container_add(GTK_CONTAINER(hbox), image_two);	// 添加到布局里
	
	// 获取图片控件里的pixbuf，以这个pixbuf又重新创建一个图片控件
	GdkPixbuf *tmp = gtk_image_get_pixbuf( GTK_IMAGE(image_two) );
	GtkWidget *image_three = gtk_image_new_from_pixbuf(tmp);
	
	gtk_container_add(GTK_CONTAINER(hbox), image_three);	// 添加到布局里
	
	// 给创建的图片控件重新设置一张图片
	GtkWidget *image_four =  gtk_image_new_from_file("./image/1.bmp");
	src = gdk_pixbuf_new_from_file("./image/2.bmp", NULL);// 读取原图片	
	dst = gdk_pixbuf_scale_simple(src,200, 200, GDK_INTERP_BILINEAR);	// 修改图片大小(100, 100), 保存在dst
	gtk_image_set_from_pixbuf(GTK_IMAGE(image_four), dst);	// 给image_four重新设置一张图片
	g_object_unref(src);	// pixbuf使用完，需要人为释放资源
	g_object_unref(dst);
	gtk_container_add(GTK_CONTAINER(hbox), image_four);	// 添加到布局里
	
	
	gtk_widget_show_all(window);	// 显示窗口控件
 
    gtk_main(); 	// 主事件循环
 
    return 0; 
} 
