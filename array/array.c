#include <stdio.h>
#include <stdlib.h> 

#define ROW 16
#define COL 16

int a[ROW][COL];
int temp[ROW*COL];
int count;

//p_2维数组
//temp _ 存储数组
//row 要取出的第一个行号
//col 要取出的第一个列号
//count 存放数组的下标
/*先取一次*/
void getOneTime(int (*p)[COL],int *temp,int row,int col,int *count){
	int i,j;
	for(i=row;i<8+row;++i){//行
		for(j=col;j<8+col;++j){
			temp[(*count)++] = p[i][j]; 
		}
	}
}
/*再取第一个把行*/
void getOneRow(int (*p)[COL],int *temp,int row,int col,int *count){
	int i;
	for(i=0;i<ROW/8;++i){
		getOneTime(p,temp,row,col+i*8,count);
	}
}
/*取出所有*/
void getAll(int (*p)[COL],int *temp,int row,int col,int *count){
	int i;
	for(i=0;i<ROW/8;++i){
		getOneRow(p,temp,row+i*8,col,count);
	}
}
//打印出数组元素
void myProw(int *a,int col){
	int i;
	for(i=0;i<col;++i){
		printf("%d ",a[i]);
	}
	printf("\n");
}

void myPall(int (*p)[COL],int row){
	int i;
	for(i=0;i<row;++i){
		myProw(p[i],COL);
	}
}


int main(int argc,char **argv){

	
	int i,j;
	for(i=0;i<ROW;++i){
		for(j=0;j<COL;++j){
			a[i][j] = rand()%100;
		}
	}
	myPall(a,ROW);
	printf("******************\n");
	getAll(a,temp,0,0,&count);
	myProw(temp,ROW*COL);
	return 0;
}
