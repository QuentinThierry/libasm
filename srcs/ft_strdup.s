section .text
	global ft_strdup

extern ft_strlen
extern ft_strcpy
extern malloc

ft_strdup:
	push rbp
	push rbx				; save rbx (caller saved)
	mov rbp, rsp

	mov rbx, rdi			; save the original ptr
	call ft_strlen			; get size of malloc
	inc rax					; add 1 to size for \0 bit
	mov rdi, rax

	call malloc				; malloc for the string size
	cmp rax, 0
	je exit_func			; check malloc failed

	mov rdi, rax
	mov rsi, rbx
	call ft_strcpy			; copy the string

	exit_func:
		pop rbx
		pop rbp
		ret