/*
 * Written by Serikzhan S. Kazi ©
 * Basically, stolen and adapted from:
 * 1) Richard Heathfield, "The C Unleashed"
 * 2) Wikipedia select() article http://en.wikipedia.org/wiki/Select_%28Unix%29
 * 3) stackoverflow.com
 *
 * COMPILE: gcc -o my_client client.c
 * USAGE  : ./my_client hostname filename_to_be_sent
 * TESTed: with "localhost" only
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#define LEN (1 << 21)
#define DBG(x) (x)

int rndm( int n ) { return (int)(n*((rand()/(1.0+(double)RAND_MAX)))); }
char buff[LEN];

int main( int argc, char **argv ) {
	int sockfd = 0,block_size;
	char data[0xff] = {0},file_to_send[0x400];
	struct in_addr serv_addr;
	struct hostent *he;
	struct sockaddr_in their_addr;
	FILE *fp;
	
	srand(time(NULL));
	if ( argc < 3 ) {
		fputs("usage: application hostname filename\n",stderr);
		return 1;
	}

	if ( !(fp = fopen(argv[2],"r")) ) {
		fprintf(stderr,"Error with opening file %s\n",argv[2]);
		return 1;
	}

	/* inet_aton(argv[1],&serv_addr); */

	if ( !(he = gethostbyname("localhost")) ) {
		perror("gethostbyname()");
		switch ( h_errno ) {
			case HOST_NOT_FOUND:
				puts("HOST_NOT_FOUND");
				break ;
			case NO_ADDRESS:
				puts("NO_ADDRESS");
				break ;
			case NO_RECOVERY:
				puts("NO_RECOVERY");
				break ;
			case TRY_AGAIN:
				puts("TRY_AGAIN");
				break ;
		}
		return 1;
	}

	if ( (sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1 ) {
		puts("Error with socket()");
		return 1;
	}

	their_addr.sin_family = AF_INET, their_addr.sin_port = htons(1089);
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	memset(their_addr.sin_zero,0,sizeof their_addr.sin_zero);

	if ( connect(sockfd,(struct sockaddr *)&their_addr,sizeof(struct sockaddr)) == -1 ) {
		puts("Error with connect()");
		return 1;
	}

	/*
	 * Sending the contents
	 */
	for(;(block_size = fread(buff,sizeof 0[buff], LEN,fp))>0;) 
		if ( send(sockfd,buff,block_size,0) == -1 ) {
			puts("Error with send()");
			return 1;
		}
	fclose(fp);

	/*
	memset(data,0,sizeof data);
	if ( recv(sockfd,data,sizeof data,0) == -1 ) {
		puts("Error with recv()");
		return 1;
	}
	printf("Received: %s\n",data);
	*/

	shutdown(sockfd,2);
	return 0;
}

