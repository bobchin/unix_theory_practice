/*
 * whotofile.c
 *   目的　：ほかのプログラムの出力をリダイレクトするにはどうすればよいかを示す
 *   考え方：forkしてから、子の中で出力をリダイレクトし、最後にexecする
 */
#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
  int pid;
  int fd;

  printf("About to run who into a file\n");

  /* 新プロセスを作成する。失敗したら終了 */
  if ((pid = fork()) == -1) {
    perror("fork");
    exit(1);
  }

  /* 子プロセスの仕事 */
  if (pid == 0) {
    close(1);

    fd = creat("userlist", 644);
    execlp("who", "who", NULL);
    perror("execlp");
    exit(1);
  }

  if (pid != 0) {
    wait(NULL);
    printf("Done running who. results in userlist\n");
  }

  return 0;
}
