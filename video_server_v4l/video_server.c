#include <cv.h>
#include <highgui.h>
#include <ctype.h>

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <sys/fcntl.h>

#include <sys/wait.h> 		/* SIGPIPE */

#define PIPE_CREATER_FIFO_IN_FILE_NAME "/tmp/SensorPipeCreaterCtoS"
#define PIPE_CREATER_FIFO_OUT_FILE_NAME "/tmp/SensorPipeCreaterStoC"
#define INPUT_FIFO_FILE_NAME "/tmp/SensorPipeCtoS"
#define OUTPUT_FIFO_FILE_NAME "/tmp/SensorPipeStoC"

#define WIDTH 352
#define HEIGHT 288
#define FRAME_SIZE (WIDTH*HEIGHT*3)

#define TRUE 1
#define FALSE 0

int pipe_creater_in_fd;
int pipe_creater_out_fd;
char buf[1024];
IplImage *frame = 0;

/* fd_set rfds,wfds; */
int in_pipe_fd_arr[50];
int out_pipe_fd_arr[50];
int all_pipe_count = 0;

extern void sigpipe_handler();

int init_pipe_creater(){
  char rm_command_str[50] = "rm -f ";
  char num_str[5];
  strcat(rm_command_str,PIPE_CREATER_FIFO_IN_FILE_NAME);
  system(rm_command_str);
  strcpy(rm_command_str,"rm -f ");
  strcat(rm_command_str,PIPE_CREATER_FIFO_OUT_FILE_NAME);
  system(rm_command_str);

  if(mkfifo(PIPE_CREATER_FIFO_IN_FILE_NAME,0666)==-1){
    perror("mkfifo to create pipe for pipe creater input");
    exit(-1);
  }
  if((pipe_creater_in_fd = open(PIPE_CREATER_FIFO_IN_FILE_NAME,O_RDONLY | O_NONBLOCK))==-1){
    perror("open input fifo for pipe creater");
    exit(-1);
  }
  if(mkfifo(PIPE_CREATER_FIFO_OUT_FILE_NAME,0666)==-1){
    perror("mkfifo to create pipe for pipe creater output");
    exit(-1);
  }
  if((pipe_creater_out_fd = open(PIPE_CREATER_FIFO_OUT_FILE_NAME,O_WRONLY))==-1){
    perror("open output fifo for pipe creater");
    exit(-1);
  }

  signal(SIGPIPE,sigpipe_handler);
}

int new_pipe(int num){
  /* remove pipe files which has same name */
  char rm_command_str[50] = "rm -f ";
  char num_str[5];
  int write_len,write_len_sum = 0;
  char num_tmp = num;
  /* send pipe number which will be created */
  while(write_len_sum < 1){
    write_len = write(pipe_creater_out_fd,&num_tmp,1);
    write_len_sum += write_len;
  }  

  sprintf(num_str,"%d",num);
  strcat(rm_command_str,INPUT_FIFO_FILE_NAME);
  strcat(rm_command_str,num_str);
  system(rm_command_str);

  strcpy(rm_command_str,"rm -f ");
  strcat(rm_command_str,OUTPUT_FIFO_FILE_NAME);
  strcat(rm_command_str,num_str);
  system(rm_command_str);

  /* setup FIFOs and open them */    
  char tmp_str[50];
  strcpy(tmp_str,INPUT_FIFO_FILE_NAME);
  strcat(tmp_str,num_str);
  if(mkfifo(tmp_str,0666)==-1){
    perror("mkfifo to create input fifo");
    exit(-1);
  }
  if((in_pipe_fd_arr[num] = open(tmp_str,O_RDONLY | O_NONBLOCK))==-1){
/*   if((in_pipe_fd_arr[num] = open(tmp_str,O_RDONLY))==-1){ */
    perror("open input fifo");
    exit(-1);
  }

  strcpy(tmp_str,OUTPUT_FIFO_FILE_NAME);
  strcat(tmp_str,num_str);
  if(mkfifo(tmp_str,0666)==-1){
    perror("mkfifo to create output fifo");
    exit(-1);
  }
  if((out_pipe_fd_arr[num] = open(tmp_str,O_WRONLY))==-1){
    perror("open output fifo");
    exit(-1);
  }
  
/*   FD_SET(in_pipe_fd_arr[0], &rfds); */
/*   FD_SET(out_pipe_fd_arr[0], &wfds); */
}

