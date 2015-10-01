/*
 * prompting shell version 2
 *
 *   バージョン１の’ワンショット問題’を解決する
 *   execvp()を使うが、先にfork()を使い、シェルがほかのコマンドを
 *   実行するために子プロセスの終了を待てるようにする
 *
 *   新しい問題：シェルはシグナルをキャッチしてしまう。
 *             viを実行して^Cを押してみよう
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
  void execute(char *[]);

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
 * fork, execvp, waitを使ってコマンドを起動する
 */
void execute(char *arglist[])
{
  int pid, exitstatus;

  pid = fork();
  switch (pid) {
    case -1:
      perror("fork failed");
      exit(1);
    case 0:
      execvp(arglist[0], arglist);
      perror("execvp failed");
      exit(1);
    default:
      while(wait(&exitstatus) != pid)
        ;
      printf("child exited with status %d,%d\n",
        exitstatus >> 8, exitstatus & 0377);
  }
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
