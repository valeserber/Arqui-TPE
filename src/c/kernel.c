#include "../../include/kasm.h"
#include "../../include/defs.h"

DESCR_INT idt[0xFF];    /* 256 entries IDT*/
IDTR idtr;              /* IDTR */


/**********************************************
kmain()
Punto de entrada de código C.
*************************************************/

kmain()
{
    int i,num;

/* Borra la pantalla. */

   k_clear_screen();
   set_cursor(10,0);

/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0,IRQ1 e INT80h. */

    setup_IDT_entry(&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_INT, 0);
    setup_IDT_entry(&idt[0x09], 0x08, (dword)&_int_09_hand, ACS_INT, 0);
    setup_IDT_entry(&idt[0x80], 0x08, (dword)&_int_80h_hand, ACS_INT, 0);

/* Load IDTR */

    idtr.base = 0;
    idtr.base += (dword)&idt;
    idtr.limit = sizeof(idt)-1;

    _lidt (&idtr);
    _Cli();
/* Habilito interrupcion de teclado*/

    _mascaraPIC1(0xFD);
    _mascaraPIC2(0xFF); 
    _Sti();

/* Inicializa el buffer de teclado vacio*/
    buffer_initialize(); 
   
   //int integer;
   //scanf("%d", &integer);
   //printf("%d",integer);
   
    while(1){
	shell_run();
    }
}

