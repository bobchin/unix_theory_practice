/*
 * spliteline.c - smshのためにコマンドを読んで解析する関数
 *
 *   char *next_cmd(char *prompt, FILE *fp) - 次のコマンドを取得する
 *   char **spliteline(char *str)           - 文字列を解析する
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "smsh.h"

/*
 * 目的　：fpから次のコマンドを行を読み出す
 * 戻り値：コマンド行を保持する動的に確保した文字列
 * エラー：EOFならNULL（本当はエラーではない）
 *       emalloc()からfatalを呼び出す
 * メモ　：BUFSIZ単位でメモリを確保する
 */
char *next_cmd(char *prompt, FILE *fp)
{
  char *buf;
  int bufspace = 0;
  int pos = 0;
  int c;

  printf("%s", prompt);
  while((c = getc(fp)) != EOF) {
    if (pos + 1 >= bufspace) {
      if (bufspace == 0) {
        buf = emalloc(BUFSIZ);
      } else {
        buf = erealloc(buf, bufspace + BUFSIZ);
      }
      bufspace += BUFSIZ;
    }

    if (c == '\n') {
      break;
    }

    buf[pos++] = c;
  }

  if (c == EOF && pos == 0) {
    return NULL;
  }

  buf[pos] = '\0';
  return buf;
}

/*
 * spliteline（行を解析して文字列配列に分割する）
 */
#define is_delim(x) ((x)==' '||(x)=='\t')

/*
 * 目的　：行を空白区切りのトークンに分割する
 * 戻り値：トークンのコピーを指す末尾がNULLのポインタ配列
 *       行にトークンが含まれていない場合はNULL
 * 動作　：配列を順にチェックし、文字列を探してコピーを作る
 * メモ　：strtok()を使えば簡単だが、あとでクォートに対応する
 *       つもりなのでstrtok()は使わない
 */
char **splitline(char *line)
{
  char *newstr();
  char **args;
  int spots = 0;
  int bufspace = 0;
  int argnum = 0;
  char *cp = line;
  char *start;
  int len;

  if (line == NULL) {
    return NULL;
  }

  args = emalloc(BUFSIZ);
  bufspace = BUFSIZ;
  spots = BUFSIZ / sizeof(char *);

  while(*cp != '\0') {
    while(is_delim(*cp)) {
      cp++;
    }
    if (*cp == '\0') {
      break;
    }
    if (argnum + 1 >= spots) {
      args = erealloc(args, bufspace + BUFSIZ);
      bufspace += BUFSIZ;
      spots += (BUFSIZ / sizeof(char *));
    }

    start = cp;
    len = 1;
    while(*++cp != '\0' && !(is_delim(*cp))) {
      len++;
    }
    args[argnum++] = newstr(start, len);
  }

  args[argnum] = NULL;
  return args;
}

/*
 * 目的　：文字列のコンストラクタ
 * 戻り値：文字列、NLにはならない
 */
char *newstr(char *s, int l)
{
  char *rv = emalloc(l + 1);

  rv[l] = '\0';
  strncpy(rv, s, l);
  return rv;
}

/*
 * 目的　：splitlineが返したリストを解放する
 * 戻り値：なし
 * 動作　：リスト内のすべての文字列を開放してリストを解放する
 */
void freelist(char **list)
{
  char **cp = list;
  while(*cp) {
    free(*cp++);
  }
  free(list);
}

void *emalloc(size_t n)
{
  void *rv;
  if ((rv = malloc(n)) == NULL) {
    fatal("out of memory", "", 1);
  }
  return rv;
}

void *erealloc(void *p, size_t n)
{
  void *rv;
  if ((rv = realloc(p, n)) == NULL) {
    fatal("realloc() failed", "", 1);
  }
  return rv;
}
