#ifndef EEPROM_H
#define	EEPROM_H

#include <xc.h> // include processor files - each processor file is guarded.  


void write_eep( unsigned char address, unsigned char data );
unsigned char read_eep( unsigned short address );
void write_eep_24(uint8_t address, uint24_t data);
uint24_t read_eep_24(uint8_t address);
void write_eep_16(uint8_t address, uint16_t data);
uint16_t read_eep_16(uint8_t address);

#endif	/* XC_HEADER_TEMPLATE_H */

