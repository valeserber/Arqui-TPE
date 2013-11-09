#include "../include/defs.h"

/**********************************
*
*  Kernel
*
***********************************/

#ifndef _kernel_
#define _kernel_

#define OS_PID  0

int (*player)(void);

typedef int size_t;
typedef short int ssize_t;
typedef enum eINT_80 {WRITE=0, READ} tINT_80;
typedef enum eUSER {U_KERNEL=0, U_NORMAL} tUSERS;

/* __write
*
* Recibe como parametros:
* - File Descriptor
* - Buffer del source
* - Cantidad
*
**/
ssize_t __write(int fd, const void * buf, size_t count);

/* __read
*
* Recibe como parametros:
* - File Descriptor
* - Buffer a donde escribir
* - Cantidad
*
**/
ssize_t __read(int fd, void *buf, size_t count);

#endif
