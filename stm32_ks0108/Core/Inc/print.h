#ifndef _PRINT_H_
#define _PRINT_H_

void print_init(void (*print_char)(char c));
void print(char* fmt, ...);

#endif
