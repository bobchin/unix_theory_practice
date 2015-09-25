/*
 * who3.c - 読み出しでバッファリングを行うwho
 *   - 空レコードが出力されないようにし、時刻を適切に整形する
 *   - 入力をバッファリングする(utmplib.cを使う)
 */
#include <stdio.h>
#include <sys/types.h>
#include <utmpx.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define SHOWHOST

void show_info(struct utmpx *);
void showtime(time_t);

int main()
{
  /*
  struct utmp *utbufp,
              *utmp_next();

  if (utmp_open(UTMP_FILE) == -1) {
    perror(UTMP_FILE);
    exit(1);
  }

  while ((utbufp = utmp_next()) != ((struct utmp *)NULL)) {
    show_info(utbufp);
  }
  utmp_close();
  return 0;
  */
  struct utmpx *utbufp,
               *utmp_next();

  if (utmp_open(UTMPX_FILE) == -1) {
   perror(UTMPX_FILE);
   exit(1);
  }

  while ((utbufp = utmp_next()) != ((struct utmp *)NULL)) {
    show_info(utbufp);
  }
  utmp_close();

  return 0;
}

/*
 * show_info()
 *   utmpx構造体の内容を人間が読めるように表示する
 *   レコードにユーザ名がふくまれていない場合には何も表示しない
 *   *注意* サイズ情報をハードコードしてはならない
 */
/*
void show_info(struct utmp *utbufp)
*/
void show_info(struct utmpx *utbufp)
{
  /*
  if (utbufp->ut_type != USER_PROCESS)
    return;

  printf("%-8.8s", utbufp->ut_name);
  printf(" ");
  printf("%-8.8s", utbufp->ut_line);
  printf(" ");
  showtime(utbufp->ut_time);
#ifdef SHOWHOST
  if (utbufp->ut_host[0] != '\0')
    printf(" (%s)\n", utbufp->ut_host);
#endif
  printf("\n");
  */

  if (utbufp->ut_type != USER_PROCESS)
    return;

  printf("%-8.8s", utbufp->ut_user);
  printf(" ");
  printf("%-8.8s", utbufp->ut_line);
  printf(" ");
  showtime(utbufp->ut_tv.tv_sec);
  printf(" ");
#ifdef SHOWHOST
  if (utbufp->ut_host[0] != '\0')
    printf(" (%s)\n", utbufp->ut_host);
#endif
  printf("\n");
}

/*
 * 人間が理解しやすい形式で時刻を表示する
 * ctimeを使って文字列を組み立ててからその一部を抜き出す。
 * 注意： %12.12sは文字列をchar12個分で出力し、
 * 長さを12バイト以下に制限する。
 */
void showtime(long timeval)
{
  char *cp;
  cp = ctime(&timeval);
  printf("%12.12s", cp + 4); /* 4文字目から12文字抜き出す */
}
