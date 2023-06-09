#ThreadSanitizer 通过检查内存之间的happens-before关系，找出程序中潜在的数据竞争
alipay: alipay.c
	gcc -fsanitize=thread alipay.c -o alipay

clean:
	rm -f alipay