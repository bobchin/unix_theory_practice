/*
 * hello3.c
 *   目的：refreshとsleepを使ってアニメーション効果を与える
 *   概要：初期化・描画・終了
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
    sleep(1);
    refresh();
  }
  endwin();

  return 0;
}
