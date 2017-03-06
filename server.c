#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define MAXLEN 0x400

volatile sig_atomic_t done;

char data[1 << 21],tmp[0x400];

void inthandler( int Sig ) { done = 1; }
FILE *res_file[0x400];

int check_for_data( int sockfd ) {
	struct timeval tv;
	fd_set read_fd;
	tv.tv_sec = 0, tv.tv_usec = 0;
	FD_ZERO(&read_fd);
	FD_SET(sockfd, &read_fd);
	if ( select(sockfd+1, &read_fd, NULL, NULL, &tv) == -1 )
		return 0;
	if ( FD_ISSET(sockfd,&read_fd) )
		return 1;
	return 0;
}

void die( const char *p ) {
	perror(p);
	exit(EXIT_FAILURE);
}

int main( int argc, char **argv ) {
	int sockfd = 0,read_size,written,i,j,k,
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
	if ( bind(sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr)) == -1 ) {
		puts("Unexpected error on bin()");
		return 1;
	}
	if ( listen(sockfd,4) == -1 ) {
		puts("Unexpected error on listen()");
		shutdown(sockfd,2);
		return 1;
	}
	FD_ZERO(&master);
	FD_ZERO(&read_fds);
	FD_SET(sockfd,&master);
	maxfd = sockfd;
	for(;;) {
		memcpy(&read_fds,&master,sizeof(master));
		if ( (nready = select(maxfd+1,&read_fds,NULL,NULL,NULL)) == -1 ) {
			puts("Error with select()");
			return 1;
		}
		for ( i = 0; i <= maxfd && nready > 0; ++i ) {
			if ( FD_ISSET(i,&read_fds) ) {
				--nready;
				if ( i == sockfd ) {
					new_fd = accept(sockfd,NULL,NULL);
					FD_SET(new_fd,&master);
					if ( maxfd < new_fd ) {
						maxfd = new_fd;
						sprintf(tmp,"received_%04d.txt",new_fd);
						res_file[new_fd] = fopen(tmp,"w");
					}
				}
				else {
					if ( (nbytes = recv(i,data,sizeof data,0)) <= 0 )
						die("recv()");
					if ( (fwrite(data,sizeof *data,nbytes,res_file[i])) < nbytes )
						die("fwrite()");
					close(i);
					FD_CLR(i,&master);
				}
			}
		}
	}
	for ( i = 0; i <= maxfd; ++i )
		if ( i != sockfd )
			if ( res_file[i] )
				fclose(res_file[i]);

	/*
	fp = fopen("received_01.txt","w");
	for(;!done;) 
		if ( 0 != check_for_data(sockfd) ) {
			sin_size = sizeof(struct sockaddr_in);
			if ( (new_fd = accept(sockfd,(struct sockaddr *)&their_addr, &sin_size)) == -1 ) {
				puts("Unexpected error on accept()");
				continue ;
			}
			memset(data,0,sizeof data);
			if ( (read_size = recv(new_fd,data,sizeof data,0)) == -1 ) 
				puts("Unexpected error on recv()");
			else {
				if ( (written = fwrite(data,sizeof 0[data],read_size,fp)) < read_size ) {
					puts("write() failed on server.");
				}
			}
			shutdown(new_fd,2);
		}
	if ( fp ) fclose(fp);
	*/

	shutdown(sockfd,2);
	puts("User requested program to halt.");

	return 0;

}

