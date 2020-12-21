
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
   0x41,       //код 0xC0, символ 'А'
   0xA0,       //код 0xC1, символ 'Б'
   0x42,       //код 0xC2, символ 'В'
   0xA1,       //код 0xC3, символ 'Г'
   0xE0,       //код 0xC4, символ 'Д'
   0x45,       //код 0xC5, символ 'Е'
   0xA3,       //код 0xC6, символ 'Ж'
   0xA4,       //код 0xC7, символ 'З'
   0xA5,       //код 0xC8, символ 'И'
   0xA6,       //код 0xC9, символ 'Й'
   0x4B,       //код 0xCA, символ 'К'
   0xA7,       //код 0xCB, символ 'Л'
   0x4D,       //код 0xCC, символ 'М'
   0x48,       //код 0xCD, символ 'Н'
   0x4F,       //код 0xCE, символ 'О'
   0xA8,       //код 0xCF, символ 'П'
   0x50,       //код 0xD0, символ 'Р'
   0x43,       //код 0xD1, символ 'С'
   0x54,       //код 0xD2, символ 'Т'
   0xA9,       //код 0xD3, символ 'У'
   0xAA,       //код 0xD4, символ 'Ф'
   0x58,       //код 0xD5, символ 'Х'
   0xE1,       //код 0xD6, символ 'Ц'
   0xAB,       //код 0xD7, символ 'Ч'
   0xAC,       //код 0xD8, символ 'Ш'
   0xE2,       //код 0xD9, символ 'Щ'
   0xAD,       //код 0xDA, символ 'Ъ'
   0xAE,       //код 0xDB, символ 'Ы'
   0x62,       //код 0xDC, символ 'Ь'
   0xAF,       //код 0xDD, символ 'Э'
   0xB0,       //код 0xDE, символ 'Ю'
   0xB1,       //код 0xDF, символ 'Я'
   0x61,       //код 0xE0, символ 'а'
   0xB2,       //код 0xE1, символ 'б'
   0xB3,       //код 0xE2, символ 'в'
   0xB4,       //код 0xE3, символ 'г'
   0xE3,       //код 0xE4, символ 'д'
   0x65,       //код 0xE5, символ 'е'
   0xB6,       //код 0xE6, символ 'ж'
   0xB7,       //код 0xE7, символ 'з'
   0xB8,       //код 0xE8, символ 'и'
   0xB9,       //код 0xE9, символ 'й'
   0xBA,       //код 0xEA, символ 'к'
   0xBB,       //код 0xEB, символ 'л'
   0xBC,       //код 0xEC, символ 'м'
   0xBD,       //код 0xED, символ 'н'
   0x6F,       //код 0xEE, символ 'о'
   0xBE,       //код 0xEF, символ 'п'
   0x70,       //код 0xF0, символ 'р'
   0x63,       //код 0xF1, символ 'с'
   0xBF,       //код 0xF2, символ 'т'
   0x79,       //код 0xF3, символ 'у'
   0xE4,       //код 0xF4, символ 'ф'
   0x78,       //код 0xF5, символ 'х'
   0xE5,       //код 0xF6, символ 'ц'
   0xC0,       //код 0xF7, символ 'ч'
   0xC1,       //код 0xF8, символ 'ш'
   0xE6,       //код 0xF9, символ 'щ'
   0xC2,       //код 0xFA, символ 'ъ'
   0xC3,       //код 0xFB, символ 'ы'
   0xC4,       //код 0xFC, символ 'ь'
   0xC5,       //код 0xFD, символ 'э'
   0xC6,       //код 0xFE, символ 'ю'
   0xC7        //код 0xFF, символ 'я'
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

