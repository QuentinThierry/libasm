section .text
	global ft_list_sort


; rdx, rcx, r8, r9, r10, r11
; r12, r13, r14, r15

; rdi=**begin_list, rsi=int (*cmp)(void*, void *)
ft_list_sort:
	push r12
	push r13
	push r14
	mov r12, rsi					; save the cmp function pointer
	mov r13, [rdi]					; get first elem of the list (var1)
	.loop1:
		cmp r13, 0
		je .end_loop1

		mov r14, [r13 + 8]			; set r14 to r13->next
		.loop2:
			cmp r14, 0				; test if end of list
			je .end_loop2

			mov rdi, [r14]			; load data ptr into first arg rdi
			mov rsi, [r13]			; load data ptr into second arg rsi
			call r12				; call cmp function ptr

			test eax, eax			; test sign bit (cmp ret is 32 bits)
			js .swap_elems			; if neg, then not sorted so swap them
			; else
				jmp .done
			; if
			.swap_elems:
				mov rax, [r13]		; rax = var1
				xchg [r14], rax		; swap(var2, rax)
				mov [r13], rax		; var1 = rax

			.done:
			mov r14, [r14 + 8]		; r14 = r14->next
			jmp .loop2
		.end_loop2:

		mov r13, [r13 + 8]
		jmp .loop1
	.end_loop1:

	pop r14
	pop r13
	pop r12
	ret