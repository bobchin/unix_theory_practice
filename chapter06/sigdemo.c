/*
 * sigdemo1.c
 *   - シグナルハンドラの仕組みを示す
 *   - このプログラムを実行してからCTRL+Cを数回押してみよう
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void)
{
  void f(int);
  int i;

  signal(SIGINT, f);
  for (i = 0; i < 5; i++) {
    printf("Hello\n");
    sleep(1);
  }

  return 0;
}

void f(int signum)
{
  printf("OUCH!\n");
}
