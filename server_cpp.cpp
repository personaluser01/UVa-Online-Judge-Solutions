/*
 * Written by Serikzhan S. Kazi ©
 * Basically, stolen and adapted from:
 * 1) Richard Heathfield, "The C Unleashed"
 * 2) Wikipedia select() article http://en.wikipedia.org/wiki/Select_%28Unix%29
 * 3) stackoverflow.com
 *
 * COMPILE: g++ -o my_server server_cpp.cpp
 * DESCRIPTION: Receives files from clients; names them, successively, as "received_0002.txt", "received_0003.txt", etc.
 */
#include <stdio.h>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define MAXLEN 0x400
using namespace std;

volatile sig_atomic_t done;

char data[1 << 21],tmp[0x400];
map<int,int> m;

void inthandler( int Sig ) { done = 1; }

FILE *res_file[0x400];

void die( const char *p ) {
	perror(p);
	exit(EXIT_FAILURE);
}

int main( int argc, char **argv ) {
	int sockfd = 0,read_size,written,i,j,k,cur,
		nready,maxfd,new_fd,nbytes;
	struct sockaddr_in my_addr,their_addr;
	socklen_t sin_size = 0;
	fd_set master,read_fds;
	char *endp;
	FILE *fp;

	if ( signal(SIGINT,SIG_IGN) != SIG_IGN )
		signal(SIGINT,inthandler);
	if ( signal(SIGTERM,SIG_IGN) != SIG_IGN )
		signal(SIGTERM,inthandler);

	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = INADDR_ANY;
	my_addr.sin_port = htons(1089);
	memset(my_addr.sin_zero,0,sizeof my_addr.sin_zero);
	if ( (sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1 ) {
		puts("Unexpected error on socket()");
		return 1;
	}
	if ( bind(sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr)) == -1 ) 
		die("bind()");
	if ( listen(sockfd,4) == -1 ) {
		shutdown(sockfd,2);
		die("listen()");
	}
	FD_ZERO(&master);
	FD_ZERO(&read_fds);
	FD_SET(sockfd,&master);
	m.clear(), m[maxfd = sockfd] = (cur = 0),++cur;

	for(;;) {
		memcpy(&read_fds,&master,sizeof(master));
		if ( (nready = select(maxfd+1,&read_fds,NULL,NULL,NULL)) == -1 ) {
			die("select()");
		}
		for ( i = 0; i <= maxfd && nready > 0; ++i ) {
			if ( FD_ISSET(i,&read_fds) ) {
				--nready;
				if ( i == sockfd ) {
					new_fd = accept(sockfd,NULL,NULL);
					FD_SET(new_fd,&master);
					if ( maxfd < new_fd ) maxfd = new_fd;
					if ( m.find(new_fd) == m.end() ) {
						m[new_fd] = ++cur;
						printf("New descriptor arrived %d, mapped to %d\n",new_fd,cur);
						sprintf(tmp,"received_%04d.txt",m[new_fd]);
						res_file[m[new_fd]] = fopen(tmp,"w");
					}
				}
				else {
					if ( (nbytes = recv(i,data,sizeof data,0)) <= 0 )
						die("recv()");
					if ( (fwrite(data,sizeof *data,nbytes,res_file[m[i]])) < nbytes )
						die("fwrite()");
					close(i);
					FD_CLR(i,&master);
					m.erase(m.find(i));
				}
			}
		}
	}
	for ( map<int,int>::iterator it = m.begin(); it != m.end(); ++it )
		if ( it->second != sockfd )
			if ( res_file[it->first] )
				fclose(res_file[it->first]);

	shutdown(sockfd,2);
	puts("User requested program to halt.");

	return 0;

}

