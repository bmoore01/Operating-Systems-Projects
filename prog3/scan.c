#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>


int main(int argc, char **argv[]) {
		int sockfd = 0;
		int ports[] = {21,22,23,25,80,143,443}; // ports to scan
		int size = sizeof(ports) / sizeof(ports[0]); // get size of array of ports
		int i;
		struct sockaddr_in serv_addr;
		struct timeval timeout;
		timeout.tv_sec = 2;
		timeout.tv_usec = 0;
		//char * address = malloc(strlen(argv[1]));

		/* The switching localhost to the loopback address
		 * would work from time to time but then it would give me a 
		 * Seg fault so I'm not risking submitting it, but I'm sure I just
		 * need to do some more reading on how to use those pesky
		 * pointers
		 */
		
		/*
		if you user passes localhost switch it to loopback address
		if(strcmp(argv[1],"localhost") == 0)
				address = "127.0.0.1";
		else
				address = argv[1];
		*/

		if (argc != 2) {
				printf("Usage: %s <IP of server>\n", argv[0]);
				return 1;
		}


		if((sockfd = socket(AF_INET,SOCK_STREAM, 0)) < 0) {
				printf("\n Error: Could not create socket \n");
				return 1;
		}

		memset(&serv_addr, '0', sizeof(serv_addr));

		serv_addr.sin_family = AF_INET;

		if(inet_pton(AF_INET, argv[1],&serv_addr.sin_addr)<=0) {
				printf("\n inet_pton error occured\n");
				return 1;
		}
		
		if(setsockopt(sockfd, SOL_SOCKET,SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0) {
				printf("Error: setsockopt failed\n");
				return 1;
		}

		printf("PORT\t STATE\n");

		for(i = 0; i < size; i++) { 

			serv_addr.sin_port= htons(ports[i]); 

			if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0) {
					close(sockfd);
					printf("%d/tcp\t open\n",ports[i]);

					if((sockfd = socket(AF_INET,SOCK_STREAM, 0)) < 0) 
						printf("\n Error: Could not create socket \n");
			} 
			else
					printf("%d/tcp\t closed\n",ports[i]);
		}

		close(sockfd); //if not closed close at the end of the program

		return 0;
}
