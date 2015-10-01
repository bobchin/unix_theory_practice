/*
 * prompting shell version 1
 *   コマンドと引数の入力を促す
 *   execvp呼び出しのために引数配列を作る
 *   execvp()を使い、制御を返さない
 */
#include <stdio.h>
#include <signal.h>
#include <string.h>

#include <unistd.h>
#include <stdlib.h>

#define MAXARGS 20
#define ARGLEN 100

int main(void)
{
  char *arglist[MAXARGS + 1];
  int numargs;
  char argbuf[ARGLEN];
  char *makestring();
  int execute(char *[]);

  numargs = 0;
  while (numargs < MAXARGS) {
    printf("Arg[%d]? ", numargs);
    if (fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n') {
      arglist[numargs++] = makestring(argbuf);
    } else {
      if (numargs > 0) {
        arglist[numargs] = NULL;
        execute(arglist);
        numargs = 0;
      }
    }
  }

  return 0;
}

/*
 * execvpを使ってコマンドを起動する
 */
int execute(char *arglist[])
{
  execvp(arglist[0], arglist);
  perror("execvp fialed");
  exit(1);
}

/*
 * 改行を取り除き、文字列の記憶領域を作る
 */
char *makestring(char *buf)
{
  char *cp;

  buf[strlen(buf) - 1] = '\0';
  cp = malloc(strlen(buf) + 1);
  if (cp == NULL) {
    fprintf(stderr, "no memory\n");
    exit(1);
  }
  strcpy(cp, buf);
  return cp;
}
