
#include "eeprom.h"


void write_eep( unsigned char address, unsigned char data )
{
    while( EECON1bits.WR  )     
    {}
    // EEPROM_WRITE( address, data ); íå ïğàöşº äëÿ PIC18!!!!!
  
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

void write_eep_24(uint8_t address, uint24_t data) {
    //write_eep(address, (uint8_t) (data >> 24));
    write_eep(address, (uint8_t) (data >> 16));
    write_eep(address + 1, (uint8_t) (data >> 8));
    write_eep(address + 2, (uint8_t) data);
}

uint24_t read_eep_24(uint8_t address) {
    uint32_t data = 0;

    // data = read_eep(address) << 24;
    data |= read_eep(address) << 16;
    data |= read_eep(address + 1) << 8;
    data |= read_eep(address + 2);
    return data;
}


void write_eep_16(uint8_t address, uint16_t data) {
    write_eep(address, (uint8_t) (data >> 8));
    write_eep(address + 1, (uint8_t) data);
}

uint16_t read_eep_16(uint8_t address){
    uint16_t data = 0;
    
    data = read_eep(address) << 8;
    data |= read_eep(address+1);
    return data;
}