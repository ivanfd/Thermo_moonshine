/*
 * File:   main.c
 * Author: User
 *
 * Created on 24 ������ 2020 �., 15:44
 */


#include <xc.h>
#include "main.h"


uint8_t timer_val = 0, time_flag = 0; // ��� ������������� �����������
uint16_t temperature_1 = 32767, temperature_2 = 32767;
uint16_t temperature_1_old = 32767, temperature_2_old = 32767;
bit en_send_usart = 0;
uint8_t minus_1 = '+', minus_2 = '+';
uint8_t TxtBuf[16];
bit read_key = 0; // ����� �� ������� ������
bit en_sound = 0; // ����� �������
bit sound_yes = 0; // �������� �������� �������
bit snd_k, snd_b, snd_all, snd_k_b, snd_b_b;
bit en_snd_k = 0, en_snd_b = 0;
uint8_t tik_time = 0, tik_time_b = 0; // �������� ���� ��� ������ �� ����
uint8_t pressed_key;    // ���� �������� ��������� ������
uint8_t select = SEL_MAIN; //�� � ���� �� �����������
uint8_t sub_sel = VAL_1, pre_sub_sel;
uint8_t sub_sel_kol;
uint8_t sub_main = SUB_MAIN_1;
uint8_t dq_num = 1;
uint8_t set_t_dq1_up, set_t_dq1_dwn;
uint8_t set_t_dq2_100, set_t_dq2_10;
int16_t set_t_dq2;
uint16_t temp1_fix; //, temp2_fix;

// ����� ������� � LCD
const uint8_t symbol_3[8] = {0x00, 0x04, 0x06, 0x07, 0x06, 0x04, 0x00, 0x00};
const uint8_t symbol_4[8] = {0x06, 0x09, 0x09, 0x06, 0x00, 0x00, 0x00, 0x00};
const uint8_t symbol_5[8] = {0x06, 0x09, 0x09, 0x06, 0x00, 0x00, 0x0F, 0x00};

