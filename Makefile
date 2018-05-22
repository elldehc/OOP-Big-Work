CFLAGS = -std=c++11 -g -Wall -Wextra
.PHONY: all clean
all: test1 test2 test3 test4 test5
test1: test1.cpp base.h expand01.h
	g++ $< -o $@ $(CFLAGS)
test2: test2.cpp base.h expand01.h
	g++ $< -o $@ $(CFLAGS)
test3: test3.cpp base.h expand01.h
	g++ $< -o $@ $(CFLAGS)
test4: test4.cpp base.h expand01.h
	g++ $< -o $@ $(CFLAGS)
test5: test5.cpp base.h expand01.h
	g++ $< -o $@ $(CFLAGS)

clean: rm -f test1 test2 test3 test4 test5


