all: main

main: main.c 
	gcc -Werror -lpapi $< -o $@

.PHONY: clean test

clean: 
	rm main
test:
	rm main
	gcc -Werror -lpapi main.c -o main -fsanitize=address
	sh test.sh
	rm main
	make
