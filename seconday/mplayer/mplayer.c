#include <stdio.h>
#include <gtk/gtk.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


GtkWidget *window;
GtkWidget *draw_area;
GtkWidget *hscale;//水平比列构件
GtkObject *adjust;//调整对象
GtkWidget *playbutton;
GtkWidget *stopbutton;
GtkWidget *pausebutton;
GtkWidget *fwordbutton;
GtkWidget *backbutton;
GtkWidget *volincbutton;
GtkWidget *voldecbutton;
GtkWidget *statbar;//状态栏
GtkWidget *scrolled;
GtkWidget *mylable;
GtkWidget *table;
gint time_id;
pthread_t th;//线程ID
gchar *ext[6]={"mp3","mp4","avi","mpg","rm","rmvb"};
FILE *fp=NULL;
gchar statbarinfo[256];



enum STAT {STAT_PLAY,STAT_PAUSE,STAT_STOP};//枚举的电影状态
enum STAT status=STAT_STOP;//初始化状态为STOP

/*获取文件路径名*/
char* GetFileName(char* pathname)
{
	int len;
	char* pch;
	if(pathname)
	{
		len=strlen(pathname);
		pch=pathname+len-1;
		while(pch>=pathname)
		{
			if(*pch=='\\' || *pch=='/')
				return (pch+1);
			pch=pch-1;
		}
	}
	return pathname;
}

//获取电影名
int GetFilePreName(char* prename, char* filename)
{
	int len,i=0;
	if(filename)
	{
		len=strlen(filename);
		for(i=0;i<(len-4);i++)
			*(prename+i) = *(filename+i);
	}
	return i;
}
//获取格式
char* GetFileExtName(char* pathname)
{
	int len;
	char* pch;
	if(pathname)
	{
		len=strlen(pathname);
		pch=pathname+len-1;
		while(pch>=pathname)
		{
			if(*pch=='.')
				return (pch+1);
			pch=pch-1;
		}
	}
	return NULL;
}
/*对正在播放的电影的操作*/
void send_cmd(GtkWidget *gw, gpointer data){
	gchar cmd[256];
	gchar *str=(gchar *)data;
	if(status==STAT_STOP)
		return;
	else if(status==STAT_PAUSE)
	{
		if(strcmp(str,"pause")==0 || strcmp(str,"play")==0)
		{
			status=STAT_PLAY;
			sprintf(cmd,"echo \"%s\" > /tmp/cmd","pause");
			gtk_statusbar_push(GTK_STATUSBAR(statbar),1,statbarinfo);//用于将新消息加到状态栏中，它返回一个消息标识符(Message Identifier)。这个标识符可以和上下文标识符一起传给gtk_statusbar_remove函数以将该消息从状态栏的栈中删除
		}
		else
			return;
	}
	else
	{
		if(strcmp(str,"pause")==0)
		{
			status=STAT_PAUSE;
			sprintf(cmd,"echo \"%s\" > /tmp/cmd","pause");
			gtk_statusbar_push(GTK_STATUSBAR(statbar),3,"pause");
		}
		else if(strcmp(str,"stop")==0)
		{
			status=STAT_STOP;
			sprintf(cmd,"echo \"%s\" > /tmp/cmd","quit");
			gtk_adjustment_set_value(GTK_ADJUSTMENT(adjust),0);
			gtk_statusbar_push(GTK_STATUSBAR(statbar),2,"stop");
		}
		else if(strcmp(str,"back")==0)
			sprintf(cmd,"echo \"seek -10\" > /tmp/cmd");
		else if(strcmp(str,"fword")==0)
			//sprintf(cmd,"echo \"vo_fullscreen 1\" > /tmp/cmd");
			sprintf(cmd,"echo \"seek 10\" > /tmp/cmd");
		else if(strcmp(str,"volinc")==0)
			sprintf(cmd,"echo \"volume 30\" > /tmp/cmd");
		else if(strcmp(str,"voldec")==0)
			sprintf(cmd,"echo \"volume -30\" > /tmp/cmd");
		else
			return;
	}
	system(cmd);
}

void close_main(){
	system("killall mplayer");
	gtk_main_quit();
}

int timeout(gpointer data)
{
	if(status==STAT_STOP)
		return FALSE;
	if(status==STAT_PAUSE)
		return TRUE;
	system("echo \"get_percent_pos\" > /tmp/cmd");
	return TRUE;
}

void widget_destroy(GtkWidget *gw, gpointer data)
{
	gtk_widget_destroy(GTK_WIDGET(data));
}

