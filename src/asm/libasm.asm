GLOBAL  _read_msw,_lidt
GLOBAL  read, write, _test
GLOBAL  _mascaraPIC1, _mascaraPIC2, _Cli, _Sti
GLOBAL  _debug
GLOBAL _opencd
EXTERN printStatus
GLOBAL _printError
EXTERN printNum
GLOBAL _closecd

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



_opencd:

call _pollBSY

mov ax, 00h
mov dx, 0x1F6
out dx, ax ; al puerto 1f6 mando un cero

mov dx, 0x1F1
mov ax, 0
out dx, ax ; al puerto 1f1 mando un cero

;call _pollDRDY

mov dx, 0x1F7
mov ax, 0xA0
out dx, ax ; al puerto 1f7 mando el A0

; puede pasar q tarde un cacho

mov ebx, 65000
loop9:
dec ebx
cmp ebx, 0
jne loop9

call _pollBSY
call _pollDRQ

mov dx, 0x1F0
mov al, 0x1E
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

call _pollBSY
call _pollDRDY

mov dx, 0x1F7
mov ax, 0xA0
out dx, ax

call _pollBSY
call _pollDRQ

mov dx, 0x1f0
mov al, 1Bh
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 2
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

;mov eax, 0
;mov dx, 0x1f7
;in eax, dx
;push eax
;call printStatus
;pop eax

call _pollBSY
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;pollDRDY no hace falta
;;pollbsy es fijarse si busy no esta en 1
;;polldrq es fijarse que drq este en 1
;;0x1E y todo cero es para habilitar la lectora
;;para cerrar la lectora no hace falta 0x1E
;; solo hace falta 0x1B
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_pollBSY:
MOV DX, 1F7h
LOOP1:
IN AL, DX
AND AL, 0x80
JNE LOOP1
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_pollDRDY:
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_pollDRQ:
MOV DX, 1F7h
LOOP4:
IN AL, DX
AND AL,0x08
JE LOOP4
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


_printError:
mov dx, 0x1F1
mov ax, 0
in al, dx
push eax
call printNum
pop eax
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_closecd:

call _pollBSY

mov ax, 00h
mov dx, 0x1F6
out dx, ax ; al puerto 1f6 mando un cero

mov dx, 0x1F1
mov ax, 0
out dx, ax ; al puerto 1f1 mando un cero

;call _pollDRDY

mov dx, 0x1F7
mov ax, 0xA0
out dx, ax ; al puerto 1f7 mando el A0

; puede pasar q tarde un cacho

mov ebx, 65000
loop97:
dec ebx
cmp ebx, 0
jne loop97

call _pollBSY
call _pollDRQ

mov dx, 0x1F0

mov al, 0x1E
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

call _pollBSY
call _pollDRDY

mov dx, 0x1F7

mov ax, 0xA0
out dx, ax

call _pollBSY
call _pollDRQ

mov dx, 0x1f0
mov al, 1Bh
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 3
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov eax, 0
mov dx, 0x1f7
in eax, dx
push eax
call printStatus
pop eax

call _pollBSY
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_infocd:

call _pollBSY

mov ax, 00h
mov dx, 0x1F6
out dx, ax ; al puerto 1f6 mando un cero

mov dx, 0x1F1
mov ax, 0
out dx, ax ; al puerto 1f1 mando un cero

;call _pollDRDY
mov dx, 0x1F7
mov ax, 0xA0
out dx, ax ; al puerto 1f7 mando el A0

; puede pasar q tarde un cacho
mov ebx, 65000
loop982:
dec ebx
cmp ebx, 0
jne loop982

call _pollBSY
call _pollDRQ

mov dx, 0x1F0
mov al, 0x1E
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

call _pollBSY
call _pollDRDY

mov dx, 0x1F7
mov ax, 0xA0
out dx, ax

call _pollBSY
call _pollDRQ

mov dx, 0x1f0
mov al, 1Bh
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 2
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov al, 0
out dx, al

mov eax, 0
mov dx, 0x1f7

in eax, dx
push eax
call printStatus
pop eax

call _pollBSY
ret

;openCD:
;    mov     cx, 6       ;do this 6 times because it's 6 word writes (a word is 2 bytes) 
;    mov     ds, seg buff 
;    mov     si, OFFSET buff 
;                        ;DS:SI now points to the buffer which contains our ATAPI command packet 
;    cld                 ;clear direction flag so SI gets incremented, not decremented ;
;
;COMPACKLOOP: ;command packet sending loop 
;    mov     dx, 170h    ;data register ;Because we're going to need to write a word (2 bytes), we can't just use an 
;                        ;8-bit register like AL. For this operation, we'll need to use the full width 
;                        ;of the 16-bit accumulator AX. We'll use the LODSW opcode, which loads AX 
;                        ;with whatever DS:SI points to. Not only this, but if the direction flag is 
;                        ;cleared (which we did a few lines above with the CLD instruction), LODSW 
;                        ;also auto-increments SI. 
;    lodsw 
;    out     dx, ax      ;send the current word of the command packet!!! 
;                        ; manda una palabra del buff, su paquete de comando 
;                        ;; escribirle 6 veces en 
;                        ;donde tengo las direcciones de memoria si tngo en amster y slave 
;                        ;te mando buff mas indice y voy aumentando el indice en 2, 
;                        ;entre cada ciclo tiene q haber un tiempo de descanso 
;                        ;para recomponerse 
;    mov     dx, 3F6h 
;                        ;Alternate Status Register 
;                        ;IN AL, DX ;wait one I/O cycle 
;    loopnz COMPACKLOOP  ;loop using ecx as a counter

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

;section .bss
;    buffer db 1Bh, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0
