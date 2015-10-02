/*
 * listargs.c
 *   コマンド行引数の個数を出力し、引数リストを表示して、
 *   最後に標準エラー出力にメッセージを表示する
 */
#include <stdio.h>

int main(int ac, char *av[])
{
  int i;

  printf("Number of args: %d, Args are:\n", ac);
  for (i = 0; i < ac; i++) {
    printf("args[%d] %s\n", i, av[i]);
  }

  fprintf(stderr, "This message is sent to stderr.\n");

  return 0;
}
