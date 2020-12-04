/*
 * File:   main.c
 * Author: User
 *
 * Created on 24 ноября 2020 г., 15:44
 */


#include <xc.h>
#include "main.h"


uint8_t timer_val = 0, time_flag = 0;  // для конвертування температури
uint16_t temperature_1, temperature_2;
uint8_t minus_1 = '+', minus_2 = '+';
uint8_t TxtBuf[16];
bit read_key = 0; // дозвіл на читання кнопок
bit en_sound = 0; // дозвіл сигналу
bit sound_yes = 0; // загальна заборона сигналу
uint8_t pressed_key;
uint8_t select = SEL_MAIN; //де в меню ми знаходимося
uint8_t sub_sel;
uint8_t sub_main = SUB_MAIN_1;
uint8_t dq_num = 1;
uint8_t set_t_dq1_up, set_t_dq1_dwn, set_t_dq2_up, set_t_dq2_dwn;
uint16_t temp1_fix, temp2_fix;

const uint8_t symbol_3[8] = {0x00, 0x04, 0x06, 0x07, 0x06, 0x04, 0x00, 0x00};
const uint8_t symbol_4[8] = {0x06, 0x09, 0x09, 0x06, 0x00, 0x00, 0x00, 0x00};

void main(void) {
    Main_init();

    lcd_gotoxy(1, 1);
    lcdPrint("---ТЕРМОМЕТР---");
    lcd_gotoxy(1, 2);
    lcdPrint("(c)Ivan_fd v1.0");
    Delay_ms(2000);
    clearLCD();
    if ((KEY_PORT & (1 << KEY_OK)) == 0) {
        clearLCD();
        select = SEL_SET_DQ;
        lcd_gotoxy(1, 1);
        lcdPrint("Датчик 1, або 2");
        lcd_gotoxy(1, 2);
        lcdPrint("Вибiр 18B20:");
        // Delay_ms(2000);
    }

    set_t_dq1_up = read_eep(EE_TMP1_UP); // читаємо з еепром пороги
    set_t_dq1_dwn = read_eep(EE_TMP1_DWN); // температур
    set_t_dq2_up = read_eep(EE_TMP2_UP);
    set_t_dq2_dwn = read_eep(EE_TMP2_DWN);
    temp1_fix = read_eep(EE_TMP1_FIX);
    temp2_fix = read_eep(EE_TMP2_FIX);

    while (1) {


        if (read_key) {
            key_press();
            read_key = 0;
        }
        pressed_key = key_GetKey(); // читаємо копку

        switch (select) {
            case SEL_MAIN:
                if (ds18b20_readTemp(&time_flag, &timer_val)) { // читаємо температуру
                    temperature_1 = ds18b20_get_temp(1, &minus_1);
                    temperature_2 = ds18b20_get_temp(2, &minus_2);
                }

                
                // виводимо температуру
                // з двох датчиків
                //---------------------
                switch (sub_main) { // вибираємо яку температуру показувати
                    case SUB_MAIN_1: // температура з колони
                        lcd_gotoxy(1, 1);
                        lcdPrint("Колона:");
                        lcd_gotoxy(8, 1);
                        if (!(temperature_1 == 32767)) {
                            if (((temperature_1 / 100) % 10) == 0) {
                                lcd_putc(minus_1);
                                //lcd_putc(((temperature_1 / 100) % 10) + 48);
                                lcd_putc(((temperature_1 / 10) % 10) + 48);
                                lcd_putc('.');
                                lcd_putc(((temperature_1 % 10) + 48));
                                lcd_putc(0x01);
                                lcd_putc('C');
                                lcd_putc(' ');
                                lcd_putc(' ');
                            } else {
                                lcd_putc(minus_1);
                                lcd_putc(((temperature_1 / 100) % 10) + 48);
                                lcd_putc(((temperature_1 / 10) % 10) + 48);
                                lcd_putc('.');
                                lcd_putc(((temperature_1 % 10) + 48));
                                lcd_putc(0x01);
                                lcd_putc('C');
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
                        lcd_gotoxy(1, 2);
                        lcd_putc(0xCE);
                        lcd_putc(((temp1_fix / 100) % 10) + 48);
                        lcd_putc(((temp1_fix / 10) % 10) + 48);
                        lcd_putc('.');
                        lcd_putc(((temp1_fix % 10) + 48));
                        lcd_putc(0x01);
                        lcd_putc(' ');
                        lcd_putc(0xD9);  
                        lcd_putc(((set_t_dq1_up / 10) % 10) + 48);
                        lcd_putc('.');
                        lcd_putc(((set_t_dq1_up % 10) + 48));                        
                        lcd_putc(' ');
                        lcd_putc(0xDA);  
                        lcd_putc(((set_t_dq1_dwn / 10) % 10) + 48);
                        lcd_putc('.');
                        lcd_putc(((set_t_dq1_dwn % 10) + 48)); 

                        break;
                    case SUB_MAIN_2:// температура з голови
                        lcd_gotoxy(1, 1);
                        lcdPrint("Голова:");
                        lcd_gotoxy(8, 1);
                        if (!(temperature_2 == 32767)) {
                            if (((temperature_2 / 100) % 10) == 0) {
                                lcd_putc(minus_2);
                                //lcd_putc(((temperature_2 / 100) % 10) + 48);
                                lcd_putc(((temperature_2 / 10) % 10) + 48);
                                lcd_putc('.');
                                lcd_putc(((temperature_2 % 10) + 48));
                                lcd_putc(0x01);
                                lcd_putc('C');
                                lcd_putc(' ');
                                lcd_putc(' ');
                            } else {
                                lcd_putc(minus_2);
                                lcd_putc(((temperature_2 / 100) % 10) + 48);
                                lcd_putc(((temperature_2 / 10) % 10) + 48);
                                lcd_putc('.');
                                lcd_putc(((temperature_2 % 10) + 48));
                                lcd_putc(0x01);
                                lcd_putc('C');
                                lcd_putc(' ');
                                //lcd_putc(' ');
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
                        lcd_gotoxy(1, 2);
                        lcd_putc(0xCE);
                        lcd_putc(((temp2_fix / 100) % 10) + 48);
                        lcd_putc(((temp2_fix / 10) % 10) + 48);
                        lcd_putc('.');
                        lcd_putc(((temp2_fix % 10) + 48));
                        lcd_putc(0x01);
                        lcd_putc(' ');
                        lcd_putc(0xD9);
                        lcd_putc(((set_t_dq2_up / 10) % 10) + 48);
                        lcd_putc('.');
                        lcd_putc(((set_t_dq2_up % 10) + 48));
                        lcd_putc(' ');
                        lcd_putc(0xDA);
                        lcd_putc(((set_t_dq2_dwn / 10) % 10) + 48);
                        lcd_putc('.');
                        lcd_putc(((set_t_dq2_dwn % 10) + 48));
                        break;
                }// end sub_main

                if (sound_yes) { // якщо є дозвіл звуку
                    lcd_gotoxy(16, 1);
                    lcd_putc(0xED);
                    if ((((temperature_1 >= (temp1_fix + set_t_dq1_up)) || 
                            (temperature_1 <= (temp1_fix - set_t_dq1_dwn))) && 
                                (!(temperature_1 == 32767))) || 
                            (((temperature_2 >= (temp2_fix + set_t_dq2_up)) || 
                            (temperature_2 <= (temp2_fix - set_t_dq2_dwn))) && 
                                (!(temperature_2 == 32767))))
                        en_sound = 1;
                    else
                        en_sound = 0;

                } else {
                    lcd_gotoxy(16, 1);
                    lcd_putc(0xD5);
                    SND = 0;
                    en_sound = 0;
                }                


                if (pressed_key == KEY_OK_EVENT) { // натиснули кнопку ОК
                    clearLCD();
                    select = SEL_DQ_SND;
                    lcd_gotoxy(1, 1);
                    lcdPrint(" Порiг  Сигнал");
                    lcd_gotoxy(1, 2);
                    lcdPrint("  OK      UP");

                }
                
                if (pressed_key == KEY_UP_EVENT) {
                    if (sub_main == SUB_MAIN_1)
                        sub_main = SUB_MAIN_2;
                    else
                        sub_main = SUB_MAIN_1;
                }
                
                if (pressed_key == KEY_BOTH_EVENT) {
                    temp1_fix = temperature_1;
                    temp2_fix = temperature_2;
                    write_eep(EE_TMP1_FIX, temp1_fix);
                    write_eep(EE_TMP2_FIX, temp2_fix);
                }

                break;
                //===========================================
            case SEL_SET_DQ:// налаштування приєднання датчиків

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
                        lcdPrint(" Код прочитано ");
                    }

                    select = SEL_STOP;
                }
                break;
            case SEL_STOP:
                break;
            case SEL_DQ_SND:
                if (pressed_key == KEY_OK_EVENT) { // натиснули кнопку ОК
                    clearLCD();
                    select = SEL_SET_TEMP;
                    lcd_gotoxy(1, 1);
                    lcdPrint("  Гiстерезис  ");
                    lcd_gotoxy(1, 2);
                    lcdPrint("Кол(1)/Гол(2):");
                }

                if (pressed_key == KEY_UP_EVENT) {
                    sound_yes = !(sound_yes);
                    select = SEL_MAIN;
                }
                break;
            case SEL_SET_TEMP:// вибір налаштування порогів
                lcd_gotoxy(16, 2);
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
                    if (dq_num == 1) {
                        select = SEL_SET_TEMP_DQ1;
                        sub_sel = SUB_SEL_UP;
                        clearLCD();
                        lcd_gotoxy(1, 1);
                        lcdPrint("    Колона  ");
                        lcd_gotoxy(1, 2);
                        lcdPrint("Темп Верх:");
                    } else {
                        select = SEL_SET_TEMP_DQ2;
                        sub_sel = SUB_SEL_UP;
                        clearLCD();
                        lcd_gotoxy(1, 1);
                        lcdPrint("    Голова  ");
                        lcd_gotoxy(1, 2);
                        lcdPrint("Темп Верх:");
                    }
                }

                break;
            case SEL_SET_TEMP_DQ1:// налаштовуємо пороги датчика колони
                switch (sub_sel) {
                    case SUB_SEL_UP: // верхній поріг спрацювання сигналу
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
                            sub_sel = SUB_SEL_DWN;
                            lcd_gotoxy(1, 2);
                            lcdPrint("Темп Низ:     ");
                        }
                        break;
                    case SUB_SEL_DWN:// нижній поріг спрацювання сигналу
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
                            select = SEL_MAIN;
                            write_eep(EE_TMP1_UP, set_t_dq1_up);
                            write_eep(EE_TMP1_DWN, set_t_dq1_dwn);
                        }
                        break;
                }//end sub_sel

                break;
            case SEL_SET_TEMP_DQ2:// налаштовуємо пороги датчика голови
                switch (sub_sel) {
                    case SUB_SEL_UP: // верхній поріг спрацювання сигналу
                        lcd_gotoxy(11, 2);
                        lcd_putc('+');                        
                        lcd_putc(((set_t_dq2_up / 10) % 10) + 48);
                        lcd_putc('.');
                        lcd_putc(((set_t_dq2_up % 10) + 48));

                        if (pressed_key == KEY_OK_EVENT) {
                            set_t_dq2_up++;
                            if (set_t_dq2_up == 11)
                                set_t_dq2_up = 0;
                        }
                        if (pressed_key == KEY_UP_EVENT) {
                            set_t_dq2_up--;
                            if (set_t_dq2_up == 255)
                                set_t_dq2_up = 10;
                        }
                        if (pressed_key == KEY_BOTH_EVENT) {
                            sub_sel = SUB_SEL_DWN;
                            lcd_gotoxy(1, 2);
                            lcdPrint("Темп Низ:     ");
                        }
                        break;
                    case SUB_SEL_DWN:// нижній поріг спрацювання сигналу
                        lcd_gotoxy(10, 2);
                        lcd_putc('-');
                        lcd_putc(((set_t_dq2_dwn / 10) % 10) + 48);
                        lcd_putc('.');
                        lcd_putc(((set_t_dq2_dwn % 10) + 48));

                        if (pressed_key == KEY_OK_EVENT) {
                            set_t_dq2_dwn++;
                            if (set_t_dq2_dwn == 11)
                                set_t_dq2_dwn = 0;
                        }
                        if (pressed_key == KEY_UP_EVENT) {
                            set_t_dq2_dwn--;
                            if (set_t_dq2_dwn == 255)
                                set_t_dq2_dwn = 10;
                        }
                        if (pressed_key == KEY_BOTH_EVENT) {
                            select = SEL_MAIN;
                            write_eep(EE_TMP2_UP, set_t_dq2_up);
                            write_eep(EE_TMP2_DWN, set_t_dq2_dwn);
                        }
                        break;
                }//end sub_sel
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
    OSCCONbits.IRCF = 0b111; // Внутрішній осцилятор 8MHz
    ADCON1bits.PCFG = 0b1111; // всі порти цифрові

    DQ = 1;

    init_ds18b20();

    T1CON = 0b10000000;
    //T1CONbits.TMR1ON = 0; // вимкнути таймер 1
    TMR1H = HIGH_BYTE(TMR1Val);
    TMR1L = LOW_BYTE(TMR1Val);
    
    T0CONbits.T0PS = 0b000; //таймер 0 дільник 1:1
    T0CONbits.PSA = 1;
    T0CONbits.T08BIT = 0; //16 біт таймер 0
    T0CONbits.T0CS = 0;
    T0CONbits.TMR0ON = 1;
    TMR0H = HIGH_BYTE(TMR0Val);
    TMR0L = LOW_BYTE(TMR0Val);
    INTCONbits.T0IE = 1; // переривання від таймера 0
    INTCON2bits.RBPU = 0; // підтягуючі резистори
    

    
    PIE1bits.TMR1IE = 1; // переивання від таймера 1
    INTCONbits.PEIE = 1; // включити глобальні переивання
    INTCONbits.GIE = 1; // включити переферійні переривання
    initLCD();
    cgrom_char(&symbol_4, 1);
    SND = 0;

}

void Delay_ms(uint16_t delay) {
    for (uint16_t i = 0; i <= delay; i++)
        __delay_ms(1);
}
void interrupt myInt(void) {
    static uint8_t snd_delay;
    if (PIR1bits.TMR1IF == 1) {
        PIR1bits.TMR1IF = 0; // скинути признак переривання від таймера 1
        TMR1H = HIGH_BYTE(TMR1Val);
        TMR1L = LOW_BYTE(TMR1Val);
        if (++timer_val >= 30) // затримка > 750мс
        {
            timer_val = 0;
            time_flag = 1;
            T1CONbits.TMR1ON = 0;

        }
    }
    if (INTCONbits.T0IF == 1) {//відбулося переривання від таймера 0
        INTCONbits.T0IF = 0;
        TMR0H = HIGH_BYTE(TMR0Val);
        TMR0L = LOW_BYTE(TMR0Val);
        read_key = 1;
        if (en_sound) {
            snd_delay++;
            if (snd_delay <= SND_TIME) {
                SND = 1; // включити вивід звуку(активний бузер!)
            } else
                SND = 0; // вимкнути вивід звуку(активний бузер!)
            if(snd_delay > SND_PAUSE)
                snd_delay = 0;
        }else
            SND = 0;
        
    }
    return;
}
