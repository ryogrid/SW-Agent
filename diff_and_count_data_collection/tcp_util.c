#include <stdio.h>
#include <string.h>	/* strlen() */
#include <sys/ioctl.h>
#include "tcp_util.h"

fd_set rfds,wfds,efds;
int listening_socket;

int tcp_bind( int portno , int async)
{
    struct sockaddr_in addr ;
    int addr_len ;
    int inet_option;
    int sock_optval = 1;
    int val;

    if(async){
      inet_option = AF_INET;
    }else{
      inet_option = PF_INET;
    }

    if( (listening_socket = socket(inet_option, SOCK_STREAM, 0)) < 0 )
      {
	perror("socket");
	return( -1 );
      }

    if(async){
      if ( setsockopt(listening_socket, SOL_SOCKET, SO_REUSEADDR,
		      &sock_optval, sizeof(sock_optval)) == -1 ){
	perror("setsockopt");
	exit(1);
      }
    }

	memset( &addr, 0, sizeof(addr) );
	addr.sin_family = AF_INET ;
	addr.sin_addr.s_addr = INADDR_ANY ;
	addr.sin_port = htons( portno );

	if( bind(listening_socket,(struct sockaddr *)&addr,sizeof(addr)) < 0 )
	{
	    perror("bind");
	    fprintf(stderr,"port number %d is already used. wait a moment or kill another program.\n", portno );
	    return( -1 );
	}
	if( listen( listening_socket, 5 ) < 0 )
	{
	    perror("listen");
	    close( listening_socket );
	    return( -1 );
	}

	if(async){
	  FD_ZERO( &rfds );
	  FD_SET(listening_socket, &rfds );
/* 	  make socket non blocking mode */
/*        if use MSG_DONTWAIT flag on send(), this isn't necessary */
/* 	  val = 1; */
/* 	  ioctl(listening_socket, FIONBIO, &val); */
	}

	return( listening_socket );
}

int tcp_accept(int sock_fd){
  return accept(sock_fd,0,0);
}

/* try to accept. if request exists, add client's sockfd to fdsets(rfds,wfds,efds) */
/* accept_func: function which is executed after accept operation */
/* return: 0 -> not accepted , 1 -> accepted */
int tcp_async_accept(int (accept_func)(int sock)){
  struct sockaddr_in client_address;
  int client_sockfd;
  int client_len;
  int result;
  struct timeval timeout = {0, 0};
  fd_set tmp_rfds;

  memcpy(&tmp_rfds, &rfds, sizeof(rfds));
  result = select(FD_SETSIZE,&tmp_rfds,( fd_set* ) 0,( fd_set* ) 0,&timeout );
  if ( result < 0 ) {
    perror( "async_accept error!" );
  }

  if(FD_ISSET(listening_socket,&tmp_rfds)){
    client_sockfd = accept(listening_socket, ( struct sockaddr* ) & client_address, &client_len );

    if ( client_sockfd == -1 ){
      perror("accept");
      exit(1);
    }

    if ( client_sockfd > FD_SETSIZE-1 ){
      perror("accept");
      exit(1);
    }

    FD_SET( client_sockfd, &rfds );
    FD_SET( client_sockfd, &wfds );
    FD_SET( client_sockfd, &efds );

    accept_func(client_sockfd);

    return 1;
  }else{
    return 0;
  }
}

int tcp_async_read(int (read_func)(int sock)){
  int fd;
  FILE *in, *out;
  int result;
  struct timeval timeout = {0, 0};
  fd_set tmp_rfds;

  memcpy(&tmp_rfds, &rfds, sizeof(rfds));
  result = select(FD_SETSIZE,&tmp_rfds,( fd_set* ) 0,( fd_set* ) 0,&timeout );
  for(fd = 0;fd < FD_SETSIZE;fd++){
    if(FD_ISSET(fd,&tmp_rfds) && (fd != listening_socket)){
      read_func(fd);
/*       tcp_open_stream(fd,&in,&out); */
/*       read_func(in); */
/*       fclose(in); */
/*       fclose(out); */
    }
  }
}

int tcp_async_write(int (write_func)(int sock)){
  int fd;
  FILE *in, *out;
  int result;
  struct timeval timeout = {0, 0};
  fd_set tmp_wfds;

  memcpy(&tmp_wfds, &wfds, sizeof(wfds));
  result = select(FD_SETSIZE,( fd_set* ) 0,&tmp_wfds,( fd_set* ) 0,&timeout );
  for(fd = 0;fd < FD_SETSIZE;fd++){
    if(FD_ISSET(fd,&tmp_wfds) && (fd != listening_socket)){
      write_func(fd);
/*       tcp_open_stream(fd,&in,&out); */
/*       write_func(out); */
/*       fclose(in); */
/*       fclose(out); */
    }
  }
}

