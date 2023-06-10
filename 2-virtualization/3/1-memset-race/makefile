memset-race: memset-race.c thread.h
	#gcc -fsanitize=thread memset-race.c -o memset-race
	gcc memset-race.c -o memset-race
clean:
	rm -f memset-race