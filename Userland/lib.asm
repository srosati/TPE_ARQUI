GLOBAL getChar
GLOBAL putChar
GLOBAL getTime
GLOBAL drawPixel
GLOBAL setInterval
GLOBAL stopInterval
GLOBAL getScreenDimentions

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
