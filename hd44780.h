
#ifndef HD44780_H
#define	HD44780_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "main.h"
#include <stdint.h>

typedef enum{
    COMMAND,
    DATA,
}LCD_REGISTER_TYPE;

#define _ON 1
#define _OFF 0
#define _ONE_LINE 0
#define _TWO_LINES 1
#define LCD_LINE_TWO 0x40 // LCD RAM address for the 2nd line 


#define CURSOR _OFF // Valid options are ON or OFF
#define BLINK _OFF // Valid option are ON or OFF
#define NUMLINES _TWO_LINES // Valid options are ONE_LINE or TWO_LINES

#define RS LATAbits.LATA2
#define EN LATAbits.LATA1
#define D4 LATCbits.LATC0
#define D5 LATCbits.LATC1
#define D6 LATCbits.LATC2
#define D7 LATCbits.LATC3

const char HD44780_CYR[] =
{
   0x41,       //��� 0xC0, ������ '�'
   0xA0,       //��� 0xC1, ������ '�'
   0x42,       //��� 0xC2, ������ '�'
   0xA1,       //��� 0xC3, ������ '�'
   0xE0,       //��� 0xC4, ������ '�'
   0x45,       //��� 0xC5, ������ '�'
   0xA3,       //��� 0xC6, ������ '�'
   0xA4,       //��� 0xC7, ������ '�'
   0xA5,       //��� 0xC8, ������ '�'
   0xA6,       //��� 0xC9, ������ '�'
   0x4B,       //��� 0xCA, ������ '�'
   0xA7,       //��� 0xCB, ������ '�'
   0x4D,       //��� 0xCC, ������ '�'
   0x48,       //��� 0xCD, ������ '�'
   0x4F,       //��� 0xCE, ������ '�'
   0xA8,       //��� 0xCF, ������ '�'
   0x50,       //��� 0xD0, ������ '�'
   0x43,       //��� 0xD1, ������ '�'
   0x54,       //��� 0xD2, ������ '�'
   0xA9,       //��� 0xD3, ������ '�'
   0xAA,       //��� 0xD4, ������ '�'
   0x58,       //��� 0xD5, ������ '�'
   0xE1,       //��� 0xD6, ������ '�'
   0xAB,       //��� 0xD7, ������ '�'
   0xAC,       //��� 0xD8, ������ '�'
   0xE2,       //��� 0xD9, ������ '�'
   0xAD,       //��� 0xDA, ������ '�'
   0xAE,       //��� 0xDB, ������ '�'
   0x62,       //��� 0xDC, ������ '�'
   0xAF,       //��� 0xDD, ������ '�'
   0xB0,       //��� 0xDE, ������ '�'
   0xB1,       //��� 0xDF, ������ '�'
   0x61,       //��� 0xE0, ������ '�'
   0xB2,       //��� 0xE1, ������ '�'
   0xB3,       //��� 0xE2, ������ '�'
   0xB4,       //��� 0xE3, ������ '�'
   0xE3,       //��� 0xE4, ������ '�'
   0x65,       //��� 0xE5, ������ '�'
   0xB6,       //��� 0xE6, ������ '�'
   0xB7,       //��� 0xE7, ������ '�'
   0xB8,       //��� 0xE8, ������ '�'
   0xB9,       //��� 0xE9, ������ '�'
   0xBA,       //��� 0xEA, ������ '�'
   0xBB,       //��� 0xEB, ������ '�'
   0xBC,       //��� 0xEC, ������ '�'
   0xBD,       //��� 0xED, ������ '�'
   0x6F,       //��� 0xEE, ������ '�'
   0xBE,       //��� 0xEF, ������ '�'
   0x70,       //��� 0xF0, ������ '�'
   0x63,       //��� 0xF1, ������ '�'
   0xBF,       //��� 0xF2, ������ '�'
   0x79,       //��� 0xF3, ������ '�'
   0xE4,       //��� 0xF4, ������ '�'
   0x78,       //��� 0xF5, ������ '�'
   0xE5,       //��� 0xF6, ������ '�'
   0xC0,       //��� 0xF7, ������ '�'
   0xC1,       //��� 0xF8, ������ '�'
   0xE6,       //��� 0xF9, ������ '�'
   0xC2,       //��� 0xFA, ������ '�'
   0xC3,       //��� 0xFB, ������ '�'
   0xC4,       //��� 0xFC, ������ '�'
   0xC5,       //��� 0xFD, ������ '�'
   0xC6,       //��� 0xFE, ������ '�'
   0xC7        //��� 0xFF, ������ '�'
};


void lcdNibble(uint8_t nibble);
void initLCD();
void lcdWrite(uint8_t byte, LCD_REGISTER_TYPE type);
void clearLCD();
void lcd_gotoxy(uint8_t x, uint8_t y);
void lcd_putc(char c);
void lcdPrint(const unsigned char *t);
void cgrom_char(uint8_t *symbol, uint8_t address);


#endif	/* XC_HEADER_TEMPLATE_H */

