#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define PORT 8000

int main(int argc,char **argv){
	int sockfd = -1;
	struct sockaddr_in clientaddr;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	memset(&clientaddr,0,sizeof(clientaddr));
	clientaddr.sin_family = AF_INET;
	clientaddr.sin_port = htons((short)PORT);
	clientaddr.sin_addr.s_addr = inet_addr( "127.0.0.1" );
	if(connect(sockfd,(struct sockaddr*)&clientaddr,sizeof(clientaddr)) == -1){
		printf("connect failed!\n");
		exit(0);
	}
	client_oprate(sockfd);
	close(sockfd);
	return 0;
}

void client_oprate(int fd){		
	char buf[128] = "my first work!";
	char readbuf[128]  = {};
	write(fd,buf,sizeof(buf));
	read(fd,readbuf,sizeof(readbuf));
	printf("%s\n",readbuf);
}
