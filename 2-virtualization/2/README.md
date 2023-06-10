内存是什么：内存是带有访问权限控制的连续内存段。
可以通过`mmap`、`munmap`、`mprotect`三个系统调用调整状态机的地址空间，包括分配匿名的内存、映射文件内容到内存、修改访问权限。#include <stdio.h>


int main() {

  extern char **environ;

  for (char **env = environ; *env; env++) {

    printf("%s\n", *env);

  }

}