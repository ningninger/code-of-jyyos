#include "thread.h"

#include "thread-sync.h"


#define T 4

#define N 10000000


sem_t done;

long sum = 0;


void atomic_inc(long *ptr) {

  asm volatile(

    "lock incq %0"

    : "+m"(*ptr) : : "memory"

  );

}


void Tsum() {

  for (int i = 0; i < N; i++) {

    atomic_inc(&sum);

  }

  V(&done);

}


void Tprint() {

  //当前面的done完成了以后，我们就可以进行打印了
  //所以当生产者消费者的数量不对等的时候，使用信号量也是一个比较好的方法
  for (int i = 0; i < T; i++) {

    P(&done);

  }

  printf("sum = %ld\n", sum);

}


int main() {

  SEM_INIT(&done, 0);

  for (int i = 0; i < T; i++) {

    create(Tsum);

  }

  create(Tprint);

}