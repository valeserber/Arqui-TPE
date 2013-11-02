/*********************************************
kasm.h

************************************************/

#include "defs.h"


unsigned int    _read_msw();

void            _lidt (IDTR *idtr);

void        _mascaraPIC1 (byte mascara);  /* Escribe mascara de PIC1 */
void        _mascaraPIC2 (byte mascara);  /* Escribe mascara de PIC2 */

void        _Cli(void);         /* Disable interruptions */
void        _Sti(void);         /* Enable interruptions */

void        _int_08_hand();     /* Timer tick */
void        _int_09_hand();     /* Keyboard */
void        _int_80h_hand();     /* System call */

void        _debug (void);

void        _write(int fd, char *buf, int count); /*write user space*/
void        _read(int fd, char *buf, int count);


