GLOBAL getYear
GLOBAL getMonth
GLOBAL getDay
GLOBAL getHour
GLOBAL getMinute
GLOBAL getSecond

EXTERN bcdToInt

section .text

%macro rtcHandler 1
	push rdi
	mov al, %1
	out 70h, al
	in al, 71h
	mov rdi, rax
	call bcdToInt
	pop rdi
	ret
%endmacro

getYear:
	rtcHandler 9

getMonth:
	rtcHandler 8

getDay:
	rtcHandler 7

getHour:
	rtcHandler 4

getMinute:
	rtcHandler 2

getSecond:
	rtcHandler 0