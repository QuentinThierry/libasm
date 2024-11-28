section .text
	global ft_list_size

; rdi=*begin_list
ft_list_size:
	xor rax, rax
	.loop:
		cmp rdi, 0
		je .end_loop
		mov rdi, qword [rdi + 8]	; set rdi to the address of the next elem (rdi = rdi->next)
		inc rax
		jmp .loop
	.end_loop:
	ret