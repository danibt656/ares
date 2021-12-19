segment .data
	__msg_error_division	db "****Error de ejecuccion: Division por cero.", 0
	__msg_error_vector	db "****Error de ejecuccion: Indice fuera de rango.", 0

segment .bss
	__esp resd 1
	_resultado resd 1
	_x resd 1

segment .text
	global main
	extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
	extern alfa_malloc, alfa_free, ld_float
_fibonacci:
	push ebp
	mov ebp, esp
	sub esp, 8
	mov eax, dword [ebp + 8]
	push dword eax
	push dword 0
	pop dword ebx
	pop dword eax
	cmp eax, ebx
	je __igual_1
	push dword 0
	jmp __end_igual_1
__igual_1:
	push dword 1
__end_igual_1:
	pop eax
	cmp eax, 0
	je __else_2
	push dword 0
	pop eax
	mov esp, ebp
	pop ebp
	ret
	jmp near __endif_2
__else_2:
__endif_2:
	mov eax, dword [ebp + 8]
	push dword eax
	push dword 1
	pop dword ebx
	pop dword eax
	cmp eax, ebx
	je __igual_3
	push dword 0
	jmp __end_igual_3
__igual_3:
	push dword 1
__end_igual_3:
	pop eax
	cmp eax, 0
	je __else_4
	push dword 1
	pop eax
	mov esp, ebp
	pop ebp
	ret
	jmp near __endif_4
__else_4:
__endif_4:
	mov eax, dword [ebp + 8]
	push dword eax
	push dword 1
	pop dword ebx
	pop dword eax
	sub eax, ebx
	push dword eax
	call _fibonacci
	add esp, 4
	push dword eax
	pop dword eax
	lea ebx, [ebp - 4]
	mov [ebx], eax
	mov eax, dword [ebp + 8]
	push dword eax
	push dword 2
	pop dword ebx
	pop dword eax
	sub eax, ebx
	push dword eax
	call _fibonacci
	add esp, 4
	push dword eax
	pop dword eax
	lea ebx, [ebp - 8]
	mov [ebx], eax
	mov eax, dword [ebp - 4]
	push eax
	mov eax, dword [ebp - 8]
	push eax
	pop dword ebx
	pop dword eax
	add eax, ebx
	push dword eax
	pop eax
	mov esp, ebp
	pop ebp
	ret

main:
	mov dword [__esp], esp
	push dword _x
	call scan_int
	add esp, 4
	push dword [_x]
	call _fibonacci
	add esp, 4
	push dword eax
	pop dword eax
	mov dword [_resultado], eax
	push dword [_resultado]
	call print_int
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
