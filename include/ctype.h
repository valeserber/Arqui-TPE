#include "defs.h"

#ifndef _CTYPE_H_
#define _CTYPE_H_
/* 
 * Checks whether c is an alphabetic letter
 */
bool isalpha(int c);

/* 
 * Checks whether c is a decimal digit character
 */
bool isdigit(int c);

/* 
 * Checks whether c is a hexadecimal digit character
 */
bool isxdigit(int c);

/* 
 * Checks whether c is a decimal digit or an uppercase or lowercase letter
 */
bool isalnum(int c);

/* 
 * Checks whether c is a white-space character. For the "C" locale,
 * white-space characters are any of: ' ', '\t', '\n', '\v', '\f', or '\r' 
 */
bool isspace(int c);

/* 
 * Checks whether c is a lowercase letter
 */
bool islower(int c);

/* 
 * Checks whether c is an uppercase letter
 */
bool isupper(int c);

/* 
 * Converts c to its lowercase equivalent if c is an uppercase letter and 
 * has a lowercase equivalent. If no such conversion is possible, the value 
 * returned is c unchanged.
 */
int tolower(int c);

/* 
 * Converts c to its uppercase equivalent if c is a lowercase letter and 
 * has an uppercase equivalent. If no such conversion is possible, the value 
 * returned is c unchanged.
 */
int toupper(int c);

#endif
