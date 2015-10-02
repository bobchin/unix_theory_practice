/*
 * 目的　　：ファイルディスクリプタ０を端末からファイルとの接続に置き換えて、
 *         標準入力をリダイレクトする方法を示す。
 * 操作内容：標準入力の３行分のデータを読み出してからfd0をクローズし、
 *         ディスクファイルをオープンしてから、さらに標準入力を3行読み出す
 */
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
  int fd;
  char line[100];

  /* 3行読んで出力する */
  fgets(line, 100, stdin); printf("%s", line);
  fgets(line, 100, stdin); printf("%s", line);
  fgets(line, 100, stdin); printf("%s", line);

  /* 入力をリダイレクトする */
  close(0);
  fd = open("/etc/passwd", O_RDONLY);
  if (fd != 0) {
    fprintf(stderr, "Cound not open data as fd 0\n");
    exit(1);
  }

  /* 3行読んで出力する */
  fgets(line, 100, stdin); printf("%s", line);
  fgets(line, 100, stdin); printf("%s", line);
  fgets(line, 100, stdin); printf("%s", line);

  return 0;
}
