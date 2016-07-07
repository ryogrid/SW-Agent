#include "stdsoap2.h"
#include <sys/wait.h>           /* SIGPIPE */

#define msec *(-1000);
#define PORT_NUM 1024
#define DUMMY 0xffffff

/* #include "diff_and_countH.h" */
/* #include "diff_count.nsmap" */

void *process_request(void*);

/* dummy */
int pthread_key_create(pthread_key_t *key, void (*destr_function) (void *)){
    return 1;
}

int try_serve_once(struct soap *soap){
  int s;

  s = soap_accept(soap);
  if (s < 0){
    if (soap->errnum){
      soap_print_fault(soap, stderr);
      return -1;
    }else{
      return 1;
    }
  }else{
//    fprintf(stderr, "accepted %d IP=%d.%d.%d.%d ... \n",s, (int)(soap->ip>>24)&0xFF, (int)(soap->ip>>16)&0xFF, (int)(soap->ip>>8)&0xFF, (int)soap->ip&0xFF);
    soap_serve(soap);	// process RPC skeletons
//    fprintf(stderr, "served\n");
    soap_destroy(soap);
    soap_end(soap);	// clean up
    return 1;
  }
}

void sock_finalize(struct soap *soap){
  soap_done(soap);
}

extern void *dime_read_open(struct soap *soap, void *handle, const char *id, const char *type, const char *options);
extern void dime_read_close(struct soap *soap, void *handle);
extern size_t dime_read(struct soap *soap, void *handle, char *buf, size_t len);

extern void sigpipe_handler();

extern int do_using_stream_interface;

void sigpipe_handler(){
}

int main(int argc, char **argv){
  int ret;
  struct soap soap;
  int m;

  /* --------------initialization of soap----------------*/
  /* this procesure can't write on a function due to gsoap's constraint */

/*   soap_init(&soap); */

  // use HTTP chunking when possible
  // chunking allows streaming of DIME content without requiring DIME attachment size to be set
  // DIME attachments can be streamed without chunking only if the attachment size is set
  soap_init1(&soap, SOAP_IO_KEEPALIVE | SOAP_IO_CHUNK | SOAP_ENC_MTOM);

  // for DIME streaming
  soap.fdimereadopen = dime_read_open;
  soap.fdimereadclose = dime_read_close;
  soap.fdimeread = dime_read;

  // for MTOM streaming
  soap.fmimereadopen = dime_read_open;
  soap.fmimereadclose = dime_read_close;
  soap.fmimeread = dime_read;

  soap.accept_timeout = 1.0 msec;
  m = soap_bind(&soap, NULL,PORT_NUM,1000);
  if (m < 0)
    { soap_print_fault(&soap, stderr);
      exit(1);
    }
  /* ----------------------------------------------------*/
  signal(SIGPIPE,sigpipe_handler);
/*   init_video(); */
  while(1){
   if(do_using_stream_interface){
	   /*     /\* call procedure which tries to handle connection request on BEE *\/ */
	   ioctl(-1,DUMMY);
   }
    process_a_frame();
    if(do_using_stream_interface){
       data_write();
    }
    ret = try_serve_once(&soap);
    if(ret < 0){
      break;
    }
  }
  sock_finalize(&soap);
  finilize_video();
}
