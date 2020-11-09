GLOBAL _irq0handler
GLOBAL _irq1handler
GLOBAL _syscallhandler
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask

EXTERN irqDispatcher
EXTERN clearScreen
EXTERN getChar
EXTERN putChar
EXTERN getTime
EXTERN drawPixel
EXTERN setInterval
EXTERN stopInterval
EXTERN getScreenDimentions
EXTERN getMem
EXTERN getRegisters
EXTERN exceptionCode

section .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro

_irq0handler:
	irqHandlerMaster 0

_irq1handler:
	irqHandlerMaster 1

_syscallhandler:
	sti
	cmp rax, 0
	je .clear_screen
	cmp rax, 1
	je .call_getc
	cmp rax, 2
	je .call_putc
	cmp rax, 3
	je .get_time
	cmp rax, 4
	je .draw_pixel
	cmp rax, 5
	je .set_interval
	cmp rax, 6
	je .stop_interval
	cmp rax, 7
	je .get_screen_dimentions
	cmp rax, 8
	je .get_mem
	cmp rax, 9
	je .get_registers
	cmp rax, 10
	je .get_exception_code
	jmp .done

.clear_screen:
	call clearScreen
	jmp .done

.call_getc:
	call getChar
	jmp .done

.call_putc:
	call putChar
	jmp .done

.get_time:
	call getTime
	jmp .done

.draw_pixel:
	call drawPixel
	jmp .done

.set_interval:
	call setInterval
	jmp .done

.stop_interval:
	call stopInterval
	jmp .done

.get_screen_dimentions:
	call getScreenDimentions
	jmp .done

.get_mem:
	call getMem
	jmp .done

.get_registers:
	call getRegisters
	jmp .done

.get_exception_code:
	call exceptionCode
	jmp .done

.done:
	push rax
	mov al, 20h
	out 20h, al
	pop rax
	iretq
	
_cli:
	cli
	ret

_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn