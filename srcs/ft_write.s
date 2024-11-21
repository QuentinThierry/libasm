section .text
	global ft_write

extern __errno_location

ft_write:
	mov rax, 1					; call syscall 1 (write)
	syscall
	cmp rax, 0					; if write ret is < 0
	jl on_error
	ret

	on_error:
		neg rax
		mov rbx, rax
		call __errno_location	; find errno location
		mov dword [rax], ebx	; derefence errno location and set it to ebx, errno is 32 bits long
		mov rax, -1
		ret
