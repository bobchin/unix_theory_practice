/*
 * pipe.c
 *   目的　：１つのプロセスから別のプロセスにデータを流す
 *         パイプラインの作り方を示す。引数として２つのコマンドを取り、
 *         av[1]の出力をav[2]の入力に接続する
 *   使い方：pipe command1 command2
 *   効果　：command1 | command2
 *   制限　：コマンドは引数を取ることができない
 *   引数の個数がわかっているのでexeclp()を使う
 *   注意　：子と親を取り替えると面白いことになる
 */
#include <stdio.h>
#include <unistd.h>

#include <stdlib.h>

#define oops(m,x) { perror(m); exit(x); }

int main(int ac, char **av)
{
  int thepipe[2], /* ２つのファイルディスクリプタ */
      pid;        /* プロセスID */

  if (ac != 3) {
    fprintf(stderr, "usage: pipe cmd1 cmd2\n");
    exit(1);
  }

  /* パイプを取得 */
  if (pipe(thepipe) == -1) {
    oops("Cannot get a pipe", 1);
  }

  /* パイプを作ったのでプロセスを２つにする */
  if ((pid = fork()) == -1) {
    oops("Cannot fork", 2);
  }

  /* この時点でプロセスは２個ある。親はパイプから読み出す */
  if (pid > 0) {
    /* 親はパイプに書き込まない */
    close(thepipe[1]);

    /* 標準入力のコピーを作ってパイプを閉じる */
    if (dup2(thepipe[0], 0) == -1) {
      oops("could not redirect stdin", 3);
    }
    close(thepipe[0]);

    execlp(av[2], av[2], NULL);
    oops(av[2], 4);
  }

  /* 子はav[1]を実行し、パイプに書き込む */
  close(thepipe[0]);

  if (dup2(thepipe[1], 1) == -1) {
    oops("could not redirect stdout", 4);
  }
  close(thepipe[1]);

  execlp(av[1], av[2], NULL);
  oops(av[1], 5);
}
