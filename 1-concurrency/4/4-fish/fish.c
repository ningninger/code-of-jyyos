#include "thread.h"

#include "thread-sync.h"

//一份很重要的code


#define LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))


//一共有6种状态
enum { A = 1, B, C, D, E, F, };


//一共有这么多的状态转换
struct rule {

  int from, ch, to;

} rules[] = {

  { A, '<', B },

  { B, '>', C },

  { C, '<', D },

  { A, '>', E },

  { E, '<', F },

  { F, '>', D },

  { D, '_', A },

};


//初始化状态
int current = A, quota = 1;

mutex_t lk = MUTEX_INIT();

cond_t cv = COND_INIT();


//返回当前状态可能的下一个状态
int next(char ch) {

  for (int i = 0; i < LENGTH(rules); i++) {

    struct rule *rule = &rules[i];

    if (rule->from == current && rule->ch == ch) {

      return rule->to;

    }

  }

  return 0;

}


static int can_print(char ch) {

    return next(ch) != 0 && quota > 0;

}


void fish_before(char ch) {

  mutex_lock(&lk);

  while (!can_print(ch)) {

    // can proceed only if (next(ch) && quota)

    cond_wait(&cv, &lk);

  }

//允许执行下面的printf
  quota--;

  mutex_unlock(&lk);

}

//执行完printf后，需要生产一个可以进行printf的资源
void fish_after(char ch) {

  mutex_lock(&lk);

  quota++;

  current = next(ch);

  assert(current);

  cond_broadcast(&cv);

  mutex_unlock(&lk);

}


const char roles[] = ".<<<<<>>>>___";


void fish_thread(int id) {

  char role = roles[id];
  //根据当前的线程号来决定自己是一个打印什么类型的字符的线程。

  while (1) {

    fish_before(role);

    putchar(role);  // Not lock-protected

    fish_after(role);

  }

}


int main() {

  setbuf(stdout, NULL);//关闭缓冲区

  for (int i = 0; i < strlen(roles); i++)

    create(fish_thread);

}