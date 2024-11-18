section .text
	global ft_strlen

ft_strlen:
	mov rax, rdi
	loop:
		cmp byte [rdi], 0
		je done
		inc rdi
		jmp loop
	done:
		sub rdi, rax
		mov rax, rdi
		ret

; ft_strlen:
; 	mov rax, 0
; 	loop:
; 		cmp byte [rdi + rax], 0
; 		je done
; 		inc rax
; 		jmp loop
; 	done:
; 		ret
