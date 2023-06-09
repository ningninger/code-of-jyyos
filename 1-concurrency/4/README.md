通过学习本章的code，我们拥有了一个黄金版本的条件状态并发模板  
```c
    lock();
    while(!CONDITION)
    {
        wait();
    }
    work();
    unlock();
```
当然，不忘初心，我们想要的过程实际上是这样的
```C
    WAIT_UNTIL(cond) with(mutex)
    {
        //cond 在此时成立
        work();
    }
```

但是操作系统的设计者提供了条件变量的机制来模仿这个过程:
+ `cond_wait(cv, lk)`释放互斥锁`lk`并进入睡眠状态。当被唤醒时，其会重新试图获取互斥锁，只有当获得了互斥锁，才返回
+ `cond_signal(cv)`唤醒一个在`cv`上等待的线程
+ `cond_boradcast(cv)`唤醒所有在`cv`上等待的线程