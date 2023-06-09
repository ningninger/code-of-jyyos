#include <am.h>

#include <klib.h>

#include <klib-macros.h>


#define MAX_CPU 8


typedef union task {

  struct {

    const char *name;

    union task *next;

    void      (*entry)(void *);

    Context    *context;

  };

  uint8_t stack[8192];

} Task;  // A "state machine"


Task *currents[MAX_CPU];

#define current currents[cpu_current()]


int locked = 0;  // A spin lock

void lock()   { while (atomic_xchg(&locked, 1)); }

void unlock() { atomic_xchg(&locked, 0); }


#include "tasks.h"

//中断程序
Context *on_interrupt(Event ev, Context *ctx) {

  if (!current) current = &tasks[0];  // First interrupt 第一次中断，实际上是在该处理器上的idle线程中，随便给一个线程

  else current->context = ctx;  // Save pointer to stack-saved context

  do {

    current = current->next;

  } while ((current - tasks) % cpu_count() != cpu_current());
  //这里做了一个简单的假设，它让每个线程存在一个归属的处理器，也就是该线程只能在该处理器上执行，
  //这让不会出现一个线程被多个处理器调度的糟糕情况

  return current->context;  // Restore a new context，通过让当前的处理器知道线程的上下文信息就可以实现执行该线程的任务了

}


void mp_entry() {

//可以理解为主动中断
  yield();  // Self-trap; never returns

}


int main() {

  cte_init(on_interrupt);//初始化中断


  for (int i = 0; i < LENGTH(tasks); i++) {

    Task *task    = &tasks[i];

    Area stack    = (Area) { &task->context + 1, task + 1 };//为每个线程分配自己的栈空间

    task->context = kcontext(stack, task->entry, (void *)task->name);//为每个线程创建自己的上下文

    task->next    = &tasks[(i + 1) % LENGTH(tasks)];
    //这里没有采用随机调度算法，而是每个线程给定下一个调度的线程

  }

  mpe_init(mp_entry);

}
