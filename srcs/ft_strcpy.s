section .text
	global ft_strcpy

; rsi is src
; rdi is dest
ft_strcpy:
	mov rax, rdi
	cpy_str:
		cmp byte [rsi], 0
		je done
		mov dl, byte [rsi]
		mov byte [rdi], dl
		inc rsi
		inc rdi
		jmp cpy_str
	done:
		mov byte [rdi], 0
	ret
