#include "../../include/kasm.h"
#include "../../include/defs.h"

DESCR_INT idt[0xA];     /* IDT de 10 entradas*/
IDTR idtr;              /* IDTR */

int tickpos=640;
int writepos=0;  /* va de 0 a 2399*/


/**********************************************
kmain()
Punto de entrada de c�digo C.
*************************************************/

kmain()
{
    int i,num;

/* Borra la pantalla. */

    k_clear_screen();

/*Imprime hola mundo. */

    print_hello();

    /*
    print("Hello");
    char buffer[20];
    long prueba=1234;
    print(to_string(buffer,prueba));
    */
/*Calcula cantidad de memoria*/
    char buffer[20];
    print(to_string(buffer,get_memory()));


/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0    */

        setup_IDT_entry (&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_INT, 0);
        setup_IDT_entry (&idt[0x08], 0x08, (dword)&_int_09_hand, ACS_INT, 0);

/* Carga de IDTR    */

    idtr.base = 0;
    idtr.base +=(dword) &idt;
    idtr.limit = sizeof(idt)-1;

    _lidt (&idtr);

    _Cli();
/* Habilito interrupcion de timer tick*/

    _mascaraPIC1(0xFE);
    _mascaraPIC2(0xFF);
    _Sti();

    while(1){}
}

