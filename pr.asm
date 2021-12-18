segment .data
msg_error_division db "Cant divide by 0", 0
msg_error_indice_vector db "Index out of range", 0
segment .bss
__esp resd 1
_x resd 1
_x resd 1
segment .text
global main
extern print_int, print_boolean, print_string, print_blank
extern print_endofline, scan_int, scan_boolean
main:
mov dword [__esp], esp
pop dword eax
pop dword ebx
mov dword [eax], ebx
lea eax, [ebp - 8]
push dword eax
call print_int
add esp, 4
call print_endofline
jmp near fin ; termina sin errores
fin_error_division: ; división por cero
push dword msg_error_division
call print_string
add esp, 4
call print_endofline
jmp near fin ; salta al final
fin_indice_fuera_rango: ; error de índice fuera de rango
push dword msg_error_indice_vector
call print_string
add esp, 4
call print_endofline
jmp near fin ; salta al final
fin:
call print_endofline
mov esp, [__esp] ; recupera el puntero de pila
ret
