#include "thread.h"


void Thello(int id) {

  while (1) {

    printf("%c", "_ABCDEFGHIJKLMNOPQRSTUVWXYZ"[id]);
    //根据线程号选择一个属于自己的字母
    //因为操作系统会通过中断程序来切换不同的线程，所以我们会看到输出不同的字母
  }

}


int main() {

  for (int i = 0; i < 10; i++) {

    create(Thello);

  }

}