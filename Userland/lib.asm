GLOBAL clearScreen
GLOBAL getChar
GLOBAL putChar
GLOBAL getTime
GLOBAL drawPixel
GLOBAL setInterval
GLOBAL stopInterval
GLOBAL getScreenDimentions
GLOBAL getMem
GLOBAL getRegisters
GLOBAL checkException
GLOBAL invalidOpCode

section .text

%macro handler 1
	push rbp
	mov rbp, rsp
	mov rax, %1
	int 80h
	mov rsp, rbp
	pop rbp
	ret
%endmacro

clearScreen:
	handler 0

getChar:
	handler 1

putChar:
	handler 2

getTime:
	handler 3

drawPixel:
	handler 4

setInterval:
	handler 5

stopInterval:
	handler 6

getScreenDimentions:
	handler 7

getMem:
	handler 8

getRegisters:
	handler 9

checkException:
	handler 10

invalidOpCode:
	ud2