/* -*- C -*- */
#include <stdlib.h>
#include <stdio.h>

#include "String.h"

static void print(String *sb) {
  printf("'%s'\n", String_GetString(sb));
}

int main(int argc, char **argv) {
  int i=0;
  String sb;
  String_Init(&sb);

  String_Append(&sb,"test",4);
  print(&sb);
  String_Reinit(&sb);

  for(;i<30;i++) {
    String_Append(&sb,"toto titi tutu",15);
    print(&sb);
  }
  String_Destroy(&sb);

  {
    String sb1,sb2,sb3,sb4,sb5,sb6,sb7,sb8;

    String_InitWithString(&sb1,"test",4);
    String_InitWithString(&sb2,"test ",5);
    String_InitWithString(&sb3,"test\t",5);
    String_InitWithString(&sb4,"test\n",5);
    String_InitWithString(&sb5,"test\n\t ",7);
    String_InitWithString(&sb6,"test\nx\t ",8);
    String_InitWithString(&sb7,"   \t \ntest",10);
    String_InitWithString(&sb8,"   \t \ntest \t",12);
    
    String_RTrimWhitespace(&sb1);
    String_RTrimWhitespace(&sb2);
    String_RTrimWhitespace(&sb3);
    String_RTrimWhitespace(&sb4);
    String_RTrimWhitespace(&sb5);
    String_RTrimWhitespace(&sb6);
    String_LTrimWhitespace(&sb7);

    print(&sb1);
    print(&sb2);
    print(&sb3);
    print(&sb4);
    print(&sb5);
    print(&sb6);
    print(&sb7);

    printf("==========\n");
    print(&sb8);
    String_TrimWhitespace(&sb8);
    print(&sb8);
  }

  return EXIT_SUCCESS;
}