void main(void) {
    Main_init();    // ����������� ����������

    lcd_gotoxy(1, 1);
    lcdPrint("---���������---");
    lcd_gotoxy(1, 2);
    lcdPrint("(c)Ivan_fd v1.7");
    Delay_ms(2000);
    clearLCD();
    if ((KEY_PORT & (1 << KEY_OK)) == 0) { // ���� ��������� ������ ��
        clearLCD();                         // ����� ��������� ���� �������
        select = SEL_SET_DQ;
        lcd_gotoxy(1, 1);
        lcdPrint("������ 1, ��� 2");
        lcd_gotoxy(1, 2);
        lcdPrint("���i� 18B20:");
        // Delay_ms(2000);
    }

    set_t_dq1_up = read_eep(EE_TMP1_UP); // ������ � ������ ������
    set_t_dq1_dwn = read_eep(EE_TMP1_DWN); // ����������
    set_t_dq2 = (uint16_t) read_eep(EE_PRESET_1_H) << 8 | read_eep(EE_PRESET_1_L);
    temp1_fix = (uint16_t) read_eep(EE_TMP1_FIX) << 8 | read_eep(EE_TMP1_FIX + 1);
    en_snd_k = read_eep(EE_PRESET_SND_K);
    en_snd_b = read_eep(EE_PRESET_SND_B);

    if (!(en_snd_k) && !(en_snd_b)) {
        sound_yes = 0;
    } else
        sound_yes = 1;

    lcd_gotoxy(10, 2);
    lcdPrint("1");
    //==========================
    //       ³���� ����
    //==========================
    while (1) {


        if (read_key) { // ���������� ������
            key_press();
            read_key = 0;
        }
        pressed_key = key_GetKey(); // ������ ��� �����

        switch (select) {
            case SEL_MAIN:
                if (ds18b20_readTemp(&time_flag, &timer_val)) { // ������ �����������
                    temperature_1_old = temperature_1;
                    temperature_2_old = temperature_2;
                    temperature_1 = ds18b20_get_temp(1, &minus_1);
                    temperature_2 = ds18b20_get_temp(2, &minus_2);
                    if((temperature_1 != temperature_1_old) || (temperature_2 != temperature_2_old))
                        en_send_usart = 1; // ��������� ��������� ����������� �� �����
                }
#ifdef DEBUG_OUT  // ������ ���������� ����������� � ����
                if (en_send_usart) {
                    en_send_usart = 0;
                    if (temperature_1 != 32767) {
                        EUSART_Write_Str("tk:");
                        EUSART_Write(((temperature_1 / 1000) % 10) + 48); // �������� ����� �����
                        EUSART_Write(((temperature_1 / 100) % 10) + 48); // �������� ����� �����
                        EUSART_Write(((temperature_1 / 10) % 10) + 48); //......
                        EUSART_Write((temperature_1 % 10) + 48);
                        //                    EUSART_Write_Str(" �C\r\n");
                    } else {
                        EUSART_Write_Str("tk:");
                        EUSART_Write_Str("0000");
                    }
                    if (temperature_2 != 32767) {
                        EUSART_Write_Str("tb:");
                        EUSART_Write(((temperature_2 / 1000) % 10) + 48); //......
                        EUSART_Write(((temperature_2 / 100) % 10) + 48); // �������� ����� �����
                        EUSART_Write(((temperature_2 / 10) % 10) + 48); //......
                        EUSART_Write((temperature_2 % 10) + 48);
                        EUSART_Write_Str("\r\n");
                    } else {
                        EUSART_Write_Str("tb:");
                        EUSART_Write_Str("0000\r\n");

                    }
                }
#endif
                // �������� �����������
                // � ���� �������
                //---------------------

                lcd_gotoxy(1, 1);
                lcdPrint("��:");
                //lcd_gotoxy(8, 1);
                if (!(temperature_1 == 32767)) { // ���� ������ �� �������
                    if (((temperature_1 / 1000) % 10) == 0) { // ���� ����� ����� 0
                        if (((temperature_1 / 100) % 10) == 0) { // ���� ����� ����� 0
                            //lcd_putc(minus_1);
                            //lcd_putc(((temperature_1 / 100) % 10) + 48);
                            lcd_putc(((temperature_1 / 10) % 10) + 48);
                            lcd_putc('.');
                            lcd_putc(((temperature_1 % 10) + 48));
                            lcd_putc(0x01);
                            //                                    lcd_putc('C');
                            lcd_putc(' ');
                            lcd_putc(' ');
                             lcd_putc(' ');
                        } else { // ���� ����� �� ����
                            //lcd_putc(minus_1);
                            lcd_putc(((temperature_1 / 100) % 10) + 48);
                            lcd_putc(((temperature_1 / 10) % 10) + 48);
                            lcd_putc('.');
                            lcd_putc(((temperature_1 % 10) + 48));
                            lcd_putc(0x01);
                            //                                    lcd_putc('C');
                            lcd_putc(' ');
                             lcd_putc(' ');
                            // lcd_putc(' ');
                        }
                    } else { // ���� ����� �� ����
                        //lcd_putc(minus_1);
                        lcd_putc(((temperature_1 / 1000) % 10) + 48);
                        lcd_putc(((temperature_1 / 100) % 10) + 48);
                        lcd_putc(((temperature_1 / 10) % 10) + 48);
                        lcd_putc('.');
                        lcd_putc(((temperature_1 % 10) + 48));
                        lcd_putc(0x01);
                        //                                lcd_putc('C');
                         lcd_putc(' ');
                        // lcd_putc(' ');
                    }
                } else {
                    lcd_putc('-');
                    lcd_putc('-');
                    lcd_putc('-');
                    lcd_putc(' ');
                    lcd_putc(' ');
                    lcd_putc(' ');
                    lcd_putc(' ');
                }
               // lcd_gotoxy(16, 1);
               // (en_snd_k) ? lcd_putc(0xED) : lcd_putc(0xD5); // ������ �����

                lcd_gotoxy(11, 1);
                //lcd_putc(0xCE);
                lcd_putc(0xAA);
                lcd_putc(((temp1_fix / 100) % 10) + 48);
                lcd_putc(((temp1_fix / 10) % 10) + 48);
                lcd_putc('.');
                lcd_putc(((temp1_fix % 10) + 48));
                (en_snd_k) ? lcd_putc(2) : lcd_putc(1);

                lcd_gotoxy(1, 2);
                lcdPrint("��:");
                //lcd_gotoxy(8, 1);
                if (!(temperature_2 == 32767)) {
                    if (((temperature_2 / 1000) % 10) == 0) { // ���� ����� ����� 0
                        if (((temperature_2 / 100) % 10) == 0) { // ���� ����� ����� 0
                            //  lcd_putc(minus_2);
                            //lcd_putc(((temperature_1 / 100) % 10) + 48);
                            lcd_putc(((temperature_2 / 10) % 10) + 48);
                            lcd_putc('.');
                            lcd_putc(((temperature_2 % 10) + 48));
                            lcd_putc(0x01);
                            //                                    lcd_putc('C');
                            lcd_putc(' ');
                            lcd_putc(' ');
                            // lcd_putc(' ');
                        } else { // ���� ����� �� ����
                            //  lcd_putc(minus_2);
                            lcd_putc(((temperature_2 / 100) % 10) + 48);
                            lcd_putc(((temperature_2 / 10) % 10) + 48);
                            lcd_putc('.');
                            lcd_putc(((temperature_2 % 10) + 48));
                            lcd_putc(0x01);
                            lcd_putc(' ');

                        }
                    } else { // ���� ����� �� ����
                        // lcd_putc(minus_2);
                        lcd_putc(((temperature_2 / 1000) % 10) + 48);
                        lcd_putc(((temperature_2 / 100) % 10) + 48);
                        lcd_putc(((temperature_2 / 10) % 10) + 48);
                        lcd_putc('.');
                        lcd_putc(((temperature_2 % 10) + 48));
                        lcd_putc(0x01);

                    }
                } else {
                    lcd_putc('-');
                    lcd_putc('-');
                    lcd_putc('-');
                    lcd_putc(' ');
                    lcd_putc(' ');
                    lcd_putc(' ');
                    //lcd_putc(' ');
                }
              //  lcd_gotoxy(16, 2);
              //  (en_snd_b) ? lcd_putc(0xED) : lcd_putc(0xD5);
                lcd_gotoxy(11, 2);
                //lcdPrint("���i�:");
                lcd_putc(0xbe);

                lcd_putc(((set_t_dq2 / 100) % 10) + 48);
                lcd_putc(((set_t_dq2 / 10) % 10) + 48);
                lcd_putc('.');
                lcd_putc(((set_t_dq2 % 10) + 48));
                (en_snd_b) ? lcd_putc(2) : lcd_putc(1);
                //lcd_putc(0x01);
                //lcd_putc(0xD9);



                //+++++++++++++++++++++++
                // �������� ������ �����
                //+++++++++++++++++++++++
                if (sound_yes) { // ���� � ����� �����
                    //                    lcd_gotoxy(15, 1);
                    //                    lcd_putc(' ');
                    //                    lcd_putc(0xED); // �������� ������ - ������
                    if (en_snd_k) { //���� ���� ��� ������ ����������
                        if (((temperature_1 >= (temp1_fix + set_t_dq1_up)) ||
                                (temperature_1 <= (temp1_fix - set_t_dq1_dwn))) &&
                                !(temperature_1 == 32767)) {

                            snd_k_b = 1; // ���� ��� ������
                        } else
                            snd_k_b = 0;
                    } else
                        snd_k_b = 0;

                    if (en_snd_b) {
                        if ((temperature_2 >= set_t_dq2) && !(temperature_2 == 32767))
                            snd_b_b = 1;
                        else
                            snd_b_b = 0;
                    } else
                        snd_b_b = 0;

                    if (snd_k_b && snd_b_b) {
                        en_sound = 1;
                        snd_k = 0;
                        snd_b = 0;
                        snd_all = 1;
                        if (tik_time >= 100) {
                            tik_time = 0;
                            EUSART_Write('A');
                            EUSART_Write('l');
                            EUSART_Write('r');
                            EUSART_Write('_');
                            EUSART_Write('A');
                            EUSART_Write('\r');
                            EUSART_Write('\n');
                        }
                    } else if (snd_b_b) {
                        en_sound = 1;
                        snd_k = 0;
                        snd_all = 0;
                        snd_b = 1;
                        if (tik_time >= 100) {
                            tik_time = 0;
                            EUSART_Write('A');
                            EUSART_Write('l');
                            EUSART_Write('r');
                            EUSART_Write('_');
                            EUSART_Write('B');
                            EUSART_Write('\r');
                            EUSART_Write('\n');
                        }                        
                    } else if (snd_k_b) {
                        en_sound = 1;
                        snd_k = 1;
                        snd_all = 0;
                        snd_b = 0;
                        if (tik_time >= 100) {
                            tik_time = 0;
                            EUSART_Write('A');
                            EUSART_Write('l');
                            EUSART_Write('r');
                            EUSART_Write('_');
                            EUSART_Write('K');
                            EUSART_Write('\r');
                            EUSART_Write('\n');
                        }
                    } else
                        en_sound = 0;

                } else {
                    //                    lcd_gotoxy(15, 1);
                    //                    lcd_putc(' ');
                    //                    lcd_putc(0xD5);
                    SND = 0;
                    en_sound = 0;
                }


                if (pressed_key == KEY_OK_EVENT) { // ��������� ������ ��
                    sub_sel--;
                    if (sub_sel == 255)
                        sub_sel = VAL_9;
                    outValPreset();

                }

                if (pressed_key == KEY_UP_EVENT) {

                    sub_sel++;
                    if (sub_sel > VAL_9)
                        sub_sel = VAL_1;
                    outValPreset();
                }

                if (pressed_key == KEY_BOTH_EVENT) { //�� ������, ����

                    clearLCD();
                    select = SEL_DQ_SND;
                    lcd_gotoxy(1, 1);
                    lcdPrint("���i� ����. Led");
                    lcd_gotoxy(1, 2);
                    lcdPrint("  1     2   1-2");
                   // Delay_ms(10);
                }

                break;
                //===========================================
            case SEL_SET_DQ:// ������������ ��������� �������

                lcd_gotoxy(14, 2);
                lcd_putc(dq_num + 48);
                if (pressed_key == KEY_OK_EVENT) {
                    dq_num++;
                    if (dq_num == 3)
                        dq_num = 1;
                }
                if (pressed_key == KEY_UP_EVENT) {
                    dq_num--;
                    if (dq_num == 0)
                        dq_num = 2;
                }
                if (pressed_key == KEY_BOTH_EVENT) {
                    if (ds18b20_readrom(dq_num)) {
                        lcd_gotoxy(1, 2);
                        lcdPrint(" ��� ��������� ");
                    }

                    select = SEL_STOP;
                }
                break;
            case SEL_STOP:
                break;
            case SEL_DQ_SND:
                if (pressed_key == KEY_OK_EVENT) { // ��������� ������ ��
                    clearLCD();
                    select = SEL_SET_TEMP;
                    lcd_gotoxy(1, 1);
                    lcdPrint("   ������i   ");
                    lcd_gotoxy(1, 2);
                    lcdPrint(" ���(1)  ���(2)");
                }

                if (pressed_key == KEY_UP_EVENT) {
                    //                    sound_yes = !(sound_yes);
                    //                    select = SEL_MAIN;
                    clearLCD();
                    select = SEL_EN_SND;
                    lcd_gotoxy(1, 1);
                    lcdPrint(" ������    ���");
                }
                if (pressed_key == KEY_BOTH_EVENT) {
                    LED_ON = !(LED_ON);
                    select = SEL_MAIN;
                    outValPreset();
                }
                break;
            case SEL_EN_SND:// ��������� �� �������� ���� ��� ������� �������
                lcd_gotoxy(4, 2);
                (en_snd_k) ? lcd_putc(0xED) : lcd_putc(0xD5);
                lcd_gotoxy(13, 2);
                (en_snd_b) ? lcd_putc(0xED) : lcd_putc(0xD5);

                if (pressed_key == KEY_OK_EVENT) { // ��������� ������ ��
                    en_snd_k = !(en_snd_k);
                }

                if (pressed_key == KEY_UP_EVENT) {
                    en_snd_b = !(en_snd_b);
                }
                if (pressed_key == KEY_BOTH_EVENT) {
                    if (!(en_snd_k) && !(en_snd_b)) {
                        sound_yes = 0;
                    } else
                        sound_yes = 1;
                    //                 sound_yes = !(sound_yes);
                    write_eep(EE_PRESET_SND_K, en_snd_k);
                    write_eep(EE_PRESET_SND_B, en_snd_b);
                    select = SEL_MAIN;
                    outValPreset();
                }
                break;
            case SEL_SET_TEMP:// ���� ������������ ������

                if (pressed_key == KEY_OK_EVENT) {
                        select = SEL_SET_TEMP_DQ1;
                        sub_sel_kol = SUB_SEL_UP;
                        clearLCD();
                        lcd_gotoxy(1, 1);
                        lcdPrint("    ������  ");
                        lcd_gotoxy(1, 2);
                        lcdPrint("���� ����:");
                }
                if (pressed_key == KEY_UP_EVENT) {
                        select = SEL_SET_TEMP_DQ2;
                        //sub_sel = SUB_SEL_UP;
                        clearLCD();
                        lcd_gotoxy(1, 1);
                        lcdPrint("    ������  ");
                        lcd_gotoxy(1, 2);
                        lcdPrint("��������");
                        set_t_dq2 = (uint16_t) read_eep(EE_PRESET_1_H) << 8 | read_eep(EE_PRESET_1_L);
                        pre_sub_sel = sub_sel;
                        sub_sel = VAL_1;
                }


                break;
            case SEL_SET_TEMP_DQ1:// ����������� ������ ������� ������
                switch (sub_sel_kol) {
                    case SUB_SEL_UP: // ������ ���� ����������� �������
                        lcd_gotoxy(11, 2);
                        lcd_putc('+');
                        lcd_putc(((set_t_dq1_up / 10) % 10) + 48);
                        lcd_putc('.');
                        lcd_putc(((set_t_dq1_up % 10) + 48));

                        if (pressed_key == KEY_OK_EVENT) {
                            set_t_dq1_up++;
                            if (set_t_dq1_up == 11)
                                set_t_dq1_up = 0;
                        }
                        if (pressed_key == KEY_UP_EVENT) {
                            set_t_dq1_up--;
                            if (set_t_dq1_up == 255)
                                set_t_dq1_up = 10;
                        }
                        if (pressed_key == KEY_BOTH_EVENT) {
                            sub_sel_kol = SUB_SEL_DWN;
                            lcd_gotoxy(1, 2);
                            lcdPrint("���� ���:     ");
                        }
                        break;
                    case SUB_SEL_DWN:// ����� ���� ����������� �������
                        lcd_gotoxy(10, 2);
                        lcd_putc('-');
                        lcd_putc(((set_t_dq1_dwn / 10) % 10) + 48);
                        lcd_putc('.');
                        lcd_putc(((set_t_dq1_dwn % 10) + 48));

                        if (pressed_key == KEY_OK_EVENT) {
                            set_t_dq1_dwn++;
                            if (set_t_dq1_dwn == 11)
                                set_t_dq1_dwn = 0;
                        }
                        if (pressed_key == KEY_UP_EVENT) {
                            set_t_dq1_dwn--;
                            if (set_t_dq1_dwn == 255)
                                set_t_dq1_dwn = 10;
                        }
                        if (pressed_key == KEY_BOTH_EVENT) {
                            sub_sel_kol = SUB_SEL_FIX;
                            write_eep(EE_TMP1_UP, set_t_dq1_up);
                            write_eep(EE_TMP1_DWN, set_t_dq1_dwn);
                            lcd_gotoxy(1, 1);
                            lcdPrint(" �i����i� t ���.");                            
                            lcd_gotoxy(1, 2);
                            lcdPrint("������i�� �� ��");                            
                            //outValPreset();
                        }
                        break;
                    case SUB_SEL_FIX:// �������� �����������

                        if (pressed_key == KEY_BOTH_EVENT) {
                            select = SEL_MAIN;
                            temp1_fix = temperature_1;
                            write_eep(EE_TMP1_FIX, (temp1_fix >> 8));
                            write_eep(EE_TMP1_FIX + 1, (uint8_t) temp1_fix);
                            outValPreset();
                        }
                        break;

                }//end sub_sel

                break;
            case SEL_SET_TEMP_DQ2:// ����������� ������ ������� ���

                lcd_gotoxy(10, 2);

                switch (sub_sel) {
                    case VAL_1: // ����� ���������
                        lcdPrint("1:");
                        break;
                    case VAL_2: // 2 ���������
                        lcdPrint("2:");
                        break;
                    case VAL_3: // 3 ���������
                        lcdPrint("3:");
                        break;
                    case VAL_4: // 4 ���������
                        lcdPrint("4:");
                        break;
                    case VAL_5: // 5 ���������
                        lcdPrint("5:");
                        break;
                    case VAL_6: // 6 ���������
                        lcdPrint("6:");
                        break;
                    case VAL_7: // 7 ���������
                        lcdPrint("7:");
                        break;
                    case VAL_8: // 8 ���������
                        lcdPrint("8:");
                        break;
                    case VAL_9: // 9 ���������
                        lcdPrint("9:");
                        break;
                }
                lcd_putc(((set_t_dq2 / 100) % 10) + 48);
                lcd_putc(((set_t_dq2 / 10) % 10) + 48);
                lcd_putc('.');
                lcd_putc((set_t_dq2 % 10) + 48);
                lcd_putc(0x01);

                if (pressed_key == KEY_OK_EVENT) {
                    if (keyLong)
                        set_t_dq2 += 10;
                    else
                        set_t_dq2++;

                    if (set_t_dq2 > 999)
                        set_t_dq2 = 999;
                }
                if (pressed_key == KEY_UP_EVENT) {
                    if (keyLong)
                        set_t_dq2 -= 10;
                    else
                        set_t_dq2--;
                    
                    if (set_t_dq2 < 1)
                        set_t_dq2 = 1;
                }

                if (pressed_key == KEY_BOTH_EVENT) {

                    switch (sub_sel) { // �������� � ������ ���
                        case VAL_1: // ����� ���������
                            write_eep(EE_PRESET_1_H, HIGH_BYTE(set_t_dq2));
                            write_eep(EE_PRESET_1_L, LOW_BYTE(set_t_dq2));
                            set_t_dq2 = (uint16_t) read_eep(EE_PRESET_2_H) << 8 | read_eep(EE_PRESET_2_L);
                            break;
                        case VAL_2: // 2 ���������
                            write_eep(EE_PRESET_2_H, HIGH_BYTE(set_t_dq2));
                            write_eep(EE_PRESET_2_L, LOW_BYTE(set_t_dq2));
                            set_t_dq2 = (uint16_t) read_eep(EE_PRESET_3_H) << 8 | read_eep(EE_PRESET_3_L);
                            break;
                        case VAL_3: // 3 ���������
                            write_eep(EE_PRESET_3_H, HIGH_BYTE(set_t_dq2));
                            write_eep(EE_PRESET_3_L, LOW_BYTE(set_t_dq2));
                            set_t_dq2 = (uint16_t) read_eep(EE_PRESET_4_H) << 8 | read_eep(EE_PRESET_4_L);                            
                            break;
                        case VAL_4: // 4 ���������
                            write_eep(EE_PRESET_4_H, HIGH_BYTE(set_t_dq2));
                            write_eep(EE_PRESET_4_L, LOW_BYTE(set_t_dq2));
                            set_t_dq2 = (uint16_t) read_eep(EE_PRESET_5_H) << 8 | read_eep(EE_PRESET_5_L);                            
                            break;
                        case VAL_5: // 5 ���������
                            write_eep(EE_PRESET_5_H, HIGH_BYTE(set_t_dq2));
                            write_eep(EE_PRESET_5_L, LOW_BYTE(set_t_dq2));
                            set_t_dq2 = (uint16_t) read_eep(EE_PRESET_6_H) << 8 | read_eep(EE_PRESET_6_L);                            
                            break;
                        case VAL_6: // 6 ���������
                            write_eep(EE_PRESET_6_H, HIGH_BYTE(set_t_dq2));
                            write_eep(EE_PRESET_6_L, LOW_BYTE(set_t_dq2));
                            set_t_dq2 = (uint16_t) read_eep(EE_PRESET_7_H) << 8 | read_eep(EE_PRESET_7_L);                            
                            break;
                        case VAL_7: // 7 ���������
                            write_eep(EE_PRESET_7_H, HIGH_BYTE(set_t_dq2));
                            write_eep(EE_PRESET_7_L, LOW_BYTE(set_t_dq2));
                            set_t_dq2 = (uint16_t) read_eep(EE_PRESET_8_H) << 8 | read_eep(EE_PRESET_8_L);                            
                            break;
                        case VAL_8: // 8 ���������
                            write_eep(EE_PRESET_8_H, HIGH_BYTE(set_t_dq2));
                            write_eep(EE_PRESET_8_L, LOW_BYTE(set_t_dq2));
                            set_t_dq2 = (uint16_t) read_eep(EE_PRESET_9_H) << 8 | read_eep(EE_PRESET_9_L);                            
                            break;
                        case VAL_9: // 9 ���������
                            write_eep(EE_PRESET_9_H, HIGH_BYTE(set_t_dq2));
                            write_eep(EE_PRESET_9_L, LOW_BYTE(set_t_dq2));
                            break;
                    }


                    sub_sel++;

                    if (sub_sel > VAL_9) {
                        sub_sel = VAL_1;
                        select = SEL_MAIN;
                        outValPreset();
                        //set_t_dq2 = (uint16_t) read_eep(EE_PRESET_1_H) << 8 | read_eep(EE_PRESET_1_L);
                        //lcd_gotoxy(10, 2);
                        //lcd_putc('1');

                    }

                    Delay_ms(10);
                }




                break;
        }// end select



    }
    return;
}

