#include <stdio.h>
#include <stdlib.h>     /* exit() */
#include <string.h>     /* memset(), memcpy() */
#include <sys/fcntl.h>

#include <cv.h>
#include <highgui.h>
#include <ctype.h>

#include <cxcore.h>	

#define BUFFERSIZE 1024
#define WIDTH 352
#define HEIGHT 288
/* #define WIDTH 640 */
/* #define HEIGHT 480 */
#define FRAME_SIZE (WIDTH*HEIGHT*3)

#define PIPE_CREATER_FIFO_IN_FILE_NAME "/tmp/SensorPipeCreaterStoC"
#define PIPE_CREATER_FIFO_OUT_FILE_NAME "/tmp/SensorPipeCreaterCtoS"
#define INPUT_FIFO_FILE_NAME "/tmp/SensorPipeStoC"
#define OUTPUT_FIFO_FILE_NAME "/tmp/SensorPipeCtoS"

/* int sock; */
char rbuf[BUFFERSIZE];
char frame_buf[FRAME_SIZE];

int pipe_in_fd = NULL,pipe_out_fd = NULL;

/* order server to create new pipe */
/* return value: pipe_number for this process */
char order_new_pipe_to_server(){
  int creater_pipe_fd_in,creater_pipe_fd_out;
  int write_len,write_len_sum=0;
  int read_len,read_len_sum=0;

  if((creater_pipe_fd_in = open(PIPE_CREATER_FIFO_IN_FILE_NAME,O_RDONLY))==-1){
    perror("open input fifo");
    exit(-1);
  }
  if((creater_pipe_fd_out = open(PIPE_CREATER_FIFO_OUT_FILE_NAME,O_WRONLY))==-1){
    perror("open output fifo");
    exit(-1);
  }

  char request_message[] = "please";
  printf("send request for order new pipe\n");
  while(write_len_sum < sizeof(request_message)){
    write_len = write(creater_pipe_fd_out,request_message,sizeof(request_message));
    write_len_sum += write_len;
  }
  printf("reading pipe number for own pipe\n");
  char pipe_id;
  while((read_len_sum += (read_len = read(creater_pipe_fd_in,&pipe_id,1))) < 1){
  }
  printf("pipe_number: %d\n",(int)pipe_id);
  return pipe_id;
}

int init_pipe(int pipe_number){
  char tmp_str[50],num_str[5];

  strcpy(tmp_str,OUTPUT_FIFO_FILE_NAME);
  sprintf(num_str,"%d",pipe_number);
  strcat(tmp_str,num_str);
  if((pipe_out_fd = open(tmp_str,O_WRONLY))==-1){
    perror("open output fifo");
    exit(-1);
  }
  
  sleep(1);

  strcpy(tmp_str,INPUT_FIFO_FILE_NAME);
  sprintf(num_str,"%d",pipe_number);
  strcat(tmp_str,num_str);
  if((pipe_in_fd = open(tmp_str,O_RDONLY))==-1){
    perror("open input fifo");
    exit(-1);
  }
}

void send_request(){
  int write_len,write_len_sum = 0;
  
  printf("send data request\n");
  char request_message[] = "please";
  while(write_len_sum < sizeof(request_message)){
    write_len = write(pipe_out_fd,request_message,sizeof(request_message));
    printf("write %d",write_len);
    write_len_sum += write_len;
  }
}

IplImage *get_frame(){
  int read_size,read_size_sum = 0;
  IplImage *new_frame;

  send_request();
/*   printf("start reading data\n"); */
  while((read_size_sum += (read_size = read(pipe_in_fd,rbuf,BUFFERSIZE))) < FRAME_SIZE){
/*     printf("read_size; %d\n",read_size); */
    if(read_size != -1){
/*       printf("left_size; %d\n",FRAME_SIZE - read_size_sum); */
      memcpy(frame_buf + (read_size_sum - read_size),rbuf,read_size);
    }
/*     printf("sum: %d\n",read_size_sum); */
  }
  new_frame = cvCreateImage( cvSize( WIDTH, HEIGHT ),  IPL_DEPTH_8U, 3);
  memcpy(new_frame->imageData,frame_buf,FRAME_SIZE);
  
  return new_frame;
}

int
main (int argc, char **argv)
{
  IplImage *frame = 0;
  int c;
  int my_pipe_number;

  cvNamedWindow ("ReadDataUsingPipe", CV_WINDOW_AUTOSIZE);
  
  my_pipe_number = order_new_pipe_to_server();
  sleep(1); 			/* wait pipe file creation */
  init_pipe(my_pipe_number);
  printf("finished set up for own pipe\n");
  while (1) {
    frame = get_frame();
    cvShowImage ("ReadDataUsingPipe", frame);
    sleep(1);
    c = cvWaitKey (10);
    if (c == '\x1b')
      break;
  }

  cvDestroyWindow ("Capture");

  return 0;
}
