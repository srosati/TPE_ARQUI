include Makefile.inc

LIB='lib.asm'
LIB_O='lib.o'

all: asm shell chess

shell:
	cd Shell; make

chess:
	cd Chess; make

asm: 
	$(ASM) $(ASMFLAGS) -o $(LIB_O) $(LIB)

clean:
	cd Shell; make clean
	cd Chess; make clean
	rm -rf *.bin


.PHONY: shell chess all clean