void Main_init(void) {


    PORTA = 0;
    LATA = 0;
    TRISA = 0;
    PORTB = 0;
    LATB = 0;
    TRISB = 0b00000110;
    PORTC = 0;
    LATC = 0;
    TRISC = 0;
    OSCCONbits.SCS0 = 0;
    OSCCONbits.SCS1 = 1;
    OSCCONbits.IRCF = 0b111; // �������� ��������� 8MHz
    ADCON1bits.PCFG = 0b1111; // �� ����� ������

    DQ = 1;

    init_ds18b20();

    T1CON = 0b10000000;
    //T1CONbits.TMR1ON = 0; // �������� ������ 1
    TMR1H = HIGH_BYTE(TMR1Val);
    TMR1L = LOW_BYTE(TMR1Val);
    IPR1bits.TMR1IP = 1; // ������� �������� ��� ������� 1

    T0CONbits.T0PS = 0b000; //������ 0 ������ 1:1
    T0CONbits.PSA = 1;
    T0CONbits.T08BIT = 0; //16 �� ������ 0
    T0CONbits.T0CS = 0;
    T0CONbits.TMR0ON = 1;
    TMR0H = HIGH_BYTE(TMR0Val);
    TMR0L = LOW_BYTE(TMR0Val);
    INTCONbits.T0IE = 1; // ����������� �� ������� 0
    INTCON2bits.T0IP = 0; // ������� �������� ��� ������� 0
    INTCON2bits.RBPU = 0; // ��������� ���������



    PIE1bits.TMR1IE = 1; // ���������� �� ������� 1
    RCONbits.IPEN = 1; //���������� ���������� ���.
    INTCONbits.PEIE = 1; // �������� �������� ����������
    INTCONbits.GIE = 1; // �������� ��������� �����������
    initLCD();
    init_uart();
    cgrom_char(symbol_4, 1);
    cgrom_char(symbol_5, 2);
    SND = 0;
    snd_k = 0;
    snd_b = 0;
    snd_all = 0;

}

