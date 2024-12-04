section .text
	global ft_list_remove_if

extern free

; rdi=**begin_list, rsi=void* dataref, rdx=int(*cmp)(elem->data, dataref), rcx=void(*free_fct)(void*)
ft_list_remove_if:
	push r12
	push r13
	push r14
	push r15
	push rbx

	mov r12, [rdi]						; load first elem in r12
	mov r13, rsi						; save dataref
	mov r14, rdx						; save cmp function ptr
	mov r15, rcx						; save free_fct function ptr
	mov rbx, 0							; save previous elem (init at NULL)
	push rdi							; stack **begin_list to modify it

	.loop:
		cmp r12, 0
		je .end_loop

		; call cmp
		mov rsi, [r12]						; cmp elem->data
		mov rdi, r13						; and dataref
		call r14							; call cmp
		cmp eax, 0
		je .should_remove
		; else no remove
			mov rbx, r12					; set previous = elem
			jmp .end_remove
		; if remove
		.should_remove:
			mov rsi, [r12]
			call r15						; free elem->data

			cmp rbx, 0						; if no previous element
			jne .had_previous_elem
			; else no previous
				mov rax, [rsp]				; load **begin_list from stack in rax
				mov rsi, [r12 + 8]			; load elem->next in rsi
				mov [rax], rsi				; change **begin_list to point to elem->next
				jmp .end_had_previous_elem	; previous is still NULL

			; if had previous
			.had_previous_elem:
				mov rax, [r12 + 8]			; previous->next = elem->next (skip elem)
				mov [rbx + 8], rax

			.end_had_previous_elem:
			push qword [r12 + 8]			; save elem->next
			mov rdi, r12					; free elem
			call free
			pop r12							; load elem->next in r12
			jmp .loop

		.end_remove:
		mov r12, [r12 + 8]					; elem = elem->next
		jmp .loop
	.end_loop:

	pop rax
	pop rbx
	pop r15
	pop r14
	pop r13
	pop r12
	ret
