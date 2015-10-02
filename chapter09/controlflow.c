/*
 * controlflow.c
 *
 *   "if" 処理は、if_stateとif_resultの２個の状態変数を使って行う
 */
#include <stdio.h>
#include "smsh.h"

#include <string.h>

enum states  { NEUTRAL, WANT_THEN, THEN_BLOCK };
enum results { SUCCESS, FAIL };

static int if_state  = NEUTRAL;
static int if_result = SUCCESS;
static int last_stat = 0;

int syn_err(char *);

/*
 * 目的　：シェルがコマンドを実行すべきかどうかを判断する
 * 戻り値：イエスなら1,ノーなら0
 * 詳細　：THEN_BLOCK内にいて、if_resultがSUCCESSならイエス
 * 　　　　THEN_BLOCK内にいて、if_resultがFAILならノー
 *　　　　　WANT_THENなら構文エラー（shは異なる）
 */
int ok_to_execute()
{
  int rv = 1;

  if (if_state == WANT_THEN) {
    syn_err("then expected");
    rv = 0;
  } else if (if_state == THEN_BLOCK && if_result == SUCCESS) {
    rv = 1;
  } else if (if_state == THEN_BLOCK && if_result == FAIL) {
    rv = 0;
  }

  return rv;
}

/*
 * 目的　：コマンドがシェル制御コマンドかどうかを報告するboot関数
 * 戻り値：0or1
 */
int is_control_command(char *s)
{
  return strcmp(s, "if") == 0
    || strcmp(s, "then") == 0
    || strcmp(s, "fi") == 0;
}

/*
 * 目的　："if", "then", "fi"を処理する-状態を変更するかエラーを検出する
 * 戻り値：OKなら1、構文エラーなら-1
 * メモ　：I would have put returns all over the place, Barry says "no"
 */
int do_control_command(char **args)
{
  char *cmd = args[0];
  int rv = -1;

  if (strcmp(cmd, "if") == 0) {
    if (if_state != NEUTRAL) {
      rv = syn_err("if unexpected");
    } else {
      last_stat = process(args + 1);
      if_result = ((last_stat == 0)? SUCCESS: FAIL);
      if_state = WANT_THEN;
      rv = 0;
    }

  } else if (strcmp(cmd, "then") == 0) {
    if (if_state != WANT_THEN) {
      rv = syn_err("then unexpected");
    } else {
      if_state = THEN_BLOCK;
      rv = 0;
    }

  } else if (strcmp(cmd, "fi") == 0) {
    if (if_state != THEN_BLOCK) {
      rv = syn_err("fi unexpected");
    } else {
      if_state = NEUTRAL;
      rv = 0;
    }

  } else {
    fatal("internal error processing:", cmd, 2);
  }

  return rv;
}

/*
 * 目的　：制御構造内の構文エラーを処理する
 * 詳細　：状態をNEUTRALにリセットする
 * 戻り値：対話的モードなら-1、スクリプト内ではfatal呼び出しになる
 */
int syn_err(char *msg)
{
  if_state = NEUTRAL;
  fprintf(stderr, "syntax error: %s\n", msg);
  return -1;
}
