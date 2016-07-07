#include <stdio.h>
#include <stdlib.h>	/* exit() */
#include <string.h>	/* strlen() */
#include "tcp_util.h"

extern	void server( int portno );

int buffer_size;
char *rbuf;

/* get integer from argv */
int get_count(int index,char **argv){
  return atoi(argv[index]);
}

main( int argc, char *argv[] )
{
    int portno ;

	if( argc == 1 )
	{
	    fprintf( stdout,"Usage: %s <portno> <buffer_size>\n",argv[0] );
	    exit( -1 );
	}

	portno = get_count(1,argv);
    buffer_size = get_count(2,argv);
    printf("port: %d, buffer size: %d\n",portno,buffer_size);
	server( portno );
}

void write_data_forever(int socket){
	  while(write(socket,rbuf,buffer_size)  != 0){
	  }
}

void
server( int portno )
{
    int sock_fd,socket ;
    pid_t child_pid ;
	sock_fd = tcp_bind( portno,0);
	if( sock_fd < 0 )
	    exit( -1 );
	tcp_print_host( portno );
	while( 1 )
	{
	    if( (socket = tcp_accept(sock_fd)) < 0 )
	    {
		perror("accept");
		exit( -1 );
	    }
	    tcp_print_peeraddr( socket );
		rbuf = (char *) malloc(buffer_size);
	    write_data_forever(socket);
	}
}
