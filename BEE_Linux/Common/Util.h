#ifndef UTIL_H_
#define UTIL_H_

void *mAlloc(unsigned int size);
void *reAlloc(void *ptr, unsigned int size);

char *endWith(char *str, char c);

#endif /*UTIL_H_*/
