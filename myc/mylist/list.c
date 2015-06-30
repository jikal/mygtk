#include "list,h"

//创建头节点，并建立链表
Node *creatHead(void){
	Node *head = (Node *)calloc(1,sizeof(Node));
	if(NULL==head){
		return NULL;
	}else{
		head->next = head;
		head->prev = head;
	}
	return head;
}

//链表头插法

int insertHead(Node *head,Node *newhead){
	if(head == NULL||newhead == NULL){
		return -1;
	}
	newhead->prev = head;
	newhead->next = head->next;
	head->next = newhead;
}
//链表尾插法
int insertTail(Node *head,Node *newhead){
	if(head==NULL||newhead == NULL){
		return -1;
	}

	newhead->next = head;
	head->prev->next = newhead;
	newhead->prev = head->prev; 
//链表长度

int sizeList(Node *head){
	Node *cur = head->next;
	int count = 0;
	while(cur!=head){
		count++;
		cur =  cur->next;
	}
	return count;
}

//c查看链表的回调函数
static void showStu(const Node *e){
	printf("num:%10d,name:%5.2s\n",e->num,e->name);
}
void showList(Node *head){
	Node *cur = head->next;
	while(cur != head){
		showStu(cur);
		cur = cur->next;
	}
	printf("\n");
}
//创建一个节点
Node *creatNode(void){
	Node *newNode = (Node *)malloc(sizeof(Node));
	if(newNode == NULL){
		return NULL;
	}
	newNode ->next = NULL;
	newNode ->prev = NULL;
	return newNode;	
}

