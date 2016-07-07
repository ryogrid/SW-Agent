#include <stdio.h>
#include <stdlib.h>     /* exit() */
#include <string.h>     /* memset(), memcpy() */
#include<sys/time.h> /* gettimeofday() */
#include "tcp_util.h"

int buffer_size;
int ex_count;
int division_sec;

double get_second()
{
  struct timeval  t_tv;
  struct timezone t_tz;
  double time;


  gettimeofday(&t_tv,&t_tz);

  time =  t_tv.tv_sec;
  time   += ((double)(t_tv.tv_usec))/1000000.0;

  return time;
}

int
client( char *server, int portno )
{
	int sock;
	char *rbuf;

	double read_size_sum = 0;
	int read_size;
	int division_count=0;
	double start_time=0,elapsed_time;
	double max_bandwidth = 0, tmp_bandwidth;

	sock = tcp_connect(server, portno);
	start_time = get_second();
	rbuf = (char *) malloc(sizeof(char) * buffer_size);
	if (rbuf == NULL) {
		fprintf(stderr, "allocation by malloc haven't succeeded\n");
	}
	while (division_count < ex_count) {
		read_size_sum += (read_size = read(sock, rbuf, buffer_size));
		elapsed_time = get_second() - start_time;
		if ((elapsed_time > division_sec)) {
			tmp_bandwidth = ((double) read_size_sum) / elapsed_time;
			if (tmp_bandwidth > max_bandwidth) {
				max_bandwidth = tmp_bandwidth;
			}
			read_size_sum = 0;
			division_count++;
			start_time = get_second();
		}
	}
	printf("max bandwidth=%10.10f Mbps", max_bandwidth * 8 / (1024.0 * 1024.0));
	close(sock);
}

/* get integer from argv */
int get_count(int index,char **argv){
  return atoi(argv[index]);
}

main( int argc, char *argv[] )
{
  char *server ;
  int portno ;

	if( argc == 1 )
	{
	    fprintf( stdout,"Usage: %s <server_address>  <portnum> <buffer_size> <experiment_count> <time_division>\n",argv[0] );
	    exit( -1 );
	}

   portno = get_count(1,argv);

   server = argv[1] ;
   portno = get_count(2,argv);
   buffer_size = get_count(3,argv);
   ex_count = get_count(4,argv);
   division_sec = get_count(5,argv);

   printf("sever: %s, port: %d, buffer size: %d, ex_count: %d, time_div: %d \n",server,portno,buffer_size,ex_count,division_sec);

  client( server, portno );
}
