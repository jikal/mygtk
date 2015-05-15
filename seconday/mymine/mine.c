#include<gtk/gtk.h>

inline char *_(char* c){
	return (g_locale_to_utf8(c,-1,0,0,0));
}

struct block{
	gint count;//表示一个点周围有多少雷

	gboolean mine;//这个点是否藏有雷

	gboolean marked; //是否标记有雷

	gboolean opened; //是否被掀开

	GtkWidget *button;
};

static struct block *map;//整个地雷区图

static gint width = 10;//雷区的宽度

static gint height = 10;//雷区的高度

static gint mines = 10; //总共的地雷区

static GtkWidget *window;

static GtkWidget *mine_label;//显示剩余的地雷数

static GtkWidget *time_label;//用于游戏结束后的重新复位

static GtkWidget *reset;//用于游戏结束后重新复位

static gint button_size = 30; //每个按钮的大小

static gint opened_count;//已经掀开多少个鸽子

static gint marked_count;//已经标记了多少个格子

static gboolean game_over;//游戏是否结束的标志

static gint game_time;//游戏时间记录

static gint i = 0,j,index;

static gint size;//整个地区的大小

static gboolean mark;//由于记录是否按了复位键

static gboolean clicked;//用于表示是否按下掀开键

//游戏结束时间调用的函数

void gameover(gboolean won){
	GtkWidget *dialog;
	gchar buf[4];
	gchar msg[100];
	game_over=TRUE;
	if(won==TRUE){    //扫雷成功法人提示信息
		g_snprintf(msg,100,_("哇！你这么牛，用时 %3d 秒。"),game_time);
	}else{		//踩到地雷的情况
		g_snprintf(msg,100,_("太有才了！这么快就结束了～～"));
	}
	for(i=0,index=0;i<height;i++){
		for(j=0;j<width;j++){
			if(map[index].opened==FALSE){
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(map[index].button),TRUE);
				gtk_button_set_label(GTK_BUTTON(map[index].button)," ");
				if(map[index].mine == FALSE){
					if(map[index].count == 0){
						gtk_button_set_label(GTK_BUTTON(map[index].button),"");
					}else{
						g_snprintf(buf,4,"%d",map[index].count);
						gtk_button_set_label(GTK_BUTTON(map[index].button),buf);
					}
				}else{
					gtk_button_set_label(GTK_BUTTON(map[index].button),_("雷"));
				}
			}
			index++;
		}
	}
	dialog = gtk_message_dialog_new(GTK_WINDOW(window),0,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,msg);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}
//布雷函数

void put_mines(){
	while(i<mines){
		gint index;
		gint row,col;
		index = g_random_int_range(0,size);
;
		if(map[index].mine==TRUE){
			continue;
		}//如果此点有雷则跳过
		map[index].mine = TRUE;
		row = index/width;
		col = index%width;

		//周围格子的count加1
		if(row>0){
			if(col>0){
				map[index-width-1].count++;
				map[index-width].count++;
			}
			if(col<width-1){
				map[index-width+1].count++;
			}
		}
		if(col>0){
			map[index-1].count++;
		}
		if(col<width-1){
			map[index+1].count++;
		}
		if(row<height-1){
			if(col>0){
				map[index+width-1].count++;
				map[index+width].count++;
			}
			if(col<width-1){
				map[index+width+1].count++;
			}
		}
		i++;
	}

}

//打开某一个格子对应的函数

void open_block(gint x, gint y){
	gint index;
	GtkWidget *button;
	index = x+y*width;
	if(game_over == TRUE || map[index].marked == TRUE){
		return;//游戏结束或防止某家对已标记的盒子打开
	}
	button = map[index].button;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button),TRUE);//改变状态为按下
	clicked  = TRUE;//表示有敲击
	if(map[index].opened==TRUE){//防止打开已经打开的盒子
		return;
	}
	map[index].opened=TRUE;//打开盒子
	
	if(map[index].mine==TRUE){
		gtk_button_set_label(GTK_BUTTON(button),_("雷"));
		gameover(FALSE);//踩到地雷游戏结束
		return;	
	}
	if(map[index].count>0){//若周围有地雷
		gchar buf[2];
		g_snprintf(buf,2,"%d",map[index].count);
		gtk_button_set_label(GTK_BUTTON(button),buf);
	}
	opened_count++;//增加一个掀开的格子数
	if(opened_count+mines==width*height){//获胜的标志
		gameover(TRUE);
		return;
	}
	if(map[index].count==0){//若周围没有格子则掀开格子
		if(y>0){
			if(x>0){
				open_block(x-1,y-1);
				open_block(x,y-1);
			}
			if(x<width-1){
				open_block(x+1,y-1);
			}	
		}
		if(x>0){
			open_block(x-1,y);
		}
		if(x<width-1){
			open_block(x+1,y);
		}
		if(y<height-1){
			if(x>0){
				open_block(x-1,y+1);
				open_block(x,y+1);
			}
			if(x<width-1){
				open_block(x+1,y+1);
			}
		}
		
	}
}
//复位
void g_reset(GtkWidget *widget,gpointer *data){
	opened_count = 0;
	marked_count = 0;
	game_over = FALSE;
	mark=TRUE;
	clicked  =FALSE;
	gtk_label_set_text(GTK_LABEL(mine_label),"10");
	for(i=0,index=0;i<height;i++){
		for(j=0;j<width;j++){
			map[index].mine = FALSE;
			map[index].count = 0;
			map[index].marked = FALSE;
			map[index].opened = FALSE;
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(map[index].button),FALSE);
			gtk_button_set_label(GTK_BUTTON(map[index].button)," ");
			index++;
		}
	}
	i = 0;
	put_mines();
}

