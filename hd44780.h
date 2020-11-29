
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

#define RS PORTAbits.RA2
#define EN PORTAbits.RA1
#define D4 PORTCbits.RC0
#define D5 PORTCbits.RC1
#define D6 PORTCbits.RC2
#define D7 PORTCbits.RC3


void lcdNibble(uint8_t nibble);
void initLCD();
void lcdWrite(uint8_t byte, LCD_REGISTER_TYPE type);
void clearLCD();
void lcd_gotoxy(uint8_t x, uint8_t y);
void lcd_putc(char c);
void lcdPrint(const unsigned char *t);
void cgrom_char(uint8_t *symbol, uint8_t address);


#endif	/* XC_HEADER_TEMPLATE_H */

