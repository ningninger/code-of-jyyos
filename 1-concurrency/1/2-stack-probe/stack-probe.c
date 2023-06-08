#include "thread.h"


void* volatile low[64];

void* volatile high[64];

//POSIX规定了程序的栈空间为8192KB

/*为什么这个程序可以通过函数的参数就可以知道当前的栈的大小呢
这需要一些计算机系统基础的知识，我们知道函数调用是会产生调用栈的，函数的参数也是被存储在栈中，
通过参数的地址，我们可以一定反映出程序的栈的大小，实际上就是是递归的深度反映出栈的大小。
*/

void update_range(int T, void* ptr) {

    if (ptr < low[T]) low[T] = ptr;

    if (ptr > high[T]) high[T] = ptr;

}


void probe(int T, int n) {

    update_range(T, &n);

    long sz = (uintptr_t)high[T] - (uintptr_t)low[T];

    if (sz % 1024 < 32)//隔一段时间打印栈至少有多大 
    {

        printf("Stack(T%d) >= %ld KB\n", T, sz / 1024);

    }

    probe(T, n + 1);  // Infinite recursion

}


void Tprobe(int T) {

    low[T] = (void*)-1;//初始化

    high[T] = (void*)0;//初始化

    // printf("stack low = %#X, stack high = %#X\n", low[T], high[T]);

    // sleep(2);

    update_range(T, &T);

    probe(T, 0);

}


int main() {

    setbuf(stdout, NULL);//关闭缓冲区，不需要等待缓冲区满了，才进行输出

    for (int i = 0; i < 4; i++) {

        create(Tprobe);//创造4个线程

    }

}