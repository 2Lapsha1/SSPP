CXX = gcc 
CXXFLAGS = -Wall -Werror -pthread

all: main

main: main.c 
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean test

clean: 
	rm main
test:
	rm main
	$(CXX) $(CXXFLAGS) main.c -o main -fsanitize=address
	sh test.sh
	rm main
	make
