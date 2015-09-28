/*
 * spwd.c: pwdを単純化したバージョン
 *
 * カレントディレクトリからスタートして再帰的にファイルシステムの
 * ルートまで上り、上のディレクトリから順に名前を出力する
 * readdir()を使って個々のディレクトリについての情報を得る
 *
 *   バグ："/" から実行すると空文字列を出力する
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

ino_t get_inode(char *);
void printpathto(ino_t);
void inum_to_name(ino_t, char *, int);

int main()
{
  printpathto(get_inode("."));
  putchar('\n');
  return 0;
}

/*
 * this_inodeに対応するディレクトリまでのパスを出力する再帰関数
 */
void printpathto(ino_t this_inode)
{
  ino_t my_inode;
  char its_name[BUFSIZ];

  if (get_inode("..") != this_inode)
  {
    chdir("..");
    inum_to_name(this_inode, its_name, BUFSIZ);

    my_inode = get_inode(".");
    printpathto(my_inode);
    printf("/%s", its_name);
  }
}

/*
 * カレントディレクトリから引数のiノード番号を持つファイル（サブディレクトリ）を
 * 探し、名前をnamebufにコピーする
 */
void inum_to_name(ino_t inode_to_find, char *namebuf, int buflen)
{
  DIR *dir_ptr;
  struct dirent *direntp;

  dir_ptr = opendir(".");
  if (dir_ptr == NULL) {
    perror(".");
    exit(1);
  }

  while ((direntp = readdir(dir_ptr)) != NULL) {
    if (direntp->d_ino == inode_to_find) {
      strncpy(namebuf, direntp->d_name, buflen);
      namebuf[buflen - 1] = '\0';
      closedir(dir_ptr);
      return;
    }
  }
  fprintf(stderr, "error looking for inum %llu\n", inode_to_find);
  exit(1);
}

/*
 * ファイルのiノード番号を返す
 */
ino_t get_inode(char *fname)
{
  struct stat info;

  if (stat(fname, &info) == -1) {
    fprintf(stderr, "Cannot stat ");
    perror(fname);
    exit(1);
  }

  return info.st_ino;
}











/**/
