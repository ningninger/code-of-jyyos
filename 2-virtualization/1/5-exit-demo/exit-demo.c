#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include <unistd.h>

#include <sys/syscall.h>


void func() {

  printf("Goodbye, Cruel OS World!\n");

}


int main(int argc, char *argv[]) {

  atexit(func);//会注册一个回调函数，这个回调函数会在我们退出的时候进行调用


  if (argc < 2) {

    return EXIT_FAILURE;

  }


  if (strcmp(argv[1], "exit") == 0) {
    //会打印
    exit(0);

  }

  if (strcmp(argv[1], "_exit") == 0) {
    //不会打印，就是不会调用回调函数，比较暴力，直接将状态机从程序中抹除掉，会删除所有线程
    _exit(0);

  }

  if (strcmp(argv[1], "__exit") == 0) {
    //不会打印，就是不会调用回调函数，只会删除当前线程
    syscall(SYS_exit, 0);

  }

}