#include "../../include/kasm.h"
#include "../../include/defs.h"

DESCR_INT idt[0xFF];    /* 256 entries IDT*/
IDTR idtr;              /* IDTR */
//BUFFER keyboard_buffer; /* keyboard buffer*/

//int tickpos=640;
extern void _test();
/**********************************************
kmain()
Punto de entrada de código C.
*************************************************/

kmain()
{
    int i,num;

/* Borra la pantalla. */

   k_clear_screen();

/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0    */

    setup_IDT_entry(&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_INT, 0);
    setup_IDT_entry(&idt[0x09], 0x08, (dword)&_int_09_hand, ACS_INT, 0);
    setup_IDT_entry(&idt[0x80], 0x08, (dword)&_int_80h_hand, ACS_INT, 0);

/* Load IDTR */

    idtr.base = 0;
    idtr.base += (dword)&idt;
    idtr.limit = sizeof(idt)-1;

    _lidt (&idtr);
    _Cli();
/* Habilito interrupcion de timer tick*/

  //  _mascaraPIC1(0xFE); //1111 1110 master PIC habilitado el timer tick
    _mascaraPIC1(0xFD);      //1111 1101  habilito el teclado
    _mascaraPIC2(0xFF); //1111 1111 slave PIC
    _Sti();

    buffer_initialize(); 
   // _test();
   //int integer;
   //scanf("%d", &integer);
   //printf("%d",integer);
   // test1();
    while(1){
	shell_run();
    }
}

