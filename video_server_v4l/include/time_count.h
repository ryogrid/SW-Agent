#ifndef _TIME_COUNT_H_

#define _TIME_COUNT_H_

#include <sys/time.h>

typedef struct _timecount{
  struct timeval tv_mem;
  struct timeval tv_now;
  int flag;
  double sec;
  long usec;
} timecount;

void time_checker_init(timecount *tcount);
void time_checker(timecount *tcount);
#endif
