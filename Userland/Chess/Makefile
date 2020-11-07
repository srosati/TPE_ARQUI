include ../Makefile.inc

MODULE=0001-chess.bin
SOURCES=$(wildcard [^_]*.c)
LIB_O='../lib.o'

all: $(MODULE)

$(MODULE): $(SOURCES)
	$(GCC) $(GCCFLAGS) -T chess.ld _loader.c $(SOURCES) $(LIB_O) -o ../$(MODULE)

clean:
	rm -rf *.o

.PHONY: all clean print
