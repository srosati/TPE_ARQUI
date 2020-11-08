include ../Makefile.inc

MODULE=0000-shell.bin
SOURCES=$(wildcard [^_]*.c)
LIB_O='../lib.o'

all: $(MODULE)

$(MODULE): $(SOURCES)
	$(GCC) $(GCCFLAGS) -T shell.ld _loader.c $(SOURCES) $(LIB_O) -o ../$(MODULE)

clean:
	rm -rf *.o

.PHONY: all clean print
