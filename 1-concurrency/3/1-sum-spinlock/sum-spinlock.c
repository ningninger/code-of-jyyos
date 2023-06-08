#include "thread.h"


#define N 100000000

#define M 10


long sum = 0;


int xchg(int volatile *ptr, int newval) {

  int result;

  asm volatile(

    "lock xchgl %0, %1"

    : "+m"(*ptr), "=a"(result)

    : "1"(newval)

    : "memory"

  );

  return result;

}


int locked = 0;


void lock() {

  while (xchg(&locked, 1)) ;

}


void unlock() {

  xchg(&locked, 0);

}


void Tsum() {

  long nround = N / M;

  for (int i = 0; i < nround; i++) {

    lock();//进入临界区

    for (int j = 0; j < M; j++) {

      sum++;  // Non-atomic; can optimize

    }

    unlock();

  }

}


int main() {

  assert(N % M == 0);//检查正确性

  //创造两个线程
  create(Tsum);

  create(Tsum);
  //等待线程执行完成
  join();

  printf("sum = %ld\n", sum);

}
