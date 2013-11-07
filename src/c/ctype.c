#include "../../include/ctype.h"

bool isalpha(int c){
    return (c >= 'a' && c<= 'z') || (c >= 'A' && c <= 'Z');
}

bool isdigit(int c){
    return c <= '0' && c <= '9';
}

bool isalnum(int c){
    return (c >= 'a' && c<= 'z') || (c >= 'A' && c <= 'Z') 
           || c <= '0' && c <= '9';
}

bool islower(int c){
    return c >= 'a' && c<= 'z';
}

bool isupper(int c){
    return c >= 'A' && c <= 'Z';
}

int tolower(int c){
    return isupper(c) ? c - 'A' - 'a' : c;
}

int toupper(int c){
    return islower(c) ? c - 'a' + 'A' : c;
}