void read_func(gpointer data)
{
	FILE *fpp=(FILE *)data;
	char str[256];
	int x_size,y_size,x,y;
	char *buf;
	int pos,value;

	while(!feof(fpp))
	{
		fgets(str,256,fpp);
		if(strstr(str,"ANS_PERCENT_POSITION")!=NULL)
		{
			buf=strstr(str,"ANS_PERCENT_POSITION");
			sscanf(buf,"ANS_PERCENT_POSITION=%i",&pos);
			value=gtk_adjustment_get_value(GTK_ADJUSTMENT(adjust));
			if(pos != value)
			{
				gdk_threads_enter();
				gtk_adjustment_set_value(GTK_ADJUSTMENT(adjust),pos);
				gdk_threads_leave();
			}
		}
	}
	pclose(fpp);
	gdk_threads_enter();
	gtk_statusbar_push(GTK_STATUSBAR(statbar),2,"stop");
	gdk_threads_leave();
	status=STAT_STOP;
}
void launch_mplayer(GtkWidget *gw,gpointer data)
{
	int fd_lst;
	FILE *fp_lst;;
	gchar *filepath; 
	gchar *filename;
	gchar *extname;
	gchar prename[256];
	gchar cmd[1024];
	gint i=0;
	unlink("/tmp/cmd");//删除一个文件的目录项并减少他的链接
	mkfifo("/tmp/cmd",0777);//建立实名管道
	if(status!=STAT_STOP)
	{
		status=STAT_STOP;
		gtk_timeout_remove(time_id);
		pthread_cancel(th);
		pclose(fp);
	}
	filepath=gtk_file_selection_get_filename(GTK_FILE_SELECTION(data));
	gtk_widget_destroy(GTK_WIDGET(data));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjust),0);
	filename=GetFileName(filepath);
	extname=GetFileExtName(filepath);
	if(extname==NULL)
	{
		gtk_statusbar_push(GTK_STATUSBAR(statbar),2,"stop");
		return;
	}
	for(i=0;i<6;i++)
	{
		if(strcmp(extname,ext[i])==0)
		{
			if(i==0)
			{
				gtk_widget_hide(draw_area);
				gtk_widget_set_size_request(GTK_WIDGET(statbar),320,-1);
			}
			else
				gtk_widget_show(draw_area);
			break;
		}
	}
	if(i==6)
	{
		gtk_statusbar_push(GTK_STATUSBAR(statbar),2,"stop");
		return;
	}
	i=GetFilePreName(prename,filename);
	prename[i]='\0';
	gtk_window_set_title(GTK_WINDOW(window),prename);
	sprintf(statbarinfo,"playing: %s",prename);
	gtk_statusbar_push(GTK_STATUSBAR(statbar),1,statbarinfo);
	fd_lst=open("/tmp/playlist",O_RDWR|O_CREAT|O_TRUNC,0666);
	fp_lst=fdopen(fd_lst,"w");//打开文件写模式
	fputs(filepath,fp_lst);//文件路径写进文件
	fputs("\n",fp_lst);
	fclose(fp_lst);//关闭文件
	close(fd_lst);//关闭文件描述符
	sprintf(cmd,"mplayer -slave -quiet -wid 0x%x -input file=/tmp/cmd -playlist /tmp/playlist", gtk_socket_get_id(GTK_SOCKET(draw_area)));
	status=STAT_PLAY;
	if((fp=popen(cmd,"r"))!=NULL)
	{
		pthread_create(&th,NULL,(void *)read_func,(void *)fp);
		pthread_detach(th);
	}
	time_id=gtk_timeout_add(1000,timeout,NULL);//每隔1000毫秒就执行timeout函数一次
}


void open_file_selection(GtkWidget *gw,gpointer data){
	GtkWidget *fileselect;
	fileselect=gtk_file_selection_new("打开文件");
	g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(fileselect)->ok_button),
			"clicked",G_CALLBACK(launch_mplayer),fileselect);
	g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(fileselect)->cancel_button),
			"clicked",G_CALLBACK(widget_destroy),fileselect);
	gtk_widget_show(fileselect);
}

