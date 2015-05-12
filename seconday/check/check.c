#include <gtk/gtk.h>
gboolean isbold = FALSE;
gboolean isitli = FALSE;
gboolean isuline = FALSE;
gboolean iscolor = FALSE;
GtkWidget *window;
GtkWidget *frame;
GtkWidget *box;
GtkWidget *box1;
GtkWidget *button;  
GtkWidget *check1;
GtkWidget *check2;
GtkWidget *check3;
GtkWidget *check4;
GtkWidget *allcheck;
GtkWidget *countercheck; 


void on_check_clicked(GtkWidget *check,gpointer data){
	switch((int)data){
		case 1:
			isbold = !isbold;
			printf("1\n");
			break;
		case 2:
			isitli = !isitli;
			break;
		case 3:
			isuline = !isuline;
			break;
		case 4:
			iscolor = !iscolor;
			break;	
	}
}
void on_allcheck_clicked(GtkWidget *check,gpointer data){
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check1),TRUE);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check2),TRUE);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check3),TRUE);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check4),TRUE);
}

void on_countercheck_clicked(GtkWidget *check,gpointer data){
	if(isbold  == TRUE){
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check1),FALSE);
	}else{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check1),TRUE);
	}
	
	if(isitli  == TRUE){
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check2),FALSE);
	}else{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check2),TRUE);
	}
	if(isuline  == TRUE){
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check3),FALSE);
	}else{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check3),TRUE);
	}
	if(iscolor  == TRUE){
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check4),FALSE);
	}else{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check4),TRUE);
	}
		

}

int main(int argc,char *argv[])  
{    
  
	gtk_init(&argc,&argv);  
//新建一个窗口  
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  
	gtk_window_set_title(GTK_WINDOW(window),"check button demo");  
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);  
	gtk_window_set_default_size(GTK_WINDOW(window),200,200);  
	g_signal_connect(GTK_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);

	box = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),box);
	allcheck = gtk_radio_button_new_with_label(NULL,"全选");
	g_signal_connect(GTK_OBJECT(allcheck),"released",G_CALLBACK(on_allcheck_clicked),NULL);
	gtk_box_pack_start(GTK_BOX(box),allcheck,FALSE,FALSE,3);

	countercheck = gtk_radio_button_new_with_label(NULL,"反选");
	g_signal_connect(GTK_OBJECT(countercheck),"released",G_CALLBACK(on_countercheck_clicked),NULL);
	gtk_box_pack_start(GTK_BOX(box),countercheck,FALSE,FALSE,3);	
	
	frame = gtk_frame_new("字体选项： ");
	gtk_box_pack_start(GTK_BOX(box),frame,FALSE,FALSE,5);

	box1 = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(frame),box1);
	gtk_container_set_border_width(GTK_CONTAINER(box1),10);
	gtk_widget_show(box);

	check1 = gtk_check_button_new_with_label(" 粗体 ");
	g_signal_connect(G_OBJECT(check1),"clicked",G_CALLBACK(on_check_clicked),(gpointer)1);
	gtk_box_pack_start(GTK_BOX(box1),check1,FALSE,FALSE,3);

	check2 = gtk_check_button_new_with_label(" 斜体 ");
	g_signal_connect(G_OBJECT(check2),"clicked",G_CALLBACK(on_check_clicked),(gpointer)2);
	gtk_box_pack_start(GTK_BOX(box1),check2,FALSE,FALSE,3);

	check3 = gtk_check_button_new_with_label(" 下划线 ");
	g_signal_connect(G_OBJECT(check3),"clicked",G_CALLBACK(on_check_clicked),(gpointer)3);
 	gtk_box_pack_start(GTK_BOX(box1),check3,FALSE,FALSE,3);

	check4 = gtk_check_button_new_with_label(" 颜色 ");
	g_signal_connect(G_OBJECT(check4),"clicked",G_CALLBACK(on_check_clicked),(gpointer)4);
	gtk_box_pack_start(GTK_BOX(box1),check4,FALSE,FALSE,3);
  
	//gtk_container_add(GTK_CONTAINER(window),check_button);  
	gtk_widget_show_all(window);  
	gtk_main();  
      
	return FALSE;  
} 
