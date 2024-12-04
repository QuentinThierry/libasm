<h1 style="text-align:center;">libasm</h1>

	Summary: The aim of this project is to get familiar with assembly language.

## How to use
- Use ``make`` to compile the ``libasm.a`` static library. 
- Use ``make test`` to compile and execute built-in unit tests.

## The language
This project uses ``x86_64`` assembly with ``Intel`` syntax. It is writting purely in asm.

It is compiled with ``nasm`` in ``elf64`` objects files.

## The project
This project aims to use and understand x86_64 assembly.

It will use concepts like :

- Calling conventions
- Managing stack variables
- Un/Conditional jumps
- Complex function calls
- Using structures in asm with linked lists
- Managing memory via malloc/free
- Syscalls
- Errno
- Function pointers

List of functions that have been (re)built :

	strlen
	strcmp
	strcpy
	strdup
	write			(errno)
	read			(errno)
	atoi_base		(atoi with any given base)
	--=-- linked list --=--
	list_push_front
	list_size
	list_sort		(sort a linked list with a given function)
	list_remove_if	(remove a linked list's element with a given function)





## Calling convention
- Some registers must be saved before being used in a function. (see below table)
- The stack must be aligned on 16 bytes before calling a function
- A function will always be aligned on 8 bytes after a call instruction (rip is pushed)

## The registers
| 64-Bits | 32-Bits | 16-Bits | 8-Bits | Calling Convention | When writing a function | Main purpose |
| --------| --------| --------| -------| -------------------| --------------| --------|
| `rax` | `eax` | `ax` | `al` | Saved by callee | Use freely | Return value |
| `rdi` | `edi` | `di` | `dil` | Saved by callee | Use freely | 1st argument |
| `rsi` | `esi` | `si` | `sil` | Saved by callee | Use freely | 2nd argument |
| `rdx` | `edx` | `dx` | `dl` | Saved by callee | Use freely | 3rd argument |
| `rcx` | `ecx` | `cx` | `cl` | Saved by callee | Use freely | 4th argument |
| `r8` | `r8d` | `r8w` | `r8b` | Saved by callee | Use freely | 5th argument|
| `r9` | `r9d` | `r9w` | `r9b` | Saved by callee | Use freely | 6th argument|
| `r10` | `r10d` | `r10w` | `r10b` | Saved by callee | Use freely | Temporary |
| `r11` | `r11d` | `r11w` | `r11b` | Saved by callee | Use freely | Temporary |
| `rsp` | `esp` | `sp` | `spl` | Saved by caller | Save before using | Stack Pointer |
| `rbx` | `ebx` | `bx` | `bl` | Saved by caller | Save before using | Local Variable |
| `rbp` | `ebp` | `bp` | `bpl` | Saved by caller | Save before using | Base Pointer |
| `r12` | `r12d` | `r12w` | `r12b` | Saved by caller | Save before using | Local Variable |
| `r13` | `r13d` | `r13w` | `r13b` | Saved by caller | Save before using | Local Variable |
| `r14` | `r14d` | `r14w` | `r14b` | Saved by caller | Save before using | Local Variable |
| `r15` | `r15d` | `r15w` | `r15b` | Saved by caller | Save before using | Local Variable |
| `rip` | | | | | | Instruction Pointer |
| `eflags` | | | | | | Status/condition code bits |
