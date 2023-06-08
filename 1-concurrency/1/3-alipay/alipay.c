#include "thread.h"


unsigned long balance = 100;//共享变量


void Alipay_withdraw(int amt) {

  if (balance >= amt) {

    usleep(1);  // Unexpected delays

    //因为延迟的产生，这个时候if语句可能已经不满足条件了
    balance -= amt;

  }

}


void Talipay(int id) {

  Alipay_withdraw(100);

}


int main() {

  create(Talipay);

  create(Talipay);

  join();

  printf("balance = %lu\n", balance);

}