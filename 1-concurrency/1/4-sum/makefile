sum: sum.c thread.h
	gcc sum.c -o sum

#100000000
sum1: sum.c thread.h
	gcc -O1 sum.c -o sum1 

#200000000
sum2: sum.c thread.h
	gcc -O2 sum.c -o sum2

#学到了-f可以忽略不存在文件，这样的话，如果有的可执行文件没有被make出来就不会报错了
clean:
	rm -f sum
	rm -f sum1
	rm -f sum2