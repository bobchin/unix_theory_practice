/*
 * waitdemo1.c - 子プロセスが終了するまで親が一時停止する様子を示す
 */
#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>

#define DELAY 2

int main(void)
{
  int newpid;
  void child_code(), parent_code();

  printf("before: my pid is %d\n", getpid());

  if ((newpid = fork()) == -1) {
    perror("fork");
  } else if (newpid == 0) {
    child_code(DELAY);
  } else {
    parent_code(newpid);
  }
}

/*
 * 新プロセスは居眠りをして終了する
 */
void child_code(int delay)
{
  printf("child %d here. will sleep for %d seconds\n", getpid(), delay);
  sleep(delay);
  printf("childe done. about to exit.\n");
  exit(17);
}

/*
 * 親は子が終了するのをまってからメッセージを出力する
 */
void parent_code(int childpid)
{
  int wait_rv;
  wait_rv = wait(NULL);
  printf("done waiting for %d. Wait returned: %d\n", childpid, wait_rv);
}
