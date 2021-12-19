segment .data
	__msg_error_division	db "****Error de ejecuccion: Division por cero.", 0
	__msg_error_vector	db "****Error de ejecuccion: Indice fuera de rango.", 0

segment .bss
	__esp resd 1
	_vector resd 3

segment .text
	global main
	extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
	extern alfa_malloc, alfa_free, ld_float

main:
	mov dword [__esp], esp
	push dword 0
	pop eax
	cmp eax, 0
	jl __error_vector
	cmp eax, 3
	jge __error_vector
	lea eax, [4*eax + _vector]
	push eax
	push dword 0
	pop dword eax
	pop dword ebx
	mov dword [ebx], eax
	push dword 1
	pop eax
	cmp eax, 0
	jl __error_vector
	cmp eax, 3
	jge __error_vector
	lea eax, [4*eax + _vector]
	push eax
	push dword 1
	pop dword eax
	pop dword ebx
	mov dword [ebx], eax
	push dword 1
	pop eax
	cmp eax, 0
	jl __error_vector
	cmp eax, 3
	jge __error_vector
	lea eax, [4*eax + _vector]
	push eax
	pop dword eax
	mov eax, dword [eax]
	push dword eax
	call print_boolean
	call print_endofline
	add esp, 4
	jmp near fin
__error_division:
	push __msg_error_division
	jmp near __salida_mensaje_error
__error_vector:
	push __msg_error_vector
__salida_mensaje_error:
	call print_string
	call print_endofline
fin:
	mov dword esp, [__esp]
	ret