int try_new_pipe(){
  int write_all_len;
  int read_len,write_len;
  int write_len_sum = 0;
  
/*   printf("try serving %d\n",rand()); */
  read_len=read(pipe_creater_in_fd,buf,sizeof(buf)-1);
  if(read_len==0){ /*  need error handling for disconnection by right */
    return 0;
  }else if(read_len==-1){ /* no input data */
    return 0;
  }else{    
    if(strncmp(buf,"please",6) == 0){
      new_pipe(all_pipe_count);
      all_pipe_count++;
      return 1;
    }else{
      printf("received unkown message!\n");
      printf("read message: %s\n",buf);
      return 0;
    }
  }  
}

void sigpipe_handler(){
/*   close(pipe_in_fd); */
/*   close(pipe_out_fd); */
/*   init_pipe(FALSE); */
}

int try_serving(int pipe_index){
  int read_len,write_len;
  int write_len_sum = 0;

/*   printf("try reading data request for pipe%d\n",pipe_index); */
/*   printf("fd: %d\n",in_pipe_fd_arr[pipe_index]); */
  read_len=read(in_pipe_fd_arr[pipe_index],buf,sizeof(buf)-1);
/*   printf("read len : %d\n",read_len); */
  if(read_len==0){ /*  need error handling for disconnection by right */
    printf("disconnect\n");
    close(in_pipe_fd_arr[pipe_index]);
    in_pipe_fd_arr[pipe_index] = -1;
    close(out_pipe_fd_arr[pipe_index]);
    out_pipe_fd_arr[pipe_index] = -1;
    return 0;
  }else if(read_len==-1){ /* no input data */
/*     perror("read error:"); */
    return 0;
  }else{    
/*     printf("read: %s\n",buf); */
    if(strcmp(buf,"please") == 0){
      /*       printf("start sending data\n"); */
      while(write_len_sum < FRAME_SIZE){
	write_len = write(out_pipe_fd_arr[pipe_index],(frame->imageData) + write_len_sum,FRAME_SIZE - write_len_sum);
	write_len_sum += write_len;
	/* 	printf("write_len_sum: %d\n",write_len_sum); */
      }
      return 1;
    }else{
      printf("received unkown message!\n");
      printf("read message: %s\n",buf);
      return 0;
    }
  }
}

/* return value:                  */
/*        n => count of request served, 0 => there was no request */
int try_serving_to_all_pipes(){
  int i;
  int process_count=0;

/*   printf("try serving %d\n",rand()); */
  /* try serving to all pipes */
  for(i=0;i< all_pipe_count;i++){
    if(in_pipe_fd_arr[i] != -1){
      process_count += try_serving(i);
    }
  }
  return process_count;
}

int
main (int argc, char **argv)
{
  CvCapture *capture = 0;
  double w = 320, h = 240;
  int c;
  int served_count;

  if (argc == 1 || (argc == 2 && strlen (argv[1]) == 1 && isdigit (argv[1][0])))
    capture = cvCreateCameraCapture (argc == 2 ? argv[1][0] - '0' : 0);

  cvSetCaptureProperty (capture, CV_CAP_PROP_FRAME_WIDTH, WIDTH);
  cvSetCaptureProperty (capture, CV_CAP_PROP_FRAME_HEIGHT, HEIGHT);

/*   cvNamedWindow ("Capture", CV_WINDOW_AUTOSIZE); */

/*   FD_ZERO( &rfds ); */
/*   FD_ZERO( &wfds ); */

  init_pipe_creater();
  while (1) {
    frame = cvQueryFrame (capture);
    try_new_pipe();
    served_count = try_serving_to_all_pipes();
/*     if(served_count != 0){ */
/*       printf("served %d requests\n",served_count); */
/*     } */
/*     cvShowImage ("Capture", frame); */
/*     c = cvWaitKey (10); */
/*     if (c == '\x1b') */
/*       break; */
  }

  cvReleaseCapture (&capture);
  cvDestroyWindow ("Capture");

  return 0;
}
