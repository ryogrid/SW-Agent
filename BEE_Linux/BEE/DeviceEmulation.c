#include "inc.h"
#include <linux/videodev.h>

#define VIDEO_DUMMY_FD 1000

int SysCallOpen(const char *pathname, int flags, mode_t mode){
  char usable_device[] = "/dev/video";
  int fd;

  printf("open: %s\n",pathname);
  if(strncmp(pathname,usable_device,10) == 0){
    return VIDEO_DUMMY_FD;
  }else{
    printf("MESSAGE BY EXECUTER: You can't use \"%s\".\n",pathname);
//    printf("BEE; you can only use %s.\n",usable_device);
    printf("MESSAGE BY EXECUTER; You can use \"/dev/sensor\" and \"/dev/client\" only.\n");
    return -1;
  }
}

#define PORT_NUM 1234
#define ASYNC 1
int sock_fd = NULL;
int current_client_fd = NULL;
/* char requestline[BUFFERSIZE]; */
int video_width = -1;
int video_height = -1;

#define BUFFERSIZE 1024

/* #ifdef WEBCAM */
/* #define WIDTH 352 */
/* #define HEIGHT 288 */
/* #else */
/* #define WIDTH 640 */
/* #define HEIGHT 480 */
/* #endif */

#define VIDEO_FRAME_SIZE (video_height*video_width*3)

#define PIPE_CREATER_FIFO_IN_FILE_NAME "/tmp/SensorPipeCreaterStoC"
#define PIPE_CREATER_FIFO_OUT_FILE_NAME "/tmp/SensorPipeCreaterCtoS"
#define INPUT_FIFO_FILE_NAME "/tmp/SensorPipeStoC"
#define OUTPUT_FIFO_FILE_NAME "/tmp/SensorPipeCtoS"

int pipe_in_fd,pipe_out_fd;
char rbuf[BUFFERSIZE];
char *video_buf;

ssize_t SysCallWrite(int fd, const void *buf, size_t count){
  int ret;

  if(fd == -1){
/*     printf("write to virtual device\n"); */
    if(current_client_fd == NULL){
      return 0;
    }else{
//      ret = write(current_client_fd,buf,count);
      ret = send(current_client_fd,buf,count,0);
//    	ret = send(current_client_fd,buf,count,MSG_DONTWAIT | MSG_NOSIGNAL);
//
//      if(ret == -1){
//	switch (errno){
//	case EPIPE:
//	  printf("pipe broken\n");
//	  current_client_fd = NULL;
//	}
//      }
      return ret;
    }
  }else{
/*     printf("write to fd(%d)\n",fd); */
    return write(fd,buf,count);
  }
}

int read_func(int sock){
  int read_size;

/*   read_size = read(sock,requestline,BUFFERSIZE-1); */
/*   requestline[read_size] = '\0'; */
  if ( read_size == 0 || read_size == -1 ){
    printf("disconnected\n");
    current_client_fd = NULL;
    close(sock);
  }
}

int accept_func(int sock){
  tcp_print_peeraddr(sock);
}

int disconnect_func(int sock){
/*   printf("disconnected:\n"); */
/*   tcp_print_peeraddr(sock); */
}

void initSocketService(){
  sock_fd = tcp_bind( PORT_NUM ,ASYNC);
  if( sock_fd < 0 ){
    perror("tcp_bind:");
    exit( -1 );
  }
  tcp_print_host( PORT_NUM );
  /* ignore SIGPIPE which thrown by when a pipe brokes */
/*   signal( SIGPIPE , SIG_IGN ); */
}

void ProcessRequest(){
  int tmp_accept_fd;

  if(sock_fd == NULL){
    initSocketService();
  }
  tmp_accept_fd = tcp_async_accept(accept_func);
  if(tmp_accept_fd != 0){
    current_client_fd = tmp_accept_fd;
  }
  tcp_async_read(read_func);
/*   tcp_async_write(write_func); */
  tcp_async_disconnect(disconnect_func);
/*   printf("process\n"); */
}

/* int init_pipe(){ */
/*   if((pipe_in_fd = open(INPUT_FIFO_FILE_NAME,O_RDONLY))==-1){ */
/*     perror("open input fifo"); */
/*     exit(-1); */
/*   } */
/*   if((pipe_out_fd = open(OUTPUT_FIFO_FILE_NAME,O_WRONLY))==-1){ */
/*     perror("open output fifo"); */
/*     exit(-1); */
/*   } */
/* } */

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

void load_video_size(){
  FILE *config_file;

  config_file = fopen("./video_size.ini","r");
  if(config_file == NULL){
    perror("configuration file not found");
  }

  fscanf(config_file,"%d,%d",&video_width,&video_height);
  if((video_height == -1) || (video_width == -1)){
    printf("format of configuration file is wrong!\n");
  }else{
    printf("loaded video size : %dx%d\n",video_width,video_height);
  }
  fclose(config_file);
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

/*   printf("send request\n"); */
  char request_message[] = "please";
  while(write_len_sum < sizeof(request_message)){
    write_len = write(pipe_out_fd,request_message,sizeof(request_message));
/*     printf("write_len:%d\n",write_len); */
    write_len_sum += write_len;
  }
}

void get_frame(){
  int read_size,read_size_sum = 0;

  send_request();
/*   printf("start reading data\n"); */
  while((read_size_sum += (read_size = read(pipe_in_fd,rbuf,BUFFERSIZE))) < VIDEO_FRAME_SIZE){
/*     printf("read_size; %d\n",read_size); */
    if(read_size != -1){
/*       printf("left_size; %d\n",VIDEO_FRAME_SIZE - read_size_sum); */
      memcpy(video_buf + (read_size_sum - read_size),rbuf,read_size);
    }
/*     printf("sum: %d\n",read_size_sum); */
  }
}

int SysCallIoctl(int d, int request,int arg1, int arg2, int arg3, int arg4){
  int my_pipe_number;

  if((d == -1) && (request == 0xffffff)){
    ProcessRequest();
  }else if(request == VIDIOCMCAPTURE){
/*     printf("emulate VIDIOCMCAPTURE\n"); */
    return 1;
  }else if(request == VIDIOCSYNC){
/*     printf("emulate VIDIOCSYNC\n"); */
    if(pipe_in_fd == NULL){
      load_video_size(); 	/* read video size from configuration file */
      my_pipe_number = order_new_pipe_to_server();
      sleep(1); 			/* wait pipe file creation */
      init_pipe(my_pipe_number);
      video_buf = (char *) malloc(sizeof(char)*VIDEO_FRAME_SIZE);
    }
    get_frame();
    return 1;
  }else if(request == VIDIOCGCAP){
/*     printf("emulate VIDIOCGCAP\n"); */
    return 1;
  }else if(request == VIDIOCSPICT){
/*     printf("emulate VIDIOCSPICT\n"); */
    return 0;
  }else if(request == VIDIOCGMBUF){
    struct video_mbuf dummy_vm;
    struct video_mbuf *passed_vm;

    passed_vm = (struct video_mbuf *)arg1;
    dummy_vm.offsets[0] = 0;
    *passed_vm = dummy_vm;
/*     printf("emulate VIDIOCGMBUF\n"); */
    return 1;
  }else{
    ioctl(d,request,arg1,arg2,arg3,arg4);
  }
}

int SysCallMmap(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
    int ret;
/*     printf("emulate mmap\n"); */
    if(arg5 == VIDEO_DUMMY_FD){
/*       printf("returned internal buffer address\n"); */
      return video_buf;
    }else{
      ret = mmap(arg1,arg2,arg3,arg4,arg5,arg6);
      return ret;
    }
}
