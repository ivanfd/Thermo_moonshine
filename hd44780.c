/* Бібліотека роботи з LCD
  на контролері HD44780.
  4 - біт
  Автор: Ivan_fd
  V1.0 від 30/8/2017
 */

#include "hd44780.h"

void initLCD() {
    RS = 0;
    EN = 0;

    __delay_ms(10); // wait 10ms for lcd internal initialization
    __delay_ms(10);
    __delay_ms(10);
    __delay_ms(10);


    // First send the HIGH nibble of the Function set
    lcdNibble(0b0011); // Function set - Interface defaults to 8-bit mode
    __delay_ms(5);
    lcdNibble(0b0011); // Function set - Interface defaults to 8-bit mode
    __delay_ms(5);
    lcdNibble(0b0011); // Function set - Interface defaults to 8-bit mode
    __delay_ms(5);
    lcdNibble(0b0010); // Now set the interface to 4-bit mode
    __delay_ms(5);


    lcdWrite(((0b0010 << 4) | (NUMLINES << 3)), COMMAND); // 0x28 = 4-bit, 2-line, 5x8 font size
    __delay_ms(5);
    lcdWrite(((0b1100) | (CURSOR << 1) | (BLINK << 0)), COMMAND); // 0x0C = Turn ON display, no cursor, no blinking
    __delay_ms(8);
    clearLCD(); // Clear the screen
    __delay_ms(5);
    lcdWrite(0x06, COMMAND); // Move from left-to-right, no shifting
    __delay_ms(5);
    clearLCD();

    RS = 1;

}

void clearLCD() {
    lcdWrite(0x01, COMMAND);
    __delay_ms(2);
}

void lcdWrite(uint8_t byte, LCD_REGISTER_TYPE type) {
    if (type == COMMAND) // check expected data type
        RS = 0; // sending special commands (see hd44780 datasheet)
    else
        RS = 1; // assume actual data

    __delay_us(100);

    lcdNibble(byte >> 4); // send higher 4-bits
    lcdNibble(byte & 0x0F); // send lower 4-bits

}

void lcdNibble(uint8_t nibble) {
    D4 = (nibble & 0x01) ? 1 : 0;
    D5 = (nibble & 0x02) ? 1 : 0;
    D6 = (nibble & 0x04) ? 1 : 0;
    D7 = (nibble & 0x08) ? 1 : 0;

    // Now strobe
    EN = 1;
    __delay_us(100);
    EN = 0;
    __delay_us(100);
}

void lcd_gotoxy(uint8_t x, uint8_t y) {
    uint8_t address;

    if (y != 1)
        address = LCD_LINE_TWO;
    else
        address = 0;

    address += x - 1;
    lcdWrite(0x80 | address, COMMAND);
} 

//----------------------------- 

void lcd_putc(char c) {

            lcdWrite(c, DATA);
} 


void lcdPrint(const unsigned char *t){
    while(*t != '\0'){
        switch (*t) {
        case '\f':
            lcdWrite(1, COMMAND);
            __delay_ms(2);
            break;

        case '\n':
            lcd_gotoxy(1, 2);
            break;

        case '\b':
            lcdWrite(0x10, COMMAND);
            break;

        default:
            lcdWrite(*t, DATA);
            break;
    }
       *t++; 
        
        //lcdWrite(*t++, DATA);
    }
}

void cgrom_char(uint8_t *symbol, uint8_t address) {
    uint8_t i;
    lcdWrite(0x40 | (address * 8), COMMAND);
    for (i = 0; i < 8; i++)
        lcdWrite(*symbol++, DATA);
}

