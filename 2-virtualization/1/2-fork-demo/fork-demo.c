#include <unistd.h>

#include <stdio.h>

//问：下面的程序会产生多少个? 答：产生4个进程
int main() {

  pid_t x = fork();

  pid_t y = fork();

  printf("%d %d\n", x, y);

}