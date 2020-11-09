GLOBAL _exception0Handler
GLOBAL _exception1Handler

GLOBAL exceptionCode

EXTERN saveRegisters
EXTERN saveRIP

section .text

%macro exceptionHandler 1
	push rdi
	mov rdi, [rsp+8]
	call saveRIP
	pop rdi
	call saveRegisters
	push 0x400000
	mov BYTE [exception_code], %1
	ret
%endMacro

_exception0Handler:
	exceptionHandler 1

_exception1Handler:
	exceptionHandler 2

exceptionCode:
	mov al, [exception_code]
	mov BYTE [exception_code], 0
	ret

section .data
	exception_code db 0;


	