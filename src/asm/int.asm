GLOBAL  _int_08_hand, _int_09_hand, _int_80h_hand
GLOBAL  _registerInfo
EXTERN  uprintf
EXTERN  printFlags
EXTERN  int_08
EXTERN  int_09
EXTERN  int_80h

section .text

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
    push    ss
    push    ds
    push    es                  
    push    fs
    push    gs
    pushad                      
    call    _saveRegisters
    mov     ax, 10h             
    mov     ds, ax
    mov     es, ax
    in      al, 60h
    push    eax
    call    int_09
    add     esp, 4
    mov     al, 20h             ;End of Interruption code
    out     20h, al             ;Master PIC IO base address
    popad
    add     esp, 8
    pop     es
    pop     ds
    add     esp, 4
    iret

_saveRegisters:
    xor     eax, eax                ;counter
    mov     ecx, esp                ;ecx apunta al comienzo del stack
cycle:
    add     ecx, 4                  ;stack[ebx]
    mov     edx, [ecx]              ;edx = valor del registro
    mov     [registers+eax], edx
    add     eax, 4
    cmp     eax, 60 
    jne     cycle
    ret

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
    mov     esp, ebp
    pop     ebp
    iret

_registerInfo:
    push    ebp
    mov     ebp, esp
    mov     ecx, eaxstr 
    mov     eax, [registers+28]
    push    eax
    push    ecx
    call    uprintf
    add     esp, 8
    mov     eax, [registers+24]
    mov     ecx, ecxstr
    push    eax
    push    ecx
    call    uprintf
    add     esp, 8
    mov     eax, [registers+20]
    mov     ecx, edxstr
    push    eax
    push    ecx
    call    uprintf
    add     esp, 8
    mov     eax, [registers+16]
    mov     ecx, ebxstr
    push    eax
    push    ecx
    call    uprintf
    add     esp, 8
    mov     eax, [registers+12]
    mov     ecx, espstr
    push    eax
    push    ecx
    call    uprintf
    add     esp, 8
    mov     eax, [registers+8]
    mov     ecx, ebpstr
    push    eax
    push    ecx
    call    uprintf
    add     esp, 8
    mov     eax, [registers+4]
    mov     ecx, esistr
    push    eax
    push    ecx
    call    uprintf
    add     esp, 8
    mov     eax, [registers]
    mov     ecx, edistr
    push    eax
    push    ecx
    call    uprintf
    add     esp, 8
    mov     eax, [registers+60]
    push    eax
    call    printFlags
    add     esp, 4
    mov     eax, [registers+32]
    mov     ecx, gsstr
    push    eax
    push    ecx
    call    uprintf
    add     esp, 8
    mov     ecx, fsstr 
    mov     eax, [registers+36]
    push    eax
    push    ecx
    call    uprintf
    add     esp, 8
    mov     ecx, esstr 
    mov     eax, [registers+40]
    push    eax
    push    ecx
    call    uprintf
    add     esp, 8
    mov     ecx, dsstr 
    mov     eax, [registers+44]
    push    eax
    push    ecx
    call    uprintf
    add     esp, 8
    mov     ecx, ssstr 
    mov     eax, [registers+48]
    push    eax
    push    ecx
    call    uprintf
    add     esp, 8
    mov     ecx, csstr 
    mov     eax, [registers+56]
    push    eax
    push    ecx
    call    uprintf
    add     esp, 8
    mov     ecx, eipstr
    mov     eax, [registers+52]
    push    eax
    push    ecx
    call    uprintf
    leave
    ret

section .data
    eaxstr db "eax 0x%x",9, 0 ; 0 to null terminate the string
    ecxstr db "ecx 0x%x",9,0
    edxstr db "edx 0x%x",10,0 ; 10 = \n in ascii
    ebxstr db "ebx 0x%x",9,0
    espstr db "esp 0x%x",9,0
    ebpstr db "ebp 0x%x",10,0
    esistr db "esi 0x%x",9,0
    edistr db "edi 0x%x",9,0
    gsstr  db "gs  0x%x",9,0
    fsstr  db "fs  0x%x",9,0
    esstr  db "es  0x%x",9,0
    dsstr  db "ds  0x%x",10,0
    ssstr  db "ss  0x%x",9,0
    csstr  db "cs  0x%x",9,0
    eipstr db "eip 0x%x",0

section .bss
    registers resb 70
