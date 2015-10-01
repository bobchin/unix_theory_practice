/*
 * forkdemo3.c - fork()の戻り値を使って自分が親か子かを判断するには
 *               どうすればよいかを示す
 */
#include <stdio.h>

#include <unistd.h>

int main(void){
  int fork_rv;

  printf("Before: my pid is %d\n", getpid());
  fork_rv = fork();

  if (fork_rv == -1) {
    /* エラー */
    perror("fork");
  } else if (fork_rv == 0) {
    printf("I am the child. my pid = %d\n", getpid());
  } else {
    printf("I am the parent. my child = %d\n", fork_rv);
  }
}