//计时器

gboolean tick(gpointer data){
	gchar buf[8];
	if(game_over == FALSE){//计时
		if(mark == TRUE){//得位标记mark为TRUE，则时间刷新为0
			game_time = 0;
			mark = FALSE;		
		}
		if(clicked == TRUE){//如果有掀雷，则开始倒计时
			game_time++;//增加游戏时间
			g_snprintf(buf,8,"%d",game_time);
		}else{
			g_snprintf(buf,2,"%d",game_time);//没有敲击时一直显示为0
			gtk_label_set_text(GTK_LABEL(time_label),buf);//刷新时间
		}
		
	}
	return TRUE;//返回TRUE继续计时
}
//键盘敲击时的敲击
gboolean on_mouse_click(GtkWidget *widget,GdkEventButton *event,gpointer data){
	gint index;
	gint row,col;
	gchar buf[4];
	if(game_over==TRUE){
		return TRUE;//游戏结束时按键失去作用
	}
	index = (gint)data;
	switch(event->button){
		case 1://左键
			row = index/width;
			col = index%width;
			open_block(col,row);
			break;
		case 2:
			break;
		case 3://右键
			if(map[index].opened == TRUE){//已经掀开的作标记
				break;
			}
			if(map[index].marked!=TRUE){
				map[index].marked=TRUE;
				gtk_button_set_label(GTK_BUTTON(widget),("*"));
				marked_count++;
			}else{
				map[index].marked = FALSE;
				gtk_button_set_label(GTK_BUTTON(widget),"");
				marked_count--;
			}
			//显示新的地雷数
			g_snprintf(buf,4,"%d",mines-marked_count);
			gtk_label_set_text(GTK_LABEL(mine_label),buf);			
	}
	return TRUE;	
}

int main(int argc , char *argv[]){
	size =  width*height;
	map = (struct block*)g_malloc0(sizeof(struct block)*width*height);//分配内容为0的内存空间
	put_mines();

	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *label;
	gtk_init(&argc,&argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"delete_event",gtk_main_quit,NULL);
	reset = gtk_button_new_with_label(_("重开"));
	gtk_widget_set_usize(reset,100,28);
	vbox = gtk_vbox_new(FALSE,0);
	hbox = gtk_hbox_new(FALSE,0);
	label = gtk_label_new("Mines:");
	gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,6);
	mine_label = gtk_label_new("10");
	gtk_box_pack_start(GTK_BOX(hbox),mine_label,FALSE,FALSE,3);
	gtk_box_pack_start(GTK_BOX(hbox),reset,FALSE,TRUE,6);
	label = gtk_label_new("Time:");
	gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,6);
	time_label = gtk_label_new("0");
	gtk_box_pack_start(GTK_BOX(hbox),time_label,TRUE,FALSE,0);
	gtk_widget_show_all(hbox);
	gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,0);
	for(i=0,index=0;i<height;i++){//初始化格子
		gint j;
		hbox = gtk_hbox_new(FALSE,0);
		for(j=0;j<width;j++){
			GtkWidget *button;
			button  = gtk_toggle_button_new();
			gtk_widget_set_usize(button,button_size,button_size);
			g_object_set(G_OBJECT(button),"can-focus",FALSE,NULL);
			gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,0);
			gtk_widget_show(button);
			g_signal_connect(G_OBJECT(button),"button-press-event",G_CALLBACK(on_mouse_click),(gpointer)index);
			map[index].button = button;
			index++;
		}
		gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,0);
		gtk_widget_show(hbox);
	}
	gtk_container_add(GTK_CONTAINER(window),vbox);
	gtk_widget_show(vbox);
	gtk_widget_show(window);
	g_timeout_add(1000,(GSourceFunc)tick,NULL);//计时器启动
	g_signal_connect(GTK_OBJECT(reset),"clicked",GTK_SIGNAL_FUNC(g_reset),NULL);
	gtk_main();
	return FALSE;
}

