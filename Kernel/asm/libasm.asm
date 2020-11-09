GLOBAL cpuVendor
GLOBAL getKey
GLOBAL saveRegisters
GLOBAL saveRIP
GLOBAL getRegisters
GLOBAL getMem

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

saveRIP:
	mov [registers+128], rdi
	ret

saveRegisters:
	mov [registers], rax
	mov [registers+8], rbx
	mov [registers+16], rcx
	mov [registers+24], rdx
	mov [registers+32], rbp
	mov [registers+40], rsp
	mov [registers+48], rsi
	mov [registers+56], rdi
	mov [registers+64], r8
	mov [registers+72], r9
	mov [registers+80], r10
	mov [registers+88], r11
	mov [registers+96], r12
	mov [registers+104], r13
	mov [registers+112], r14
	mov [registers+120], r15
	ret

getRegisters:
	push rax
	push rbx
	push rcx
	mov rax, 0
	mov rbx, 0
.loop:
	mov rcx, [registers+rbx]
	mov [rdi+rbx], rcx
	add rbx, 8
	inc rax
	cmp rax, 17
	jl .loop
	pop rcx
	pop rbx
	pop rax
	ret


getKey:
	push rbp
	mov rbp, rsp
	in al, 0x60	
	mov rsp, rbp
	pop rbp
	ret

getMem:
	push rbp
	mov rbp, rsp
	push rbx
.loop:
	mov bl, [rdi]
	mov [rsi], bl
	inc rdi
	inc rsi
	dec rdx
	cmp rdx, 0
	jg .loop
	pop rbx
	mov rsp, rbp
	pop rbp
	ret

section .bss
	registers resb 136


