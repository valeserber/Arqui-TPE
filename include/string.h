#ifndef _STRING_H_
#define _STRING_H_

#define NULL ((void*)0)
/*
 * Compares the C string s to the string t, character by character until
 * the characters differ or a terminating null-character is reached.
 * Returns zero if both strings are equal, greater than zero if the first
 * character that does not match has a greater value in s than in t, or
 * less than zero on the contrary.
 */
size_t strcmp(const char *s, const char *t);

/*
 * Returns the length of the C string str, counting from the first element
 * pointed to by the argument pointer, until a terminating null-character
 * is reached.
 */
size_t strlen(const char * str);

/*
 * Converts a value of type long to an array, in the base specified by the
 * radix parameter. radix must be a value between 2 and 16.
 */
char* ltoa(long value, char* buffer, int radix);

/*
 * Parses the C string str interpreting its content as an integral number,
 * which is returned as a value of type int. The function discards as many
 * whitespace characters (as in isspace) as necessary until the first
 * non-whitespace character is found. Then, starting from this character,
 * takes optional initial plus or minus sign followed by as many base-10
 * digits as possible, and interprets them as numerical value.
 * If the first sequence of non-whitespace characters in str is not a valid
 * integral number, or if no such sequence exists because either str is empty
 * or it contains only whitespace characters, no conversion is performed and
 * zero is returned
 */
int atoi(const char * str);

/*
 * Converts a string representing a hexadecimal number to int
 */
int atohexa(char * buffer);

int hexatoint(char n);

#endif
