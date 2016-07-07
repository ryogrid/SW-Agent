#include <sys/types.h>	/* socket(), wait4() */
#include <sys/socket.h>	/* socket() */
#include <netinet/in.h>	/* struct sockaddr_in */
#include <sys/resource.h> /* wait4() */
#include <sys/wait.h>	/* wait4() */
#include <netdb.h>	/* getnameinfo() */
#include <sys/ioctl.h>

/* for server */
extern	int tcp_bind( int portno , int async);	/* return socket file descriptor*/
extern  int tcp_accept(int sock_fd);   /* return socket */
extern	int tcp_open_stream( int sock, FILE **inp, FILE **outp ); /* create in/out stream with socket from accept function or tcp_connect function*/

/* for client */
extern  int tcp_connect( char *server, int portno );

/* utility */
extern	void tcp_print_host( int portno );   /* print information about binding host and port */
extern	void tcp_print_peeraddr( int sock );  /* print information abount accepted connection with socket from accept function */

extern int tcp_async_accept(int (accept_func)(int sock));
extern int tcp_async_read(int (read_func)(int sock));
extern int tcp_async_write(int (write_func)(int sock));
extern int tcp_async_disconnect(int (disconnect_func)(int sock));

#define BUFFERSIZE      1024
