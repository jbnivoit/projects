#include "FlickrClientImpl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

  char c[16]="0123456789ABCDEF";
  char s[33];

  memset(s,0,sizeof(s));
  
  hex(c,s);
  printf("%s\n",s);

 return EXIT_SUCCESS;
}
