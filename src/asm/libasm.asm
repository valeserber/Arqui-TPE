GLOBAL  _read_msw,_lidt
GLOBAL  _int_08_hand, _int_09_hand, _int_80h_hand
GLOBAL  read, write, _registerInfo
GLOBAL  _mascaraPIC1, _mascaraPIC2, _Cli, _Sti
GLOBAL  _debug

EXTERN  int_08
EXTERN  int_09
EXTERN  int_80h
EXTERN  uprintf
EXTERN  printFlags


SECTION .text

_Cli:
    cli                         ;limpia flag de interrupciones
    ret

_Sti:
    sti                         ;habilita interrupciones por flag
    ret

_mascaraPIC1:                   ;Escribe mascara del PIC 1
    push    ebp
    mov     ebp, esp
    mov     ax, [ss:ebp+8]      ;ax = mascara de 16 bits
    out     21h, al
    pop     ebp
    retn

_mascaraPIC2:                   ;Escribe mascara del PIC 2
    push    ebp
    mov     ebp, esp
    mov     ax, [ss:ebp+8]      ;ax = mascara de 16 bits
    out     0A1h, al
    pop     ebp
    retn

_read_msw:
    smsw    ax                  ;Obtiene la Machine Status Word
    retn

_lidt:                          ;Carga el IDTR
    push    ebp
    mov     ebp, esp
    push    ebx
    mov     ebx, [ss: ebp + 6]  ;ds:bx = puntero a IDTR
    rol     ebx,16
    lidt    [ds: ebx]           ;load IDTR
    pop     ebx
    pop     ebp
    retn

read:
    push    ebp
    mov     ebp, esp
    mov     ebx, [ebp+8]
    mov     ecx, [ebp+12]
    mov     edx, [ebp+16]
    mov     eax, 3              ;sys_read  number
    int     80h
    leave
    ret

write:
    push    ebp
    mov     ebp, esp
    mov     ebx, [ebp+8]        ;fd
    mov     ecx, [ebp+12]       ;*buf
    mov     edx, [ebp+16]       ;count
    mov     eax, 4              ;sys_write number
    int     80h
    leave
    ret

_registerInfo:
        push    ebp
        mov     ebp, esp
	pushad
 	mov     ecx, eaxstr 
	mov     eax, [esp+4]
	push    eax
	push    ecx
	call    uprintf
	add     esp, 8
	mov     eax, [esp+8]
	mov     ecx, ecxstr
	push    eax
	push    ecx
	call    uprintf
	add     esp, 8
	mov     eax, [esp+12]
	mov     ecx, edxstr
	push    eax
	push    ecx
	call    uprintf
	add     esp, 8
	mov     eax, [esp+16]
	mov     ecx, ebxstr
	push    eax
	push    ecx
	call    uprintf
	add     esp, 8
	mov     eax, [esp+20]
	mov     ecx, espstr
	push    eax
	push    ecx
	call    uprintf
	add     esp, 8
	mov     eax, [esp+24]
	mov     ecx, ebpstr
	push    eax
	push    ecx
	call    uprintf
	add     esp, 8
	mov     eax, [esp+28]
	mov     ecx, esistr
	push    eax
	push    ecx
	call    uprintf
	add     esp, 8
	mov     eax, [esp+32]
	mov     ecx, edistr
	push    eax
	push    ecx
	call    uprintf
	add     esp, 8
	pushfd
	call    printFlags
	popfd
	popad
        leave
        ret
    
_int_08_hand:                   ;Handler de INT 8 ( Timer tick)
    push    ds
    push    es                  ;Se salvan los registros
    pusha                       ;Carga de DS y ES con el valor del selector
    mov     ax, 10h             ;a utilizar.
    mov     ds, ax
    mov     es, ax
    call    int_08
    mov     al,20h              ;Envio de EOI generico al PIC
    out     20h,al
    popa
    pop     es
    pop     ds
    iret

_int_09_hand:                   ;Keyboard Handler
    push    ds
    push    es                  ;Se salvan los registros
    pusha                       ;Carga de DS y ES con el valor del selector
    mov     ax, 10h             ;a utilizar.
    mov     ds, ax
    mov     es, ax
    in      al, 60h
    push    eax
    call    int_09
    add     esp, 4
    mov     al, 20h 		;End of Interruption code
    out     20h, al             ;Master PIC IO base address
    popa
    pop     es
    pop     ds
    iret

_int_80h_hand:
    push    ebp
    mov     ebp, esp
    push    edi
    push    esi
    push    edx
    push    ecx
    push    ebx
    push    eax
    call    int_80h
    add     esp, 24
    mov     esp, ebp
    pop     ebp
    ret

; Debug para el BOCHS, detiene la ejecució; Para continuar colocar en el BOCHSDBG: set $eax=0
;

_debug:
    push    bp
    mov     bp, sp
    push    ax
vuelve:
    mov     ax, 1
    cmp     ax, 0
    jne     vuelve
    pop     ax
    pop     bp
    retn

section .data
    eaxstr db "eax 0x%x",9, 0 ; 0 to null terminate the string
    regstrlen equ $-eaxstr
    ecxstr db "ecx 0x%x",9,0
    edxstr db "edx 0x%x",10,0 ; 10 = \n in ascii
    ebxstr db "ebx 0x%x",9,0
    espstr db "esp 0x%x",9,0
    ebpstr db "ebp 0x%x",10,0
    esistr db "esi 0x%x",9,0
    edistr db "edi 0x%x",9,0
section .bss
    regBuffer resb 32
