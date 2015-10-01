/*
 * exec1.c - プログラムが別のプログラムを起動するのがいかに簡単かを示す
 */
#include <stdio.h>
#include <unistd.h>

int main(void)
{
  char *arglist[3];

  arglist[0] = "ls";
  arglist[1] = "-l";
  arglist[2] = 0;

  printf("* * * Abount to exec ls -l\n");
  execvp("ls", arglist);
  printf("* * * ls is done. bye\n");
}
