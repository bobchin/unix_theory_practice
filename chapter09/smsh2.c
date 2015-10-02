/*
 * smsh2.c - small-shell version 2
 *   コマンド行解析をサポートするsmsh
 *   さらに、if..then..else..fiロジックをサポートする(process()呼び出し)
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "smsh.h"

#define DFL_PROMPT "> "

int main(void)
{
  char *cmdline, *prompt, **arglist;
  int result, process(char **);
  void setup();

  prompt = DFL_PROMPT;
  setup();

  while((cmdline = next_cmd(prompt, stdin)) != NULL) {
    if ((arglist = splitline(cmdline)) != NULL) {
      result = process(arglist);
      freelist(arglist);
    }
    free(cmdline);
  }

  return 0;
}

/*
 * 目的　：シェルの初期化
 * 戻り値：なし。トラブルが起きたらfatal()を呼び出す
 */
void setup()
{
  signal(SIGINT, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);
}

void fatal(char *s1, char *s2, int n)
{
  fprintf(stderr, "Error: %s,%s\n", s1, s2);
  exit(n);
}
