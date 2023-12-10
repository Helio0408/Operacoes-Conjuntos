all:
	gcc src/*.c -Wall -Wextra -std='c99' -pedantic --debug -o main

run:
	./main

clear:
	rm main

clean:
	rm main