void Delay_ms(uint16_t delay) {
    for (uint16_t i = 0; i <= delay; i++)
        __delay_ms(1);
}

void high_priority interrupt myIntH(void) {

    if (PIR1bits.TMR1IF == 1) {
        PIR1bits.TMR1IF = 0; // ������� ������� ����������� �� ������� 1
        TMR1H = HIGH_BYTE(TMR1Val);
        TMR1L = LOW_BYTE(TMR1Val);
        if (++timer_val >= 30) // �������� > 750��
        {
            timer_val = 0;
            time_flag = 1;
            T1CONbits.TMR1ON = 0;

        }
    }

    return;
}

void low_priority interrupt myIntL(void) {
    static uint8_t snd_delay;

    if (INTCONbits.T0IF == 1) {//�������� ����������� �� ������� 0
        INTCONbits.T0IF = 0;
        TMR0H = HIGH_BYTE(TMR0Val);
        TMR0L = LOW_BYTE(TMR0Val);
        read_key = 1; // ����� �� ������� ������
        tik_time++;
        tik_time_b++;
        if (en_sound) {
            snd_delay++;
            if (snd_k) {
                if (snd_delay <= SND_TIME_K) {
                    SND = 1; // �������� ���� �����(�������� �����!)
                } else
                    SND = 0; // �������� ���� �����(�������� �����!)
                if (snd_delay > SND_PAUSE_K)
                    snd_delay = 0;
            }
            if (snd_b) {
                if (snd_delay <= SND_TIME_B) {
                    SND = 1; // �������� ���� �����(�������� �����!)
                } else
                    SND = 0; // �������� ���� �����(�������� �����!)
                if (snd_delay > SND_PAUSE_B)
                    snd_delay = 0;
            }
            if (snd_all) {
                if (snd_delay <= SND_TIME_ALL) {
                    SND = 1; // �������� ���� �����(�������� �����!)
                } else
                    SND = 0; // �������� ���� �����(�������� �����!)
                if (snd_delay > SND_PAUSE_ALL)
                    snd_delay = 0;
            }
        } else
            SND = 0;

    }
    return;
}

