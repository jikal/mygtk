#include<stdio.h>

struct Stu{
	int num;
	char name[];
	struct Student *next;
	struct Student *prev;
};
struct Stu Node;
