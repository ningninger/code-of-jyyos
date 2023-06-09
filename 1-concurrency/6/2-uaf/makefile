# AddressSanitizer可以实现一系列内存错误相关的检查
uaf: uaf.c
	gcc -fsanitize=address uaf.c -o uaf

clean:
	rm -f uaf