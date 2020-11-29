
#include "eeprom.h"


void write_eep( unsigned char address, unsigned char data )
{
    while( EECON1bits.WR  )     
    {}
    // EEPROM_WRITE( address, data ); �� ������ ��� PIC18!!!!!
  
    EEADR = address;
    EEDATA = data;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS  = 0;
    EECON1bits.WREN  = 1;
    INTCONbits.GIE   = 0;
    // required sequence start
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR    = 1;
    // required sequence end
    INTCONbits.GIE   = 1;
}

unsigned char read_eep( unsigned short address )
{
    while( EECON1bits.WR  )     
    {}
    
    EEADR = address;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS  = 0;
    EECON1bits.RD    = 1;
    return( EEDATA );
}