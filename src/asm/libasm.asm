GLOBAL  _read_msw,_lidt
GLOBAL  read, write, _test
GLOBAL  _mascaraPIC1, _mascaraPIC2, _Cli, _Sti
GLOBAL  _debug
GLOBAL _opencd
EXTERN printStatus
GLOBAL _printError
EXTERN printCapacity
GLOBAL _closecd
GLOBAL set_cursor
GLOBAL _infocd

SECTION .text

_Cli:
    cli                         ;Clears the Interrupt Enable flag
    ret

_Sti:
    sti                         ;Enables the IE flag
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
    mov     ax, [ss:ebp+8]      ;ax = 16 bit mask
    out     0A1h, al
    pop     ebp
    retn

_read_msw:
    smsw    ax                  ;Get machine status word
    retn

_lidt:                          ;Load IDTR
    push    ebp
    mov     ebp, esp
    push    ebx
    mov     ebx, [ss:ebp+6]     ;ds:bx = IDTR pointer
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

; Set cursor position (text mode 80x25)
; @param BL The row on screen, starts from 0
; @param BH The column on screen, starts from 0
; SOURCE: http://wiki.osdev.org/Text_Mode_Cursor

set_cursor:
    push    ebp
    mov     ebp,esp
    pushf
    pushad

    ;unsigned short position = (row*80) + col;
    ;AX will contain 'position'

    mov     bl, byte[ebp + 8]
    mov     bh, byte[ebp + 12]
    mov     ax, bx
    and     ax, 0ffh            ;set AX to 'row'
    mov     cl, 80
    mul     cl                  ;row*80

    mov     cx, bx
    shr     cx, 8               ;set CX to 'col'
    add     ax, cx              ;+ col
    mov     cx, ax              ;store 'position' in CX

    ;cursor LOW port to vga INDEX register
    mov     al, 0fh
    mov     dx, 3d4h            ;VGA port 3D4h
    out     dx, al

    mov     ax, cx              ;restore 'postion' back to AX
    mov     dx, 3d5h            ;VGA port 3D5h
    out     dx, al              ;send to VGA hardware

    ;cursor HIGH port to vga INDEX register
    mov     al, 0eh
    mov     dx, 3d4h            ;VGA port 3D4h
    out     dx, al

    mov     ax, cx              ;restore 'position' back to AX
    shr     ax, 8               ;get high byte in 'position'
    mov     dx, 3d5h            ;VGA port 3D5h
    out     dx, al              ;send to VGA hardware
    popad
    popf
    mov     esp,ebp
    pop     ebp
    ret

_opencd:
    jmp     checkIDEtoOpen
primaryIDE:
    call    _pollPrimUntilNotBusy
    mov     dx, 0x1f6
    mov     al, 0x10
    out     dx, al
    mov     dx, 0x1f1
    xor     al, al
    out     dx, al
    mov     dx, 0x3f6
    mov     al, 00001010b
    out     dx, al
    mov     dx, 0x1f7
    mov     al, 0xa0
    out     dx, al
    call    _pollPrimUntilNotBusy
    call    _pollPrimUntilDataRequest
    mov     dx, 0x1f0
    mov     ax, 0x1E
    out     dx, ax
    xor     ax, ax
    out     dx, ax
    out     dx, ax
    out     dx, ax
    out     dx, ax
    out     dx, ax
    call    _pollPrimUntilNotBusy
    mov     dx, 0x1f7
    mov     al, 0xA0
    out     dx, al
    call    _pollPrimUntilNotBusy
    call    _pollPrimUntilDataRequest
    mov     dx, 0x1f0
    mov     ax, 0x1b
    out     dx, ax
    xor     ax, ax
    out     dx, ax
    mov     ax, 2
    out     dx, ax
    xor     ax, ax
    out     dx, ax
    out     dx, ax
    out     dx, ax
    call    _pollPrimUntilNotBusy
exit:
    ret

secondaryIDE:
    call    _pollSecUntilNotBusy
    mov     dx, 0x176
    mov     al, 0x10
    out     dx, al
    mov     dx, 0x171
    xor     al, al
    out     dx, al
    mov     dx, 0x376
    mov     al, 00001010b
    out     dx, al
    mov     dx, 0x177
    mov     al, 0xa0
    out     dx, al
    call    _pollSecUntilNotBusy
    call    _pollSecUntilDataRequest
    mov     dx, 0x170
    mov     ax, 0x1e
    out     dx, ax
    xor     ax, ax
    out     dx, ax
    out     dx, ax
    out     dx, ax
    out     dx, ax
    out     dx, ax
    call    _pollSecUntilNotBusy
    mov     dx, 0x177
    mov     al, 0xa0
    out     dx, al
    call    _pollSecUntilNotBusy
    call    _pollSecUntilDataRequest
    mov     dx, 0x170
    mov     ax, 0x1b
    out     dx, ax
    xor     ax, ax
    out     dx, ax
    mov     ax, 2
    out     dx, ax
    xor     ax, ax
    out     dx, ax
    out     dx, ax
    out     dx, ax
    call    _pollSecUntilNotBusy
    ret

checkIDEtoOpen:
    mov     dx, 0x1f7
    mov     edi, 0xffffffff
cycle1:
    dec     edi
    jz      trySecondary
    in      al, dx
    and     al, 0x80
    jz      cycle1
    jmp     primaryIDE
