;-------------------------------
; tests/test_error.alfa
;   Autor: Carlos Anivarro
;   Autor: Daniel Barahona
;   Autor: David Garitagoitia
;-------------------------------
segment .data
msg_error_division db "**** Division por 0 no permitida", 0
msg_error_indice_vector db "**** Indice fuera de rango", 0
segment .bss
__esp resd 1
; declarar_variable
_x resd 1
; escribir_segmento_codigo
segment .text
global main
extern print_int, print_boolean, print_string, print_blank
extern print_endofline, scan_int, scan_boolean
