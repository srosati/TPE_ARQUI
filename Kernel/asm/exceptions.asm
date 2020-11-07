GLOBAL _exception0Handler
GLOBAL _exception1Handler

EXTERN inforeg

section .text

_exception0Handler:
	add rsp, 8
	push 0x400000
	iretq

_exception1Handler:
	add rsp, 8
	push 0x400000
	iretq

	