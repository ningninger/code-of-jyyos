#.S和.s没有什么区别，单纯地是因为S包含着可读性更高的汇编指令和宏，s可能包含直接使用机器指令的较低级别的代码
a.out: minimal.S

	gcc -S minimal.S > minimal.s

	as minimal.s -o minimal.o
     
	ld minimal.o

clean:
	rm -f a.out
	rm -f *.o
	rm -f *.s