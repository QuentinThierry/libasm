section .text
	global ft_list_push_front
	extern malloc

; rdi=t_list **begin_list, rsi=void *data
ft_list_push_front:

	mov rdx, rdi				; save begin_list in rdx
	mov r9, qword [rdx]

	; call malloc
	push rdx
	push rsi
	push r9
	mov rdi, 16					; the t_list obj is 16 bytes long
	sub rsp, 8					; align on 16 for call
	call malloc
	add rsp, 8					; realign on 8
	pop r9
	pop rsi
	pop rdx
	cmp rax, 0					; check for malloc fail
	je .fast_return

	mov [rax], rsi				; set the content of new elem to data
	mov [rax + 8], r9			; move saved first elem (or NULL) in new_elem->next

	mov qword [rdx], rax		; set the begin_list points on the new elem
	.fast_return:
	ret
