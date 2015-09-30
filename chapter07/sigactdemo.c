/*
 * sigactdemo.c
 *   目的：sigaction()の使い方を示す
 *   特徴：Ctrl+Cの処理中は、Ctrl+\をブロックする
 *        Ctrl+Cハンドラを設定し直さないので、２度目で終了する
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define INPUTLEN 100

int main(void)
{
  struct sigaction newhandler;
  sigset_t blocked;
  void inthandler(int);
  char x[INPUTLEN];

  newhandler.sa_handler = inthandler;
  newhandler.sa_flags = SA_RESETHAND | SA_RESTART;

  sigemptyset(&blocked);
  sigaddset(&blocked, SIGQUIT);

  newhandler.sa_mask = blocked;

  if (sigaction(SIGINT, &newhandler, NULL) == -1) {
    perror("sigaction");
  } else {
    while(1) {
      fgets(x, INPUTLEN, stdin);
      printf("intput: %s", x);
    }
  }

  return 0;
}

void inthandler(int s)
{
  printf("Called with signal %d\n", s);
  sleep(s);
  printf("done handling signal %d\n", s);
}
