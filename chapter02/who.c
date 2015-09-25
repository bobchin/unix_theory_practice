#include <stdio.h>
#include <utmpx.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define SHOWHOST

void show_info(struct utmpx *);

int main()
{
  /*
  struct utmp current_record;
  int utmpfd;
  int reclen = sizeof(current_record);

  if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
    perror(UTMP_FILE);
    exit(1);
  }

  while (read(utmpfd, &current_record, reclen) == reclen) {
    show_info(&current_record);
  }
  close(utmpxfd);
  return 0;
  */
  struct utmpx *current_record;

  while ((current_record = getutxent()) != NULL) {
    show_info(current_record);
  }
  endutxent();

  return 0;
}

/*
 * show_info()
 *   utmpx構造体の内容を人間が読めるように表示する
 *   *注意* サイズ情報をハードコードしてはならない
 */
void show_info(struct utmpx *utbufp)
{
  /*
  printf("%-8.8s", utbufp->ut_name);
  printf(" ");
  printf("%-8.8s", utbufp->ut_line);
  printf(" ");
  printf("%10ld", utbufp->ut_time);
  printf(" ");
#ifdef SHOWHOST
  printf("(%s)\n", utbufp->ut_host);
#endif
  printf("\n");
  */
  
  printf("%-8.8s", utbufp->ut_user);
  printf(" ");
  printf("%-8.8s", utbufp->ut_line);
  printf(" ");
  printf("%10ld", utbufp->ut_tv.tv_sec);
  printf(" ");
#ifdef SHOWHOST
  printf("(%s)\n", utbufp->ut_host);
#endif
  printf("\n");
}
