#include "thread.h"


//但是能很明显地感觉到这部分的代码的运行时间被加长了

#define N 100000000


long sum = 0;


void atomic_inc(long *ptr) {

  asm volatile(

    "lock incq %0"  // Atomic + memory fence

    : "+m"(*ptr)

    :

    : "memory"

  );

}


void Tsum() {

  for (int i = 0; i < N; i++) {

    atomic_inc(&sum);//load 和 store不再会被打断， 看到的和写上去保持了一致

  }

}


int main() {

  create(Tsum);

  create(Tsum);

  join();

  printf("sum = %ld\n", sum);

}