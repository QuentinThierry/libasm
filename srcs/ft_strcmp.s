section .text
	global ft_strcmp

ft_strcmp:
	xor r10, r10 ; set registers to 0
	xor r11, r11
	loop:
		mov r10b, byte [rdi]
		mov r11b, byte [rsi]

		cmp r10b, r11b ; bytes are different
		jne done
		cmp r10b, 0 ; left byte is 0
		je done
		cmp r11b, 0 ; right byte is 0
		je done

		inc rdi
		inc rsi
		jmp loop
	done:
		sub r10d, r11d
		mov rax, r10
		ret
