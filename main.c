/*
 * File:   main.c
 * Author: User
 *
 * Created on 24 ноября 2020 г., 15:44
 */


#include <xc.h>
#include "main.h"


uint8_t timer_val = 0, time_flag = 0;  // для конвертування температури
uint16_t temperature;
uint8_t minus;
uint8_t TxtBuf[16];
bit read_key = 0; // дозвіл на читання кнопок
uint8_t pressed_key;
uint8_t select = SEL_MAIN; //де в меню ми знаходимося
uint8_t dq_num = 1;



void main(void) {
    Main_init();
    initLCD();
    lcd_gotoxy(1, 1);
    lcdPrint("---TEMP SENS----");
    lcd_gotoxy(1, 2);
    lcdPrint("(c)Ivan_fd v1.0");
    Delay_ms(2000);
    clearLCD();
    if ((KEY_PORT & (1 << KEY_OK)) == 0) {
        clearLCD();
        select = SEL_SET_DQ;
        lcd_gotoxy(1, 1);
        lcdPrint("   DQ 1 or 2?  ");
        Delay_ms(2000);
    }

    while (1) {
        readTemp_Single(1, &temperature, &minus, &time_flag, &timer_val);

        if (read_key) {
            key_press();
            read_key = 0;
        }
        pressed_key = key_GetKey();// читаємо копку

        switch (select) {
            case SEL_MAIN:
                lcd_gotoxy(1, 1);
                //strcpy(TxtBuf, "Press:");
                TxtBuf[0] = 'T';
                TxtBuf[1] = 'e';
                TxtBuf[2] = 'm';
                TxtBuf[3] = 'p';
                TxtBuf[4] = ':';
                TxtBuf[5] = minus;
                TxtBuf[6] = ((temperature / 100) % 10) + 48;
                TxtBuf[7] = ((temperature / 10) % 10) + 48;
                TxtBuf[8] = '.';
                TxtBuf[9] = ((temperature % 10) + 48);
                TxtBuf[10] = ' ';
                TxtBuf[11] = ' ';
                TxtBuf[12] = ' ';
                TxtBuf[13] = ' ';
                TxtBuf[14] = ' ';
                TxtBuf[15] = 0;
                lcdPrint(TxtBuf);
                if (pressed_key == KEY_OK_EVENT) {
                    lcd_gotoxy(1, 2);
                    //strcpy(TxtBuf, "Press:");
                    TxtBuf[0] = 'P';
                    TxtBuf[1] = 'r';
                    TxtBuf[2] = 'e';
                    TxtBuf[3] = 's';
                    TxtBuf[4] = 's';
                    TxtBuf[5] = ':';
                    TxtBuf[6] = 'O';
                    TxtBuf[7] = 'K';
                    TxtBuf[8] = 0;
                    lcdPrint(TxtBuf);
                }
                if (pressed_key == KEY_UP_EVENT) {
                    lcd_gotoxy(1, 2);
                    //strcpy(TxtBuf, "Press:");
                    TxtBuf[0] = 'P';
                    TxtBuf[1] = 'r';
                    TxtBuf[2] = 'e';
                    TxtBuf[3] = 's';
                    TxtBuf[4] = 's';
                    TxtBuf[5] = ':';
                    TxtBuf[6] = 'U';
                    TxtBuf[7] = 'P';
                    TxtBuf[8] = 0;
                    lcdPrint(TxtBuf);
                }
                if (pressed_key == KEY_BOTH_EVENT) {
                    lcd_gotoxy(1, 2);
                    //strcpy(TxtBuf, "Press:");
                    TxtBuf[0] = 'P';
                    TxtBuf[1] = 'r';
                    TxtBuf[2] = 'e';
                    TxtBuf[3] = 's';
                    TxtBuf[4] = 's';
                    TxtBuf[5] = ':';
                    TxtBuf[6] = 'B';
                    TxtBuf[7] = 'T';
                    TxtBuf[8] = 0;
                    lcdPrint(TxtBuf);
                }

                break;
            case SEL_SET_DQ:
                lcd_gotoxy(1, 2);
                TxtBuf[0] = 'D';
                TxtBuf[1] = 'Q';
                TxtBuf[2] = ':';
                TxtBuf[3] = ' ';
                TxtBuf[4] = dq_num + 48;
                TxtBuf[5] = ' ';
                TxtBuf[6] = ' ';
                TxtBuf[7] = 0;
                lcdPrint(TxtBuf);

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
                    select = SEL_READ_DQ;
                }
                break;
            case SEL_READ_DQ:
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
    
    OSCCONbits.SCS0 = 0;
    OSCCONbits.SCS1 = 1;
    OSCCONbits.IRCF = 0b111; // Внутрішній осцилятор 8MHz
    
    PIE1bits.TMR1IE = 1; // переивання від таймера 1
    INTCONbits.PEIE = 1; // включити глобальні переивання
    INTCONbits.GIE = 1; // включити переферійні переривання


}

void Delay_ms(uint16_t delay) {
    for (uint16_t i = 0; i <= delay; i++)
        __delay_ms(1);
}
void interrupt myInt(void) {
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
    }
    return;
}
