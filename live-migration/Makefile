#CPPFLAGS = -DDEBUG -DLOG_LEVEL=LOG_DEBUG
CFLAGS = -Wall -Wextra -Wno-unused-parameter -g

.PHONY: all clean

build: all

all: memory-test1 memory-test2

memory-test1: memory-test1.o

memory-test1.o: memory-test1.c

memory-test2: memory-test2.o

memory-test2.o: memory-test2.c

clean:
	-rm -f *~
	-rm -f *.o
	-rm -f memory-test1 memory-test2
