#include "thread.h"

#include "thread-sync.h"


int n, count = 0;

mutex_t lk = MUTEX_INIT();


#define CAN_PRODUCE (count < n)//左括号的打印条件

#define CAN_CONSUME (count > 0)//右括号的打印条件


void Tproduce() {

  while (1) {

retry:

    mutex_lock(&lk);

    if (!CAN_PRODUCE) {

      mutex_unlock(&lk);

      goto retry;

    }

    count++;

    printf("(");  // Push an element into buffer

    mutex_unlock(&lk);

  }

}


void Tconsume() {

  while (1) {

retry:

    mutex_lock(&lk);

    if (!CAN_CONSUME) {

      mutex_unlock(&lk);

      goto retry;

    }

    count--;

    printf(")");  // Pop an element from buffer

    mutex_unlock(&lk);

  }

}


int main(int argc, char *argv[]) {

  assert(argc == 2);

  n = atoi(argv[1]);//括号嵌套深度

  setbuf(stdout, NULL);//关闭缓冲区

  for (int i = 0; i < 8; i++) //创造8个生产者和8个消费者
  {

    create(Tproduce);

    create(Tconsume);

  }

}