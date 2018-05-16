.PHONY: all clean
all: test1
test1: test1.cpp base.h
	g++ test1.cpp -o test1 -std=c++11 -g -Wall -Wextra
test2: test2.cpp base.h expand01.h
	g++ test2.cpp -o test2 -std=c++11 -g -Wall -Wextra
clean: rm -f test1 test2


