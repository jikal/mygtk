#include <gtk/gtk.h>
#define CURL_TARGET	 "http://vg.vingoojuice.com/static/upfile/V19/V2.C_Jm20vega_6.1.19_wx.tar.gz"
	GtkWidget *window;
	GtkWidget *vbox,*hbox;
	GtkWidget *combo;
	GtkWidget *label,*pronumlabel,*timelabel;
	GtkWidget *pronumentry;
	GtkWidget *timeentry;
	GtkWidget *sep;
	GtkWidget *startbutton,*endbutton;
	GtkWidget *frame;
void pressureTest(GtkWidget *button,gpointer data);
int main(int argc,char *argv[]){
	gtk_init(&argc,&argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    	gtk_window_set_default_size(GTK_WINDOW(window), 500, 300);
	gtk_window_set_title(GTK_WINDOW(window), "服务器压力测试工具");
	gtk_container_set_border_width(GTK_CONTAINER(window),20);

	//GtkWidget *image = gtk_image_new_from_file("./icon/vingoo.png");
	
	g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);


	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),vbox);

	hbox = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,15);
	
//服务器地址界面
	label = gtk_label_new("请选择服务器地址:");
	gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);
	gtk_label_set_markup(GTK_LABEL(label),"<span foreground='red' font_desc='12'>请选择服务器地址:</span>");
	combo = gtk_combo_box_new_text();
	gtk_combo_box_append_text(GTK_COMBO_BOX(combo),CURL_TARGET);
	gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
	gtk_box_pack_start(GTK_BOX(hbox),combo,FALSE,FALSE,5);

	sep = gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(vbox),sep,FALSE,FALSE,15); 
	
	hbox = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,15);
	
	
//设置进程数和时间entry
	pronumlabel =  gtk_label_new("进程数");
	gtk_label_set_markup(GTK_LABEL(pronumlabel),"<span foreground='black' font_desc='16'>进程数：</span>"); 
	gtk_box_pack_start(GTK_BOX(hbox),pronumlabel,FALSE,FALSE,5);
	pronumentry = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(hbox),pronumentry,FALSE,FALSE,5);
	timelabel =  gtk_label_new("时间");
	gtk_label_set_markup(GTK_LABEL(timelabel),"<span foreground='black' font_desc='16'>时间：</span>"); 
	gtk_box_pack_start(GTK_BOX(hbox),timelabel,FALSE,FALSE,5);
	timeentry = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(hbox),timeentry,FALSE,FALSE,5);

	sep = gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(vbox),sep,FALSE,FALSE,15); 

	hbox = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,15);

	startbutton = gtk_button_new_with_label("开始");
	gtk_widget_set_size_request(startbutton,100,40);
	gtk_box_pack_start(GTK_BOX(hbox),startbutton,FALSE,FALSE,150);
	g_signal_connect(G_OBJECT(startbutton),"clicked",G_CALLBACK(pressureTest),NULL);
	
	endbutton = gtk_button_new_with_label("结束");
	gtk_widget_set_size_request(endbutton,100,40);
	gtk_box_pack_start(GTK_BOX(hbox),endbutton,FALSE,FALSE,0);

	gtk_widget_show_all(window);
	gtk_main();
	return FALSE;
}

void pressureTest(GtkWidget *button,gpointer data){
	int ret=0,i=0;
	char cmd_buf[128] = {0};

	if(0 != Shmsem_init_Shmsem(&Shmseminfo,&Shmmem))
	{
		printf("init shmsem err\n");
		return -1;
	}

	//创建子进程池	
	for(i=0;i<MAX_PROCESS_NUM;i++)
	{
		ret = create_child_pool();
	}

	for( ;; )
	{
		//获得命令
		fscanf(stdin,"%s",cmd_buf);
		if(0 == strcmp(cmd_buf,"upload"))
		{
			Shmmem->num = 1;	
			printf("ACCEPT ACCEPT ACCEPT\n\n");
		}
		else
		{
			Shmmem->num = 0;
			printf("------------------\n");
			printf("No Cmd Input,Again\n");
			printf("------------------\n\n");
		}
	}
	Shmsem_clean(&Shmseminfo);
	
}
