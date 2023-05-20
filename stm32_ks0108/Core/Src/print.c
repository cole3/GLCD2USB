#include <stdarg.h>

void (*printch)(char ch);

static void printdecc(int dec)
{
    if(dec==0) {
        return;
    }
    printdecc(dec/10);
    printch( (char)(dec%10 + '0'));

}

static void printdec(int dec)
{
    if (dec==0) {
        printch( (char)('0'));
    } else {
        printdecc(dec);
    }
}

static void printflt(double flt)
{
    int tmpint = 0;

    tmpint = (int)flt;
    printdec(tmpint);
    printch('.');
    flt = flt - tmpint;
    tmpint = (int)(flt * 1000000);
    printdec(tmpint);
}

static void printstr(char* str)
{
    while(*str) {
        printch(*str++);
    }
}

static void printbin(int bin)
{
    if(bin == 0) {
        printstr("0b");
        return;
    }
    printbin(bin/2);
    printch( (char)(bin%2 + '0'));
}

static void printhex(int hex)
{
    if(hex==0) {
        printstr("0x");
        return;
    }
    printhex(hex/16);
    if(hex < 10) {
        printch((char)(hex%16 + '0'));
    } else {
        printch((char)(hex%16 - 10 + 'a' ));
    }
}

void print(char* fmt, ...)
{
    double vargflt = 0;
    int  vargint = 0;
    char *vargpch;
    char vargch = 0;
    char *pfmt;
    va_list vp;

    va_start(vp, fmt);
    pfmt = fmt;

    while(*pfmt) {
        if(*pfmt == '%') {
            switch(*(++pfmt)) {
            case 'c':
                vargch = va_arg(vp, int);
                printch(vargch);
                break;
            case 'd':
            case 'i':
                vargint = va_arg(vp, int);
                printdec(vargint);
                break;
            case 'f':
                vargflt = va_arg(vp, double);
                printflt(vargflt);
                break;
            case 's':
                vargpch = va_arg(vp, char*);
                printstr(vargpch);
                break;
            case 'b':
            case 'B':
                vargint = va_arg(vp, int);
                printbin(vargint);
                break;
            case 'x':
            case 'X':
                vargint = va_arg(vp, int);
                printhex(vargint);
                break;
            case '%':
                printch('%');
                break;
            default:
                break;
            }
            pfmt++;
        } else {
            if (*pfmt == '\n') {
                printch('\r');
            }
            printch(*pfmt++);
        }
    }
    va_end(vp);
}

void print_init(void (*print_char)(char c))
{
    printch = print_char;
}
