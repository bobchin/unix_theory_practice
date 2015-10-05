/*
 * pipedemo2.c
 *   目的：fork()呼び出しによってパイプアクセスが重複する様子を示す
 *       親はパイプを読み書きし続けるが、子もパイプに書き込む
 */
#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define CHILD_MESS "I want a cookie\n"
#define PAR_MESS   "tesing..\n"
#define oops(m,x)  { perror(m); exit(x); }

int main(void)
{
  int pipefd[2];
  int len;
  char buf[BUFSIZ];
  int read_len;

  if (pipe(pipefd) == -1) {
    oops("cannot get a pipe", 1);
  }

  switch (fork()) {
    case -1:
      oops("cannot get a pipe", 2);

    /* 子は５秒ごとにパイプに書き込みをする */
    case 0:
      len = strlen(CHILD_MESS);
      while(1) {
        if (write(pipefd[1], CHILD_MESS, len) != len) {
          oops("write", 3);
        }
        sleep(5);
      }

    /* 親はパイプを読みだし、パイプへの書き込みも行う */
    default:
      len = strlen(PAR_MESS);
      while(1) {
        if (write(pipefd[1], PAR_MESS, len) != len) {
          oops("write", 4);
        }
        sleep(1);
        read_len = read(pipefd[0], buf, BUFSIZ);
        if (read_len <= 0) {
          break;
        }
        write(1, buf, read_len);
      }
  }

  return 0;
}
