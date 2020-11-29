#include "ds18b20.h"


uint8_t scratch[9];
#ifdef DS18B20_MANY
uint8_t rom_dq[COUNT_DQ][8]; // ��� �������
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
uint8_t readTemp_Single(uint8_t num_d, uint16_t *buf, uint8_t *minus, uint8_t *time_flag, uint8_t *timer_val) {

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


            *buf = temp;
            *time_flag = 0;

            
            break;
            case 2:
           return FALSE;;
           break;
    
    }

}
#endif



