#CPPFLAGS = -DDEBUG -DLOG_LEVEL=LOG_DEBUG
CFLAGS = -Wall -Wextra -Wno-unused-parameter -g

.PHONY: all clean

build: all

all: cp_mmap cp_rdwr

cp_mmap: cp_mmap.o

cp_mmap.o: cp_mmap.c util.h

cp_rdwr: cp_rdwr.o

cp_rdwr.o: cp_rdwr.c util.h

clean:
	-rm -f *~
	-rm -f *.o
	-rm -f cp_mmap cp_rdwr
