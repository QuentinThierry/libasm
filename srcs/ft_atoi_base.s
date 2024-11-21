section .text
	global ft_atoi_base

extern ft_strlen



; rdi=char
is_white_space:
	cmp rdi, 32
	je .true
	cmp rdi, 8
	jle .false
	cmp rdi, 13
	jge .false

	.false
	mov rax, 0
	ret
	.true
	mov rax, 1
	ret

; rdi=base
check_base:
	push rbx					; save
	; mov qword [rsp - 8], rdi	; stack rdi ; TODO check if rsp or rbp
	call ft_strlen
	cmp rax, 1
	jle .on_error				; size is <= 1
	mov rbx, rax				; rbx is size of base
	
	mov rcx, 0
	.loop1:
		cmp rcx, rbx
		jne .end_loop1

		call is_white_space		; check if base has whitespace
		cmp rax, 0
		je .on_error

		mov rdx, rcx			; set start loop to rcx + 1
		inc rcx
		.loop2:
			cmp rcx, rbx		; end loop if its the end of base
			je .end_loop2
			mov al, byte [rsp - 8 + rdx]
			cmp byte [rsp - 8 + rcx], al 	; if base[i] == base[j]
			je .on_error
			inc rdx
			jmp .loop2

		.end_loop2:
		inc rcx
		jmp .loop1

	.end_loop1:
	pop rbx
	mov rax, 1
	ret

	.on_error:
	xor rax, rax
	pop rbx
	ret

; entry point
; rdi=str, rsi=base
ft_atoi_base:
	push rbp			; save base pointer
	mov rbp, rsp

	mov rax, rdi
	and rax, rsi		; AND both pointer
	cmp rax, 0			; compare AND res to 0
	je .fast_return		; if a ptr is NULL, error

	mov rdi, rsi
	call check_base		; check if the base is ok
	cmp rax, 0
	je .fast_return

.fast_return:
	pop rbp
	ret
