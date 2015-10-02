/*
 * stdinredir2.c
 *   標準入力をリダイレクトするための２種類の方法を示す
 *   #defineを使ってどちらを使うかを指定する
 */
#include <stdio.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdlib.h>

/* オープン・クローズ・複製・クローズパターン
#define CLOSE_DUP
*/
/* オープン・複製２・クローズパターン
#define USE_DUP2
*/

int main(void)
{
  int fd;
  int newfd;
  char line[100];

  /* 3行読んで出力する */
  fgets(line, 100, stdin); printf("%s", line);
  fgets(line, 100, stdin); printf("%s", line);
  fgets(line, 100, stdin); printf("%s", line);

  /* 入力をリダイレクトする */
  fd = open("data", O_RDONLY);

#ifdef CLOSE_DUP
  close(0);
  newfd = dup(fd);
#else
  newfd = dup2(fd, 0);
#endif

  if (newfd != 0) {
    fprintf(stderr, "Cound not duplicate fd to 0\n");
    exit(1);
  }
  close(fd);

  /* 3行読んで出力する */
  fgets(line, 100, stdin); printf("%s", line);
  fgets(line, 100, stdin); printf("%s", line);
  fgets(line, 100, stdin); printf("%s", line);

  return 0;
}
