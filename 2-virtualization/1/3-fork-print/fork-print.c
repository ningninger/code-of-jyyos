#include <stdio.h>

#include <unistd.h>

#include <sys/wait.h>

/*
这是一个很有意思的代码，并且也真实地展现了在复制一个进程的时候都做了什么？
直接运行./fork-print  和./fork-print | cat得到的行为不同
但是如果我们将main函数中的注释取消掉，那么我们可以行为又变的相同了
这是因为在进行进程复制的同时，也同时会将缓冲区复制了。
printf不只是直接打印到标准输出的，如果输出连到了一个管道中，那么会将缓冲区复制一份，这样我们就会得到一个不一样的行为。
所以如果我们直接使用系统调用write，就可以直接输出
*/

int main() {

  //setbuf(stdout, NULL);
  int n = 2;

  for (int i = 0; i < n; i++) {

    fork();

    printf("Hello\n");
    //char hello[] = "HELLO\n";
    // write(STDOUT_FILENO, hello, sizeof(hello));

  }

  for (int i = 0; i < n; i++) {

    wait(NULL);

  }

}