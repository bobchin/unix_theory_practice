/*
 * more.c - moreのバージョン0.1
 * ファイルを読みだして24行出力したら、一時停止して次のコマンドを待つ
 */
#include <stdio.h>
#include <stdlib.h>

#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *);
int  see_moe();

int main(int ac, char *av[])
{
  FILE *fp;

  if (ac == 1) {
    do_more(stdin);
  } else {
    while (--ac) {
      if ((fp = fopen(*++av, "r")) != NULL) {
        do_more(fp);
        fclose(fp);
      } else {
        exit(1);
      }
    }
  }

  return 0;
}

/*
 * PAGELEN行の情報を読み、see_more()を呼び出して命令を待つ
 */
void do_more(FILE *fp)
{
  char line[LINELEN];
  int num_of_lines = 0;
  int see_more(), reply;

  while (fgets(line, LINELEN, fp)) {
    if (num_of_lines == PAGELEN) {
      reply = see_more();
      if (reply == 0)
        break;

      num_of_lines -= reply;
    }

    if (fputs(line, stdout) == EOF)
      exit(1);

    num_of_lines++;
  }
}

/*
 * メッセージを出力して応答を待つ。先にすすめる行数を返す。
 * "q": No, "スペース": Yes, "CR": 1行
 */
int see_more()
{
  int c;

  /* vt100では反転表示 */
  printf("\033[7m more? \033[m");
  while ((c = getchar()) != EOF) {
    if (c == 'q')
      return 0;
    if (c == ' ')
      return PAGELEN;
    if (c == '\n')
      return 1;
  }
  return 0;
}
