section .text
	global ft_atoi_base

extern ft_strlen



; rdi=char
is_illegal_base_char:
	cmp dil, ' '
	je .true
	cmp dil, '+'
	je .true
	cmp dil, '-'
	je .true
	cmp dil, 8			; dil < 8 -> not illegal
	je .false
	cmp dil, 13			; dil > 13 -> not illegal
	je .false

	.false:
	mov rax, 0
	ret
	.true:
	mov rax, 1
	ret

; rdi=base
check_base:
	push rbx						; save
	push r12
	mov r12, rdi					; stack rdi ; TODO check if rsp or rbp
	call ft_strlen
	cmp rax, 1
	jle .on_error					; size is <= 1
	mov rbx, rax					; rbx is size of base
	
	mov rdx, 0
	.loop1:							; for all elements in base (rdx)
		cmp rdx, rbx
		je .end_loop1

		mov dil, byte [r12 + rdx]
		call is_illegal_base_char	; check if base has whitespace or +-
		cmp rax, 1
		je .on_error

		mov rcx, rdx				; set start loop to rdx + 1
		inc rcx
		.loop2:						; for all elements in base from rdx to end (rbx)
			cmp rcx, rbx
			je .end_loop2
			mov al, byte [r12 + rcx]
			cmp byte [r12 + rdx], al 	; if base[i] == base[j]
			je .on_error
			inc rcx
			jmp .loop2

		.end_loop2:
		inc rdx
		jmp .loop1

	.end_loop1:
	pop r12
	pop rbx
	mov rax, 1
	ret

	.on_error:
	mov rax, 0
	pop r12
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
