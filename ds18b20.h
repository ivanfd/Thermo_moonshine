#ifndef DS18B20_H
#define	DS18B20_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include "onewire.h"
#include "main.h"

//#define DS18B20_ONE // ���� ������ �� ��
#define DS18B20_MANY // ������ ������� �� ��
#define COUNT_DQ 2 // ������� �������
#define CRC8INIT	0x00
#define CRC8POLY	0x18              //0X18 = X^8+X^5+X^4+X^0

#define EE_DQ_1 0 // ������ ������� 1 � ������
#define EE_DQ_2 8 // ������ ������� 2 � ������

const char fract[] = {0,1,1,2,2,3,4,4,5,6,6,7,7,8,9,9}; // �����������, ���� ���� ����
                                                        //  0/16..., 1/16..., 2/16......
#ifdef DS18B20_ONE
uint8_t readTemp_Single(uint16_t *buf, uint8_t *minus,  uint8_t *time_flag, uint8_t *timer_val);
#endif
#ifdef DS18B20_MANY
uint8_t ds18b20_readTemp(uint8_t *time_flag, uint8_t *timer_val);
void ds18b20_readrom(uint8_t num_dq); // ��������� ��� ������� � �������� � ������
uint16_t ds18b20_get_temp(uint8_t num_dq, uint8_t *minus);
#endif
void init_ds18b20(void);
uint8_t ds18b20_crc8(uint8_t *data_in, uint8_t num_bytes);

#endif	/* XC_HEADER_TEMPLATE_H */

