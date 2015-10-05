/*
 * pipedemo.c
 *   目的：パイプの作り方と使い方を示す
 *   効果：パイプを作成し、書き込み側に出力し、読み出し側から読み出す。
 *       少々回りくどいが、パイプがどのようなものかはわかる。
 */
#include <stdio.h>
#include <unistd.h>

#include <stdlib.h>
#include <string.h>

int main()
{
  int len, i, apipe[2];
  char buf[BUFSIZ];

  /* パイプを作成する */
  if (pipe(apipe) == -1) {
    perror("could not make pipe");
    exit(1);
  }

  printf("Got a pipe! It is file descriptors: { %d %d }\n",
    apipe[0], apipe[1]);

  /* 標準入力を読みだし、パイプに書き込み、パイプから読み出して出力する */
  while(fgets(buf, BUFSIZ, stdin)) {
    len = strlen(buf);

    /* パイプに書き込み */
    if (write(apipe[1], buf, len) != len) {
      perror("writing to pipe");
      break;
    }
    /* 消去 */
    for (i = 0; i < len; i++) {
      buf[i] = 'X';
    }
    /* パイプから読み込み */
    len = read(apipe[0], buf, BUFSIZ);
    if (len == -1) {
      perror("reading from pipe");
      break;
    }
    /* 標準出力に送出 */
    if (write(1, buf, len) != len) {
      perror("writing to stdout");
      break;
    }
  }

  return 0;
}
