all: main

main: main.c 
	gcc -Wall -Werror -pthread $< -o $@

.PHONY: clean test

clean: 
	rm main
test:
	rm main
	gcc -Wall -Werror -pthread main.c -o main -fsanitize=address
	sh test.sh
	rm main
	make