/*帮助按钮下关于的界面*/
void about_main(){
	GtkWidget *about;
	GtkWidget *btn1,*btn2,*label;
	
	about=gtk_dialog_new();
	btn1=gtk_button_new_with_label("确定");
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(about)->action_area),btn1,FALSE,FALSE,0);
	g_signal_connect(G_OBJECT(btn1),"clicked",G_CALLBACK(widget_destroy),about);
	btn2=gtk_button_new_with_label("关闭");
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(about)->action_area),btn2,FALSE,FALSE,0);
	g_signal_connect(G_OBJECT(btn2),"clicked",G_CALLBACK(widget_destroy),about);
	label=gtk_label_new("\ngtkplayer 1.0.0");
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(about)->vbox),label,FALSE,FALSE,0);
	label=gtk_label_new("基于mplayer的播放前端 ^.^");
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(about)->vbox),label,FALSE,FALSE,0);
	label=gtk_label_new("981887932@qq.com\n");
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(about)->vbox),label,FALSE,FALSE,0);
	gtk_widget_show_all(about);
}

/*播放时进度条进行实时更新*/
void scale_value_changed(){
	gchar cmd[256];
	gint value;
	static int temp=0;
	
	value=gtk_adjustment_get_value(GTK_ADJUSTMENT(adjust));
	if((abs(value-temp))>1 && status!=STAT_STOP)
	{
		if(status==STAT_PAUSE)
			status=STAT_PLAY;
		sprintf(cmd,"echo \"seek %d 1\" > /tmp/cmd",value);
		system(cmd);
	}
	temp=value;
}

/*为了省略大量重复的代码量将创建一个标签盒封装一个函数*/


GtkWidget *xpm_label_button(gchar *xpm_filename, gchar *label_text )
{
	GtkWidget *box;
	GtkWidget *label;
	GtkWidget *image;
	GtkWidget *button;
	box = gtk_hbox_new (FALSE, 5);//新建一个盒子
	image = gtk_image_new_from_file (xpm_filename);//打开一个图像
	label = gtk_label_new (label_text);//新建一个标签
	gtk_box_pack_start (GTK_BOX (box), image, FALSE, FALSE, 0);//把图像放入盒子
	gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 0);//把标签放入盒子
	gtk_widget_show (image);
	gtk_widget_show (label);
	button = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(button),box);
	gtk_widget_show(box);
	return button;
}


