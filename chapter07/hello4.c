/*
 * hello4.c
 *   目的：アニメーションのために消去・時間・描画を使う方法を示す
 */
#include <stdio.h>
#include <curses.h>
#include <unistd.h>

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
    refresh();
    sleep(1);
    move(i, i + 1);
    addstr("            ");
  }
  endwin();

  return 0;
}
