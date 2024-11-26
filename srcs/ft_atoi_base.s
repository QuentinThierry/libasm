section .text
	global ft_atoi_base

extern ft_strlen


is_white_space:
	cmp dil, ' '
	je .true
	cmp dil, 8			; dil < 8 -> not whitespace
	jl .false
	cmp dil, 13			; dil > 13 -> not whitespace
	jg .false

	.true:
	mov rax, 1
	ret
	.false:
	mov rax, 0
	ret

; rdi=char
is_illegal_char:
	cmp dil, ' '
	je .true
	cmp dil, '+'
	je .true
	cmp dil, '-'
	je .true
	cmp dil, 8			; dil < 8 -> not illegal
	jl .false
	cmp dil, 13			; dil > 13 -> not illegal
	jg .false

	.false:
	mov rax, 0
	ret
	.true:
	mov rax, 1
	ret

; TODO: check stack alligment to 16

; rdi=base
check_base:
	push rbx						; save ; TODO: rbp
	push r11
	mov r11, rdi					; stack rdi
	call ft_strlen
	cmp rax, 1
	jle .on_error					; size is <= 1
	mov rbx, rax					; rbx is size of base
	
	mov rdx, 0
	.loop1:							; for all elements in base (rdx)
		cmp rdx, rbx
		je .end_loop1

		mov dil, byte [r11 + rdx]
		call is_illegal_char		; check if base has whitespace or +-
		cmp rax, 1
		je .on_error

		mov rcx, rdx				; set start loop to rdx + 1
		inc rcx
		.loop2:						; for all elements in base from rdx to end (rbx)
			cmp rcx, rbx
			je .end_loop2
			mov al, byte [r11 + rcx]
			cmp byte [r11 + rdx], al 	; if base[i] == base[j]
			je .on_error
			inc rcx
			jmp .loop2

		.end_loop2:
		inc rdx
		jmp .loop1

	.end_loop1:
	pop r11
	pop rbx
	mov rax, 1
	ret

	.on_error:
	mov rax, 0
	pop r11
	pop rbx
	ret


; rdi=str
skip_white_space:
	push r12
	mov r12, rdi

	xor rdi, rdi
	xor rcx, rcx
	.loop:						; for all char until not whitespace
		mov dil, byte [r12 + rcx]
		call is_white_space
		cmp rax, 0					; if is not a whitespace or is \0, end loop
		je .end_loop
		inc rcx						; else look next char
		jmp .loop

	.end_loop:
	pop r12
	mov rax, rcx
	ret

; rdi=str (from stack)
get_sign:
	mov rdi, [rsp + 16]		; get the value in the stack (rsp + size(rip) + 8)
	xor rcx, rcx
	mov rax, 1

	.loop:
		mov dl, byte [rdi + rcx]
		cmp dl, '+'
		je .plus
		cmp dl, '-'
		je .minus
		jmp .end_loop		; else end loop

		.plus:				; on +, inc and loop
		inc rcx
		jmp .loop
		.minus:				; on -, inc, negate and loop
		inc rcx
		neg rax
		jmp .loop
	
	.end_loop
	add [rsp + 16], rcx		; increment the value of the ptr in the stack
	ret

; rdi=base, rsi=char
is_in_base:
	mov rax, 0
	.loop:
		mov dl, byte [rdi + rax]
		cmp dl, 0			; if end of base then char is not in base, ret -1
		je .end_loop_false

		cmp dl, sil			; if base char is the wanted char, ret rax
		je .end_loop_true

		inc rax				; else inc to check next base char
		jmp .loop
	.end_loop_true:
	ret
	.end_loop_false:
	mov rax, -1
	ret

; rdi=str, rsi=base, rdx=sign
get_value:
	push rbx
	xor rcx, rcx		; rcx = return value (TODO see calling convention ?)
	mov r8, rdi			; r8 = str
	mov r9, rsi			; r9 = base
	mov r10, rdx		; r10 = sign
	
	mov rdi, r9			; call ft_strlen(base)
	call ft_strlen
	mov rbx, rax		; rbx = base size

	.loop:
		cmp byte [r8], 0
		je .end_loop

		mov rdi, r9
		mov rsi, [r8]
		call is_in_base
		cmp rax, -1		; if is not in base, stop here
		je .end_loop

		imul rcx, rbx	; mult by the base size
		add rcx, rax	; add the position of the char

		inc r8
		jmp .loop

	.end_loop:
	mov rax, rcx
	pop rbx
	ret


; entry point
; rdi=str, rsi=base
ft_atoi_base:
	push rbp					; save base pointer
	mov rbp, rsp

	mov rax, rdi
	and rax, rsi				; AND both pointer
	cmp rax, 0					; compare AND res to 0
	je .fast_return				; if a ptr is NULL, error

	mov r11, rdi
	mov rdi, rsi
	call check_base				; check if the base is ok
	cmp rax, 0
	je .fast_return

	mov rdi, r11
	call skip_white_space
	add r11, rax				; move pointer to skip whitespaces

	sub rsp, 16					; allocate 2 qword on stack (one for rdi address, one for alignment)
	mov qword [rsp + 8], r11

	call get_sign
	mov r11, [rsp + 8]			; get the changed value
	add rsp, 16					; free space on stack

	mov rdi, r11
	mov rdx, rax
	call get_value

	.fast_return:
	pop rbp
	ret