int main(int argc , char *argv[]){
	GtkAccelGroup *accel;
	GtkWidget *menu_bar, *menu, *menu_item, *menu_app;
	GtkWidget *vbox, *hbox, *box;
	GdkColor color;
	if(!g_thread_supported()){
		g_thread_init(NULL);
	}
	gdk_threads_init();
	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
	//不允许改变窗口大小，自动窗口大小
	//默认值是FALSE,TRUE,FALSE
	//gtk_window_set_policy(GTK_WINDOW(window),FALSE,FALSE,TRUE);  
	gtk_window_set_title(GTK_WINDOW(window),"gtkplayer");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_default_icon_from_file("icons/icon.png",NULL);//设置窗体图标，使所有窗体使用同一个图标
	gtk_container_set_border_width(GTK_CONTAINER(window), 2);//设置窗体边框宽度
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
	
	accel=gtk_accel_group_new();//新建一个快捷键集
	gtk_window_add_accel_group(GTK_WINDOW(window),accel);//将窗体加入快捷键集中
	vbox=gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window),vbox);//将新建的盒子放入窗口
	
	menu_bar=gtk_menu_bar_new();
	gtk_box_pack_start(GTK_BOX(vbox),menu_bar,FALSE,FALSE,1);
	menu=gtk_menu_new();
	menu_item=gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN,accel);
	gtk_menu_append(GTK_MENU(menu),menu_item);
	g_signal_connect(G_OBJECT(menu_item),"activate",G_CALLBACK(open_file_selection),NULL);
	menu_item=gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT,accel);
	gtk_menu_append(GTK_MENU(menu),menu_item);
	g_signal_connect(G_OBJECT(menu_item),"activate",G_CALLBACK(close_main),NULL);
	menu_app=gtk_menu_item_new_with_label("文件");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_app), menu);
	gtk_menu_bar_append(GTK_MENU_BAR(menu_bar), menu_app);
	
	menu=gtk_menu_new();
	menu_item=gtk_image_menu_item_new_from_stock(GTK_STOCK_ABOUT,accel);
	gtk_menu_append(GTK_MENU(menu),menu_item);
	g_signal_connect(G_OBJECT(menu_item),"activate",G_CALLBACK(about_main),NULL);
	menu_app=gtk_menu_item_new_with_label("帮助");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_app), menu);
	gtk_menu_bar_append(GTK_MENU_BAR(menu_bar), menu_app);
	
	draw_area=gtk_socket_new();
	color.red=0;
	color.blue=0;
	color.green=0;
	gtk_widget_modify_bg(draw_area, GTK_STATE_NORMAL, &color);//设置播放界面构件的背景颜色 
	gtk_widget_set_size_request(GTK_WIDGET(draw_area),400,300);//设置播放界面的大小
	gtk_box_pack_start(GTK_BOX(vbox), draw_area, TRUE, TRUE,0);
	//比例构件(Scale widgets)一般用于允许用户在一个指定的取值范围你可视地选择和操纵一个值。例如，在图片的缩放预览中调整放大倍数，或控制一种颜色的亮度，或在指定屏幕保护启动之前不活动的时间间隔时，可能需要用到比例构件。
	adjust=gtk_adjustment_new(0.0, 0.0, 100.0, 0.1, 0.0, 0.0);//创建一个调整对象
	hscale=gtk_hscale_new(GTK_ADJUSTMENT(adjust));//创建一个水平的比列构建
	gtk_scale_set_digits(GTK_SCALE(hscale),0);//设置小数位数
	gtk_scale_set_value_pos(GTK_SCALE(hscale),GTK_POS_LEFT);//起始位置在左面
	gtk_range_set_update_policy(GTK_RANGE(hscale),GTK_UPDATE_DISCONTINUOUS);//比列构件的更新方式
	g_signal_connect(G_OBJECT(hscale),"value_changed",G_CALLBACK(scale_value_changed),NULL);//触发信号函数
	gtk_widget_set_size_request(GTK_WIDGET(hscale),-1,-1);//设置构件的最小尺寸
	gtk_box_pack_start(GTK_BOX(vbox),hscale,FALSE,FALSE,0);
	
	hbox = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,0);

	playbutton=xpm_label_button("icons/start.xpm","播放");
	g_signal_connect(G_OBJECT(playbutton),"clicked",G_CALLBACK(send_cmd),"play");
	gtk_box_pack_start(GTK_BOX(hbox),playbutton,FALSE,FALSE,0);

	pausebutton=xpm_label_button("icons/pause.xpm","暂停");
	g_signal_connect(G_OBJECT(pausebutton),"clicked",G_CALLBACK(send_cmd),"pause");
	gtk_box_pack_start(GTK_BOX(hbox),pausebutton,FALSE,FALSE,0);

	stopbutton=xpm_label_button("icons/stop.xpm","停止");
	g_signal_connect(G_OBJECT(stopbutton),"clicked",G_CALLBACK(send_cmd),"stop");
	gtk_box_pack_start(GTK_BOX(hbox),stopbutton,FALSE,FALSE,0);
	
	backbutton=xpm_label_button("icons/seek-backward.xpm","快退");
	g_signal_connect(G_OBJECT(backbutton),"clicked",G_CALLBACK(send_cmd),"back");
	gtk_box_pack_start(GTK_BOX(hbox),backbutton,FALSE,FALSE,0);
	
	fwordbutton=xpm_label_button("icons/seek-forward.xpm","快进");
	g_signal_connect(G_OBJECT(fwordbutton),"clicked",G_CALLBACK(send_cmd),"fword");
	gtk_box_pack_start(GTK_BOX(hbox),fwordbutton,FALSE,FALSE,0);
	
	
	volincbutton = gtk_button_new_with_mnemonic("音量++(_W)");
	g_signal_connect(G_OBJECT(volincbutton),"clicked",G_CALLBACK(send_cmd),"volinc");
	gtk_box_pack_start(GTK_BOX(hbox),volincbutton,FALSE,FALSE,0);

	voldecbutton = gtk_button_new_with_mnemonic("音量--(_S)");
	g_signal_connect(G_OBJECT(voldecbutton),"clicked",G_CALLBACK(send_cmd),"voldec");
	gtk_box_pack_start(GTK_BOX(hbox),voldecbutton,FALSE,FALSE,0);
	
	
	statbar=gtk_statusbar_new();
	gtk_statusbar_push(GTK_STATUSBAR(statbar),0,"myplayer");
	gtk_box_pack_start(GTK_BOX(vbox),statbar,FALSE,FALSE,0);

	table = gtk_table_new(1,4,FALSE);
	gtk_box_pack_start(GTK_BOX(vbox),table,FALSE,FALSE,0);
	mylable = gtk_label_new("我的播放器");
	gtk_table_attach_defaults(GTK_TABLE(table),mylable,0,1,1,3);
	
	gtk_widget_show_all(window);
	gdk_threads_enter();
	gtk_main();
	gdk_threads_leave();

	return FALSE;
}
