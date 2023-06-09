#include "thread.h"

#include "thread-sync.h"


sem_t fill, empty;

/*
void P(sem_t *sem)
{
    wait_until(sem->count > 0)
    {
        sem->count--;
    }
}

void V(sem_t *sem)
{
    sem_count++;
}

将下面的P和V用上面的函数来替换，就不难理解了

*/



void Tproduce() {

  while (1) {

    P(&empty);//等待empty满足,满足就减掉，empty-- 好狠

    printf("(");

    V(&fill); // fill++， 叫所有的等待fill的线程可以开始干活了

  }

}


void Tconsume() {

  while (1) {

    P(&fill);

    printf(")");

    V(&empty);

  }

}


int main(int argc, char *argv[]) {

  assert(argc == 2);

  //将fill初始化为0
  SEM_INIT(&fill, 0);
  //将empty初始化成嵌套深度
  SEM_INIT(&empty, atoi(argv[1]));

  for (int i = 0; i < 8; i++) {

    create(Tproduce);

    create(Tconsume);

  }

}