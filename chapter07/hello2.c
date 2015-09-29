/*
 * hello2.c
 *   目的：ループ内でcurses関数を使うにはどづすればよいかを示す
 *   概要：初期化・描画・終了
 */
#include <stdio.h>
#include <curses.h>

int main(void)
{
  int i;

  initscr();
  clear();
  for (i = 0; i < LINES; i ++) {
    move(i, i + 1);
    if (i % 2 == 1) {
      standout();
    }
    addstr("Hello, World");
    if (i % 2 == 1) {
      standend();
    }
  }

  refresh();
  getch();
  endwin();

  return 0;
}
