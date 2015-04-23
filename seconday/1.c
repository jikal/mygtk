#include <stdio.h>
int main(){
	int &a = *(int *)(0);
	printf("%p\n",&a);

	return 0;
}
