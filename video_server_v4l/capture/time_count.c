#include <stdio.h>
#include "time_count.h"

void time_checker_init(timecount *tcount){
  //    fprintf(stderr,"timeChecker init\n");
  gettimeofday( &tcount->tv_mem, NULL);
  tcount->flag = 1;
}

void time_checker(timecount *tcount){

  long u_second = 0;
  long second = 0;

  if(tcount->flag == 1){

    gettimeofday(&tcount->tv_now, NULL);

    second = tcount->tv_now.tv_sec - tcount->tv_mem.tv_sec;
    u_second = tcount->tv_now.tv_usec - tcount->tv_mem.tv_usec;
    
    tcount->sec = (double)second + (double)u_second/1000000;
    tcount->usec = second*1000000 + u_second;

    if(tcount->sec < 0)  tcount->sec = 0;
    if(tcount->usec < 0)  tcount->usec = 0;

    tcount->tv_mem.tv_sec = tcount->tv_now.tv_sec;
    tcount->tv_mem.tv_usec = tcount->tv_now.tv_usec;
  }
  
  return;
}