trySeconday:
    mov     dx, 0x177
    mov     edi, 0xffffffff
cycle2:
    dec     edi
    jz      exit
    in      al, dx
    and     al, 0x80
    jz      cycle2
    jmp     secondaryIDE

checkIDEtoClose:
    mov     dx, 0x1f7
    mov     edi, 0xffffffff
cycle3:
    dec     edi
    jz      tryToCloseSecondary
    in      al, dx
    and     al, 0x80
    jz      cycle3
    jmp     closePrimaryIDE
tryToCloseSecondary:
    mov     dx, 0x177
    mov     edi, 0xffffffff
cycle4:
    dec     edi
    jz      exit
    in      al, dx
    and     al, 0x80
    jz      cycle4
    jmp     closeSecondaryIDE


_closecd:
    jmp checkIDEtoClose
closePrimaryIDE:
    call    _pollPrimUntilNotBusy
    mov     al, 0x10
    mov     dx, 0x1f6
    out     dx, al
    mov     dx, 0x1f7
    mov     al, 0xa0
    out     dx, al

    mov     ecx, 0xffff
waitloop2:
    loopnz  waitloop2

    call    _pollPrimUntilNotBusy
    call    _pollPrimUntilDataRequest

    mov     dx, 0x1f0
    mov     ax, 0x1b        ;Start/Stop Unit command
    out     dx, ax
    xor     ax, ax
    out     dx, ax
    mov     ax, 3           ;LoEj & Start bits enabled (Eject disc if possible)
    out     dx, ax
    xor     ax, ax
    out     dx, ax
    out     dx, ax
    out     dx, ax
    call    _pollPrimUntilNotBusy
    ret

closeSecondaryIDE:
    call    _pollSecUntilNotBusy
    mov     al, 0x10
    mov     dx, 0x176
    out     dx, al
    mov     dx, 0x177
    mov     al, 0xa0
    out     dx, al

    mov     ecx, 0xffff
waitloop6:
    loopnz  waitloop6

    call    _pollSecUntilNotBusy
    call    _pollSecUntilDataRequest

    mov     dx, 0x170
    mov     ax, 0x1b        ;Start/Stop Unit command
    out     dx, ax
    xor     ax, ax
    out     dx, ax
    mov     ax, 3           ;LoEj & Start bits enabled (Eject disc if possible)
    out     dx, ax
    xor     ax, ax
    out     dx, ax
    out     dx, ax
    out     dx, ax
    call    _pollSecUntilNotBusy
    ret

_infocd:
    call    _pollPrimUntilNotBusy
    xor     ax, 0x10
    mov     dx, 0x1f6
    out     dx, al              ;Select slave device

    mov     ecx, 0xffff
waitloop3:
    loopnz  waitloop3

    mov     dx, 0x1f1
    out     dx, al              ;Set Features register to 0
    mov     dx, 0x1f4
    mov     ax, 0x08
    out     dx, ax              ;Set LBA1 register to 0x0008
    mov     dx, 0x1f5
    out     dx, ax              ;Set LBA2 register to 0x0008
    mov     dx, 0x1f7
    mov     al, 0xa0
    out     dx, al              ;Send packet command

    mov     ecx, 0xffff
waitloop4:
    loopnz  waitloop4

    call    _pollPrimUntilNotBusy
    call    _pollPrimUntilDataRequest
    mov     dx, 0x1f0
    mov     al, 0x25            ;Read capacity command
    out     dx, al
    xor     ax, ax
    out     dx, al
    out     dx, ax
    out     dx, ax
    out     dx, ax
    out     dx, ax
    out     dx, ax
    call    _pollPrimUntilNotBusy

    mov     ecx, 4
    xor     ebx, ebx
getCapacityInfo:
    in      ax, dx
    mov     [array+ebx], ax
    add     ebx, 2
    loopnz  getCapacityInfo

    mov     eax, [array]
    mov     ebx, [array+4]
    push    ebx
    push    eax
    call    printCapacity
    add     esp, 8
    ret

_pollPrimUntilNotBusy:
    mov     dx, 0x1f7
    ;mov     edi, 0xffffffff
cycleBSY:
    ;dec     edi
    ;jz      exitBSY     ;If it's taking too long, abort
    in      al, dx      ;Read from status register
    and     al, 0x80    ;Check leftmost bit to see if drive is busy
    jnz     cycleBSY    ;While busy, keep querying until drive is available
exitBSY:
    ret

_pollPrimUntilDataRequest:
    mov     dx, 0x1f7
    ;mov     edi, 0x1fffff
cycleDRQ:
    ;dec     edi
    ;jz      exitDRQ
    in      al, dx
    and     al, 0x08
    jz      cycleDRQ
exitDRQ:
    ret

_pollSecUntilNotBusy:
    mov     dx, 0x177
    ;mov     edi, 0xffffffff
cycleBSY2:
    ;dec     edi
    ;jz      exitBSY
    in      al, dx
    and     al, 0x80
    jnz     cycleBSY2
exitBSY2:
    ret

_pollSecUntilDataRequest:
    mov     dx, 0x177
    ;mov     edi, 0x1fffff
cycleDRQ2:
    ;dec     edi
    ;jz      exitDRQ
    in      al, dx
    and     al, 0x08
    jz      cycleDRQ2
exitDRQ:
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

section .bss
    array resb 8
