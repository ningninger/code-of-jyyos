// User-defined tasks

//每个线程只是打印出自己是谁，和现在被调度到哪个处理器上
void func(void *arg) {

  while (1) {

    lock();

    printf("Thread-%s on CPU #%d\n", arg, cpu_current());

    unlock();

    for (int volatile i = 0; i < 100000; i++) ;

  }

}

//一个线程数组，每个线程包含了自己的名字和入口方法
Task tasks[] = {

  { .name = "A", .entry = func },

  { .name = "B", .entry = func },

  { .name = "C", .entry = func },

  { .name = "D", .entry = func },

  { .name = "E", .entry = func },

};