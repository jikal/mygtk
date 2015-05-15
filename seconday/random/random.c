#include<stdio.h>

#include <gtk/gtk.h>

int main(int argc, char *argv[]){
	gint index;
	gint i = 0;
	gtk_init(&argc,&argv);
	while(i<10){
		index = g_random_int_range(0,10);
		printf("%d\n",index);
		i++;
	}
	gtk_main();
	return FALSE;
}
