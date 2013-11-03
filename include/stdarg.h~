/*
* stdarg.h
*
* Provides facilities for stepping through a list of function arguments of
* an unknown number and type.
*
*/

#ifndef _STDARG_H_
#define _STDARG_H_
typedef char* va_list;


/*
* Amount of space required in an argument list (ie. the stack) for an
* argument of type t.
*/
#define __va_argsiz(t)        \
        (((sizeof(t) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))


/*
* For a simple minded compiler this should work (it works in GNU too for
* vararg lists that don't follow shorts and such).
*/
#define va_start(ap, pN)        \
        ((ap) = ((va_list) (&pN) + __va_argsiz(pN)))

/*
* End processing of variable argument list. In this case we do nothing.
*/
#define va_end(ap)        ((void)0)


/*
* Increment ap to the next argument in the list while returing a
* pointer to what ap pointed to first, which is of type t.
*
* We cast to void* and then to t* because this avoids a warning about
* increasing the alignment requirement.
*/

#define va_arg(ap, t)                                        \
         (((ap) = (ap) + __va_argsiz(t)),                \
         *((t*) (void*) ((ap) - __va_argsiz(t))))

#endif /* not _STDARG_H_ */
