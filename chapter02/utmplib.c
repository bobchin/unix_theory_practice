/*
 * utmplib.c - utmpファイルからの読み出しをバッファリングする関数
 *   含まれる関数は次のとおり
 *     utmp_open(filename) - ファイルをオープンする。エラーのときは-1を返す
 *     utmp_next() - 次の構造体を指すポインタを返す。eofのときにはNULLを返す
 *     utmp_close() - ファイルを閉じる
 *
 *  一度の読み出しでNRECS個の構造体を読みだし、バッファから構造体を１個ずつ提供する
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <utmpx.h>

/*
#define NRECS 16
#define NULLUT ((struct utmp *)NULL)
#define UTSIZE (sizeof(struct utmp))
*/
#define NRECS 16
#define NULLUT ((struct utmpx *)NULL)
#define UTSIZE (sizeof(struct utmpx))

static char utmpbuf[NRECS * UTSIZE];
static int num_recs;
static int cur_rec;
static int fd_utmp = -1;

int utmp_open(char *filename)
{
  fd_utmp = open(filename, O_RDONLY);
  cur_rec = num_recs = 0;
  return fd_utmp;
}

/*
 * バッファに次のレコードのチャンクを読みだす
 */
int utmp_reload()
{
  int amt_read;
  amt_read = read(fd_utmp, utmpbuf, NRECS * UTSIZE);
  num_recs = amt_read / UTSIZE;
  cur_rec = 0;
  return num_recs;
}

/*
struct utmp *utmp_next()
*/
struct utmpx *utmp_next()
{
  struct utmpx *recp;

  if (fd_utmp == -1)
    return NULLUT;

  if (cur_rec == num_recs && utmp_reload() == 0)
    return NULLUT;

  /*
  recp = (struct utmp *) &utmpbuf[cur_rec * UTSIZE];
  */
  recp = (struct utmpx *) &utmpbuf[cur_rec * UTSIZE];
  cur_rec++;
  return recp;
}

void utmp_close()
{
  if (fd_utmp != -1)
    close(fd_utmp);
}