/* disconnect_func: function which is executed after disconnect operation */
int tcp_async_disconnect(int (disconnect_func)(int sock)){
  int fd,result;
  struct timeval timeout = {0, 0};
  fd_set tmp_efds;

  memcpy(&tmp_efds, &efds, sizeof(efds));
  result = select(FD_SETSIZE,( fd_set* ) 0,( fd_set* ) 0,&tmp_efds,&timeout );
  for(fd = 0;fd < FD_SETSIZE;fd++){
    if(FD_ISSET(fd,&tmp_efds) && (fd != listening_socket)){
      FD_CLR(fd,&rfds);
      FD_CLR(fd,&wfds);
      FD_CLR(fd,&efds);
      disconnect_func(fd);
      close(fd);
    }
  }
}

int
tcp_open_stream( int sock, FILE **inp, FILE **outp )
{
    int sock2 ;
	if( (sock2=dup(sock)) < 0 )
	{
	    return( -1 );
	}
	if( (*inp = fdopen( sock2, "r" )) == NULL )
	{
	    close( sock2 );
	    return( -1 );
	}
	if( (*outp = fdopen( sock, "w" )) == NULL )
	{
	    fclose( *inp );
	    *inp = 0 ;
	    return( -1 );
	}
	setvbuf(*outp, (char *)NULL, _IOLBF, 0);
	return( 0 );
}

static int sockaddr_in_init( struct sockaddr_in *addr, int addrlen,char *hostname, int portno ){
    struct addrinfo hints, *ai;
    int err ;

    if( addrlen < sizeof(struct sockaddr_in) ){
      fprintf(stderr,"sockaddr_in, not enough space (%d) > (%d)\n",addrlen, sizeof(struct sockaddr_in) );
      return( -1 );
    }
    memset( &hints, 0, sizeof(hints) );
    hints.ai_family   = AF_INET ; /* IPv4 */
    if( (err = getaddrinfo( hostname, NULL, &hints, &ai )) ){
      fprintf(stderr,"unknown host %s (%s)\n",hostname,gai_strerror(err) );
                  return( -1 );
    }
    if( ai->ai_addrlen > addrlen ){
      fprintf(stderr,"sockaddr too large (%d) > (%d)\n",ai->ai_addrlen,sizeof(addr) );
      freeaddrinfo( ai );
      return( -1 );
    }
    memcpy( addr, ai->ai_addr, ai->ai_addrlen );
    addr->sin_port = htons( portno );
    freeaddrinfo( ai );

    return( 0 );
}

int
tcp_connect( char *server, int portno )
{
  struct addrinfo hints, *ai;
  struct sockaddr_in addr ;   /* IPv4 */
  int s ;
  int err ;

  if( (s = socket(PF_INET, SOCK_STREAM, 0)) < 0 ){
    perror("socket");
    return( -1 );
  }
  if( sockaddr_in_init( &addr, sizeof(addr), server, portno )<0 ){
      perror("sockaddr_in_init");
      return( -1 );
  }
  if( connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0 ){
      perror( server );
      close( s );
      return( -1 );
  }
  return( s );
}

void
tcp_print_host( int portno )
{
    char hostname[100] ;
	gethostname( hostname,sizeof(hostname) );
	hostname[99] = 0 ;
	printf("open http://%s:%d/[filepath]\n",hostname, portno );
}

void
static tcp_print_sockaddr( struct sockaddr *addrp, socklen_t addr_len )
{
    char host[BUFFERSIZE] ;
    char port[BUFFERSIZE] ;
	if( getnameinfo(addrp, addr_len, host, sizeof(host),
			port, sizeof(port), NI_NUMERICHOST|NI_NUMERICSERV)<0 )
	    return;
    	printf("%s:%s", host, port );
}

void
tcp_print_peeraddr( int socket )
{
    struct sockaddr_storage addr ;
    socklen_t addr_len ; /* MacOSX: __uint32_t */
	addr_len = sizeof( addr );
    	if( getpeername( socket, (struct sockaddr *)&addr, &addr_len  )<0 )
	{
	    perror("tcp_peeraddr_print");
	    return;
	}
    	printf("[%d] connection (fd==%d) from ",getpid(),socket );
	tcp_print_sockaddr( (struct sockaddr *)&addr, addr_len );
	printf("\n");
}



