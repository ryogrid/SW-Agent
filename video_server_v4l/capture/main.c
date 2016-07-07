#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
	
#include <linux/types.h>
#include <linux/videodev.h>
	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "define.h"
#include "camera.h"
#include <highgui.h> 

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <sys/fcntl.h>

#include <sys/wait.h> 		/* SIGPIPE */

CAM_ATTR *video; // for cap_video
int c_port[CAMERA_NUM];

#define PIPE_CREATER_FIFO_IN_FILE_NAME "/tmp/SensorPipeCreaterCtoS"
#define PIPE_CREATER_FIFO_OUT_FILE_NAME "/tmp/SensorPipeCreaterStoC"
#define INPUT_FIFO_FILE_NAME "/tmp/SensorPipeCtoS"
#define OUTPUT_FIFO_FILE_NAME "/tmp/SensorPipeStoC"

#define TRUE 1
#define FALSE 0

int pipe_creater_in_fd;
int pipe_creater_out_fd;
char buf[1024];

extern  IplImage *imgSrc;

enum videoType vtype;

int video_width = -1;
int video_height = -1;

/* fd_set rfds,wfds; */
int in_pipe_fd_arr[50];
int out_pipe_fd_arr[50];
int all_pipe_count = 0;

extern void sigpipe_handler();

void load_video_size(){
  FILE *config_file;
  char tmp_str[50];
  
  config_file = fopen("./video_type.ini","r");
  if(config_file == NULL){
    perror("configuration file not found");
  }
  
  fscanf(config_file,"%s\n",tmp_str);
  if(strcmp("webcam",tmp_str) == 0){
    vtype = WEBCAM;
    video_height = WEBCAM_HEIGHT;
    video_width = WEBCAM_WIDTH;
    printf("video type is WEBCAM\n");
  }else if(strcmp("ntsc",tmp_str) == 0){
    vtype = NTSC;
    video_height = NTSC_HEIGHT;
    video_width = NTSC_WIDTH;
    printf("video type is NTSC\n");
  }else{
    printf("unkown video type!\n");
  }

  fclose(config_file);
}

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
}

int try_new_pipe(){
  int write_all_len;
  int read_len,write_len;
  int write_len_sum = 0;
  
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

  read_len=read(in_pipe_fd_arr[pipe_index],buf,sizeof(buf)-1);
  if(read_len==0){ /*  need error handling for disconnection by right */
    printf("disconnect\n");
    close(in_pipe_fd_arr[pipe_index]);
    in_pipe_fd_arr[pipe_index] = -1;
    close(out_pipe_fd_arr[pipe_index]);
    out_pipe_fd_arr[pipe_index] = -1;
    return 0;
  }else if(read_len==-1){ /* no input data */
    return 0;
  }else{    
    if(strcmp(buf,"please") == 0){
      while(write_len_sum < FRAME_SIZE){
	write_len = write(out_pipe_fd_arr[pipe_index],(imgSrc->imageData) + write_len_sum,FRAME_SIZE - write_len_sum);
	write_len_sum += write_len;
      }
      return 1;
    }else{
      printf("received unkown message!\n");
      printf("read message: %s\n",buf);
      return 0;
    }
  }
}

/* return value:                                                  */
/*        n => count of request served, 0 => there was no request */
int try_serving_to_all_pipes(){
  int i;
  int process_count=0;

  /* try serving to all pipes */
  for(i=0;i< all_pipe_count;i++){
    if(in_pipe_fd_arr[i] != -1){
      process_count += try_serving(i);
    }
  }
  return process_count;
}

int main(int argc, char **argv)
{
  int status;
  int i;
  int served_count;
  CAM_ATTR camAttr[CAMERA_NUM];
  
  video = camAttr;
  
  load_video_size();
  init_video();
  init_pipe_creater();
  while(1){
    process_a_frame();
    try_new_pipe();
    served_count = try_serving_to_all_pipes();
  }
  finilize_video();
  
  return 0;
}
