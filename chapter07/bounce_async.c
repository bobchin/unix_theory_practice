/*
 * bounce_async.c
 *   目的：ユーザ制御のアニメーション、fdに対してO_ASYNCを指定する
 *   注意：set_ticker()はSIGALRMを送り、ハンドラはアニメーションを実現する
 *        キーボードはSIGIOを送り、mainはpause()を呼び出すだけである。
 *   コンパイル：cc bounce_async.c set_ticker.c -lcurses -o bounce_async
 */
#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/* ゲームの状態 */

#define MESSAGE "hello"
#define BLANK   "     "

int row   =  10;
int col   =   0;
int dir   =   1;
int delay = 200;
int done  =   0;

int main(void)
{
  void on_alarm(int);
  void on_input(int);
  void enable_kbd_signals(void);
  extern int set_ticker(int);

  initscr();
  crmode();
  noecho();
  clear();

  signal(SIGIO, on_input);
  enable_kbd_signals();
  signal(SIGALRM, on_alarm);
  set_ticker(delay);

  move(row, col);
  addstr(MESSAGE);

  while(!done) {
    pause();
  }

  endwin();

  return 0;
}

void on_input(int signum)
{
  int c = getch();

  if (c == 'Q' || c == EOF) {
    done = 1;
  } else {
    dir = -dir;
  }
}

void on_alarm(int signum)
{
  signal(SIGALRM, on_alarm);
  mvaddstr(row, col, BLANK);
  col += dir;
  mvaddstr(row, col, MESSAGE);
  refresh();

  if (dir == -1 && col <= 0) {

  } else if (dir == 1 && (col + strlen(MESSAGE)) >= COLS) {
    dir = -1;
  }
}

/*
 * ハンドラを組み込み、入力をどこに通知するかをカーネルに指示し、
 * シグナルを有効にする
 */
void enable_kbd_signals()
{
  int fd_flags;

  fcntl(0, F_SETOWN, getpid());
  fd_flags = fcntl(0, F_GETFL);
  fcntl(0, F_SETFL, (fd_flags|O_ASYNC));
}
