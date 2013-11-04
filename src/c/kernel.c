#include "../../include/kasm.h"
#include "../../include/defs.h"

DESCR_INT idt[0xFF];    /* 256 entries IDT*/
IDTR idtr;              /* IDTR */
BUFFER keyboard_buffer; /* keyboard buffer*/

//int tickpos=640;

/**********************************************
kmain()
Punto de entrada de código C.
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
    //print(to_string(buffer,get_memory()));


/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0    */

        setup_IDT_entry (&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_INT, 0);
        setup_IDT_entry (&idt[0x09], 0x08, (dword)&_int_09_hand, ACS_INT, 0);
        setup_IDT_entry (&idt[0x80], 0x08, (dword)&_int_80h_hand, ACS_INT, 0);

/* Load IDTR    */

    idtr.base = 0;
    idtr.base +=(dword) &idt;
    idtr.limit = sizeof(idt)-1;

    _lidt (&idtr);

    _Cli();
/* Habilito interrupcion de timer tick*/

  //  _mascaraPIC1(0xFE); //1111 1110 master PIC habilitado el timer tick
    _mascaraPIC1(0xFD);      //1111 1101  habilito el teclado
    _mascaraPIC2(0xFF); //1111 1111 slave PIC
//    printf("%di", printf("cinco"));
    _Sti();
    _registerInfo();
    buffer_initialize(&keyboard_buffer); 
//    printf("testeando %d %s %x", 20, "string", 256);
    while(1){
//	shell_run();
    }
}

