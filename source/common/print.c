/*
 * File:	print.c
 * Purpose: 
 *
 * Notes:		
 */
#include "common.h"
#include "print.h"

#if(1==PRINT_EN)

#include<stdarg.h>

inline int intpow_10(int n);
/******************************************************************************/
/* return: the number of characters that are printed
 * fmt: parameter format, only "%d(%i), %o, %x(%X), %b(binary), %u, %c, %s" are
 * supported
 * Note: Please be careful to use this function, 
 * if possible, shut down its conditional compilation in the common.h
 */
int mprintf(const char *fmt, ...)
{
    va_list ap;
    int v_int=0;
    char v_char='0';
    unsigned int v_uint=0;
    char *v_charptr=NULL;
    int num=0, i=0, j=0, flag=0;
    
    /*
     * Initialize the pointer to the variable length argument list.
     */
    va_start(ap, fmt);
    
    while(fmt[i])
    {
        num ++;
        if(fmt[i] == '%')
        {
            i ++;
            switch(fmt[i])
            {
            case 'd': case 'i': case 'D': case 'I': // signed Decimal
                v_int = (int)va_arg(ap, int);
                if(v_int<0)
                {
                    uart_putchar('-');
                    v_int = -v_int;
                }
                flag = 0;
                for(j=9; j>=1; j--)
                {
                    if(v_int/intpow_10(j)%10 > 0)
                        flag = 1;
                    if(flag)
                        uart_putchar((uint8)(v_int/intpow_10(j)%10)+'0');
                }
                uart_putchar((uint8)(v_int%10+'0'));
                break;
                
            case 'o': case 'O': // Octal
                v_uint = (unsigned int)va_arg(ap, unsigned int);
                for(j=10; j>=0; j--)
                    uart_putchar((uint8)((v_uint>>(j*3)) & 0x07)+'0');
                break;
                
            case 'x': case 'X': // Hexadecimal
                v_uint = (unsigned int)va_arg(ap, unsigned int);
                for(j=7; j>=0; j--)
                    if(((v_uint>>j*4) & 0x0f) < 10)
                        uart_putchar((uint8)((v_uint>>(j*4)) & 0x0f)+'0');
                    else
                        uart_putchar((uint8)((v_uint>>(j*4)) & 0x0f)-10+'A');
                break;
                
            case 'u': case 'U': // unsigned Decimal
                v_uint = (unsigned int)va_arg(ap, unsigned int);
                flag = 0;
                for(j=9; j>=1; j--)
                {
                    if(v_uint/intpow_10(j)%10 > 0)
                        flag = 1;
                    if(flag)
                        uart_putchar((uint8)(v_uint/intpow_10(j)%10+'0'));
                }
                uart_putchar((uint8)(v_uint%10+'0'));
                break;
                
            case 'b': case 'B': // Binary
                v_uint = (unsigned int)va_arg(ap, unsigned int);
                for(j=31; j>=0; j--)
                    uart_putchar((uint8)((v_uint>>j) & 0x01)+'0');
                break;
                
            case 'c': case 'C': // Character
                v_char = (char)va_arg(ap, unsigned int);
                uart_putchar(v_char);
                break;
                
            case 's': case 'S': // String
                v_charptr = (char*)va_arg(ap, char*);
                uart_putstr(v_charptr);
                break;
            
            default: // %, ect
                v_char = fmt[i];
                uart_putchar(v_char);
            }
        }
        else if(fmt[i] == '\n')
        {
            uart_putchar('\n');
            uart_putchar('\r');
        }
        else
        {
            uart_putchar(fmt[i]);
        }
        i ++;
    }
    
    /*
     * Cleanup the variable length argument list.
     */
    va_end(ap);
    
    return num;
}

/******************************************************************************/
/* return 10^n
 */
inline int intpow_10(int n)
{
    switch(n)
    {
        case 0: return 1;
        case 1: return 10;
        case 2: return 100;
        case 3: return 1000;
        case 4: return 10000;
        case 5: return 100000;
        case 6: return 1000000;
        case 7: return 10000000;
        case 8: return 100000000;
        case 9: return 1000000000;
        default: return 1;
    }
}

/******************************************************************************/
#endif // #if(1==PRINT_EN)