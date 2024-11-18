section .text
	global ft_strlen

ft_strlen:
	loop:
		cmp byte [rdi], 0
		je done
		inc rdi
		jmp loop
	done:
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
