GLOBAL  _read_msw,_lidt
GLOBAL  read, write, _test
GLOBAL  _mascaraPIC1, _mascaraPIC2, _Cli, _Sti
GLOBAL  _debug

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

;_test:
;    mov    eax, 0xCAFE
;    mov    ebx, 0x0FE0
;    mov    ecx, 0x0FEA
;    mov    edx, 0x0CE0
;    mov    edi, 0x0DAF
;    mov    esi, 0x0CCC
;    pushad
;    ;add    eax, eax
;    pushfd
;    call  _saveRegisters
;    call  _registerInfo
;    popfd
;    popad
;    ret

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
