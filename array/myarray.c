#include <stdio.h>
#include <stdlib.h>
#define ROW 16
#define COL 16
int array[ROW][COL];
int temp[ROW*COL];
int count;


void myProw(int a[ROW*COL],int col){
	int i;
	for(i=0;i<col;++i){
		printf("%d ",a[i]);
	}
	printf("\n");
}

void myPall(int p[ROW][COL],int row){
	int i;
	for(i=0;i<row;++i){
		myProw(p[i],COL);
	}
}

int main(){
	if((ROW% 8 !=0) || (COL % 8 != 0)){
		printf("你的数组参数定义不正确！\n");
		return;
	}
	int m,n;
	for(m=0;m<ROW;++m){
		for(n=0;n<COL;++n){
			array[m][n] = rand()%100;
		}
	}
	myPall(array,ROW);
	printf("*************************************************************\n");
	int i,j,k,l = 0;
	for(i=0;i<ROW/8;++i){
		for(j=0;j<ROW/8;++j){
			for(k=i*8;k<(i+1)*8;++k){
				for(l=j*8;l<(j+1)*8;++l){
					temp[count++]=array[k][l];
				}
			}
		}
	}
	myProw(temp,ROW*COL);
	return 0;
}
