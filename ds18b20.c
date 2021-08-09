#include "ds18b20.h"


uint8_t scratch[9];

#ifdef DS18B20_MANY
uint8_t rom_dq[COUNT_DQ][8]; // ��� �������
uint16_t temp_ready[COUNT_DQ]; // ������ �����������
#endif
//bit minus = 0; // ���� �����������



//===================================================
//      �����������
//===================================================

void init_ds18b20(void) {

    if (!ow_reset()) // ���� ������ ��������
    {

        write_byte(0xCC);
        write_byte(0x4E);
        write_byte(0x00);
        write_byte(0x00);
        write_byte(0x7F); //12 -�� �����  
    }
#ifdef DS18B20_MANY
    for (uint8_t q = 0; q < COUNT_DQ; q++) {
        for (uint8_t i = 0; i < 8; i++) {
            rom_dq[q][i] = read_eep((q*8) + i);
        }
    }
#endif
}


//====================================================
//  ������ ����������� � �������
//  ���� ������ �� ���!
//====================================================
#ifdef DS18B20_ONE
uint8_t readTemp_Single(uint16_t *buf, uint8_t *minus, uint8_t *time_flag, uint8_t *timer_val) {

    uint16_t temp = 0; // �����������
    uint8_t i, tmp, fptmp;
    *minus = '+';

    switch (*time_flag) {
        case 0:
            if (!ow_reset()) // ���� ������ ��������
            {
                write_byte(0xCC); //  ������� ������� ROM
                write_byte(0x44); //  ������������ �����������
                *timer_val = 0;
                *time_flag = 2; // ���� ����� �� �������� �� ���������� ����������
                T1CONbits.TMR1ON = 1; // ���� ������ 1 ���������� ��� �������������

                return 0;
            }
            break;
        case 1:

            ow_reset();
            write_byte(0xCC); //  ������� ������� ROM
            write_byte(0xBE); // Read scratch pad command
            for (i = 0; i < 2; i++)//  ������ ��� ����� �����������
            {
                scratch[i] = read_byte();
            }

            temp = (((uint16_t) scratch[1]) << 8) | ((uint16_t) scratch[0]);
            // temp |= scratch[0];

            if (temp & 0x8000) {
                temp = -temp; // ���� ��`���� 
                *minus = '-';
            }

            tmp = temp & 0x0f; // ����� ��������
            tmp = fract[tmp]; //  ����� ���� ����
            temp = temp >> 4; //  ������� ������ �����������
            temp = (temp & 0x00ff) * 10;
            temp = temp + tmp;

//#ifdef DEBUG
//            printf("Temperature: %d\n\r ", temp);
//#endif
//
//            fptmp = temp % 10; // ������
//            temp = temp / 10; // ���� �������
//
//            if (fptmp >= 6) temp += 1;
            //  temp = floor(temp);

            *buf = temp;
            *time_flag = 0;

            
            break;
            case 2:
           return FALSE;;
           break;
    
    }

}
#endif


//====================================================
//  ������ ����������� � �������
//   ������ �� ���!
//====================================================
#ifdef DS18B20_MANY
uint8_t ds18b20_readTemp(uint8_t *time_flag, uint8_t *timer_val) {

    uint16_t temp = 0; // �����������
    uint8_t i;

    switch (*time_flag) {
        case 0:
            if (!ow_reset()) // ���� ������ ��������
            {
                write_byte(0xCC); //  ������� ������� ROM
                write_byte(0x44); //  ������������ �����������
                *timer_val = 0;
                *time_flag = 2; // ���� ����� �� �������� �� ���������� ����������
                T1CONbits.TMR1ON = 1; // ���� ������ 1 ���������� ��� �������������

                return 0;
            }
            break;
        case 1:
            for (uint8_t j = 0; j < COUNT_DQ; j++) {
                di();
                ow_reset();
                write_byte(0x55); //  ������� ���������� ROM
                for (i = 0; i < 8; i++) { // ������ ��� �������, � ��������� �� COUNT_DQ
                          write_byte(rom_dq[j][i]);
                }
                write_byte(0xBE); // Read scratch pad command

                for (i = 0; i < 9; i++)//  ������ 9 ���� �����������
                {
                    scratch[i] = read_byte();
                }

                if (!(ds18b20_crc8(scratch, 9))) { // ���������� ���������� ����
                    temp = (((uint16_t) scratch[1]) << 8) | ((uint16_t) scratch[0]);
                    temp_ready[j] = temp;
                }else
                    temp_ready[j] = 32767;
                ei();
            }
            *time_flag = 0;
            return TRUE;
            break;
            case 2:
           return FALSE;
           break;
    
    }
    return FALSE;
}


//-----------------------------
//
//-----------------------------
uint8_t ds18b20_readrom(uint8_t num_dq){
    uint8_t i;
    uint8_t temp_rom[8];
    
    if (!ow_reset()) // ���� ������ ��������
    {
        write_byte(0x33); //  ������� READ ROM
        for (i = 0; i < 8; i++) {
            temp_rom[i] = read_byte();
        }
    }
    if (!(ds18b20_crc8(temp_rom, 8))) { // ���������� ���������� ����
        for (i = 0; i < 8; i++) {
            write_eep(((num_dq - 1)*8) + i, temp_rom[i]); // � ������ ��� � ������
        }
        Delay_ms(10);
        return TRUE;
    }
    return FALSE;
}

//-------------------------------
// �������� �������� �����������
// � ������� num_dq
//-------------------------------

uint16_t ds18b20_get_temp(uint8_t num_dq, uint8_t *minus) {
    uint16_t temp = temp_ready[num_dq-1];
    uint8_t tmp;
    *minus = '+';
    if(temp == 32767)
        return temp;
    if (temp & 0x8000) {
        temp = -temp; // ���� ��`���� 
        *minus = '-';
    }

    tmp = temp & 0x0f; // ����� ��������
    tmp = fract[tmp]; //  ����� ���� ����
    temp = temp >> 4; //  ������� ������ �����������
    temp = (temp & 0x00ff) * 10;
    temp = temp + tmp;
    
    return temp;
                      
}

#endif

uint8_t ds18b20_crc8(uint8_t *data_in, uint8_t num_bytes) {
    uint8_t crc;
    uint8_t loop_count;
    uint8_t bit_counter;
    uint8_t data;
    uint8_t feedback_bit;

    crc = CRC8INIT;

    for (loop_count = 0; loop_count != num_bytes; loop_count++) {
        data = data_in[loop_count];

        bit_counter = 8;
        do {
            feedback_bit = (crc ^ data) & 0x01;

            if (feedback_bit == 0x01) {
                crc = crc ^ CRC8POLY;
            }
            crc = (crc >> 1) & 0x7F;
            if (feedback_bit == 0x01) {
                crc = crc | 0x80;
            }

            data = data >> 1;
            bit_counter--;

        } while (bit_counter > 0);
    }

    return crc;
}



