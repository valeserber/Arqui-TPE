GLOBAL  _read_msw,_lidt
GLOBAL  _int_08_hand, _int_09_hand, _int_80h_hand
GLOBAL  _read, _write, _registerInfo
GLOBAL  _mascaraPIC1, _mascaraPIC2, _Cli, _Sti
GLOBAL  _debug

EXTERN  int_08
EXTERN  int_09
EXTERN  int_80h


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

_read:
    push    ebp
    mov     ebp, esp
    mov     eax, 3              ;sys_read  number
    mov     ebx, [ebp +8]
    mov     ecx, [ebp + 12]
    mov     edx, [ebp + 16]
    int     80h
    leave
    ret

_write:
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
    pusha
    mov     edi, 4
    mov     eax, 4
    mov     ebx, 0              ; fd = REGOUT
    mov     ecx,   
    int     80h

    
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
    mov     al, 20h              ;Envio de EOI generico al PIC
    out     20h, al
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
    eaxstr db "eax    ",0
    ecxstr db "ecx    ",0
    edxstr db "edx    ",0
    ebxstr db "ebx    ",0
    espstr db "esp    ",0
    ebpstr db "ebp    ",0
    esistr db "esi    ",0
    edistr db "edi    ",0