void outValPreset(void) {
    lcd_gotoxy(10, 2);
    switch (sub_sel) { // �� ���������� � ��������� ���������

        case VAL_1: // ����� ���������
            set_t_dq2 = (uint16_t) read_eep(EE_PRESET_1_H) << 8 | read_eep(EE_PRESET_1_L);
            lcd_putc('1');
            break;
        case VAL_2: // 2 ���������
            set_t_dq2 = (uint16_t) read_eep(EE_PRESET_2_H) << 8 | read_eep(EE_PRESET_2_L);
            lcd_putc('2');
            break;
        case VAL_3: // 3 ���������
            set_t_dq2 = (uint16_t) read_eep(EE_PRESET_3_H) << 8 | read_eep(EE_PRESET_3_L);
            lcd_putc('3');
            break;
        case VAL_4: // 4 ���������
            set_t_dq2 = (uint16_t) read_eep(EE_PRESET_4_H) << 8 | read_eep(EE_PRESET_4_L);
            lcd_putc('4');
            break;
        case VAL_5: // 5 ���������
            set_t_dq2 = (uint16_t) read_eep(EE_PRESET_5_H) << 8 | read_eep(EE_PRESET_5_L);
            lcd_putc('5');
            break;
        case VAL_6: // 6 ���������
            set_t_dq2 = (uint16_t) read_eep(EE_PRESET_6_H) << 8 | read_eep(EE_PRESET_6_L);
            lcd_putc('6');
            break;
        case VAL_7: // 7 ���������
            set_t_dq2 = (uint16_t) read_eep(EE_PRESET_7_H) << 8 | read_eep(EE_PRESET_7_L);
            lcd_putc('7');
            break;
        case VAL_8: // 8 ���������
            set_t_dq2 = (uint16_t) read_eep(EE_PRESET_8_H) << 8 | read_eep(EE_PRESET_8_L);
            lcd_putc('8');
            break;
        case VAL_9: // 9 ���������
            set_t_dq2 = (uint16_t) read_eep(EE_PRESET_9_H) << 8 | read_eep(EE_PRESET_9_L);
            lcd_putc('9');
            break;
    }
}