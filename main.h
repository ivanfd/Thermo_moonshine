/* 
 * File:   main.h
 * Author: User
 *
 * Created on 24 ноября 2020 г., 15:45
 */
#ifndef MAIN_H
#define	MAIN_H

// PIC18F2320 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = INTIO2     // Oscillator Selection bits (Internal RC oscillator, port function on RA6 and port function on RA7)
#pragma config FSCM = OFF       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Switchover bit (Internal/External Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer enable bit (PWRT enabled)
#pragma config BOR = ON         // Brown-out Reset enable bit (Brown-out Reset enabled)
#pragma config BORV = 27        // Brown-out Reset Voltage bits (VBOR set to 2.7V)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBAD = DIG       // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVR = ON        // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000200-0007FFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (000800-000FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (001000-0017FFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (001800-001FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0001FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000200-0007FFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (000800-000FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (001000-0017FFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (001800-001FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0001FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000200-0007FFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (000800-000FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (001000-0017FFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (001800-001FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0001FFh) is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdio.h>
#include "key.h"
#include "hd44780.h"
#include "ds18b20.h"
#include "onewire.h"
#include "eeprom.h"
#include "eusart.h"

#define FALSE 0
#define TRUE 1

#define _XTAL_FREQ  8000000 // чатота контролера 8МГц


#define TMR1Val 15536 
#define TMR0Val 45536 //частота переривання при дільнику 1:1 буде 25мс


#define SEL_MAIN 1 // основне меню
#define SEL_SET_DQ 2 // налаштування датчиків
#define SEL_STOP 3 // прочитати код датчика
#define SEL_SET_TEMP 4 //налаштування гістерезису температури
#define SEL_SET_TEMP_DQ1 5 //налаштування гістерезису температури
#define SEL_SET_TEMP_DQ2 6 //налаштування гістерезису температури
#define SEL_DQ_SND 7 //вибір - звук, чи читання датчиків
#define SEL_EN_SND 8 //вибір - звук, звук для конкретного датчика

#define SUB_SEL_UP 1
#define SUB_SEL_DWN 2

#define SUB_MAIN_1 1
#define SUB_MAIN_2 2


enum menuCube{VAL_1, VAL_2, VAL_3, VAL_4, VAL_5, VAL_6, VAL_7, VAL_8, VAL_9, VAL_10};


#define EE_TMP1_UP 16  // адреси еепром
#define EE_TMP1_DWN 17 // температури  
#define EE_TMP2_HI 18  // аварії
#define EE_TMP2_LO 19
#define EE_TMP1_FIX 20 //зафіксована температура датчика 1
#define EE_TMP2_FIX 22 // зафіксована температура датчика 2

#define EE_PRESET_1_H 23
#define EE_PRESET_1_L 24
#define EE_PRESET_2_H 25
#define EE_PRESET_2_L 26
#define EE_PRESET_3_H 27
#define EE_PRESET_3_L 28
#define EE_PRESET_4_H 29
#define EE_PRESET_4_L 30
#define EE_PRESET_5_H 31
#define EE_PRESET_5_L 32
#define EE_PRESET_6_H 33
#define EE_PRESET_6_L 34
#define EE_PRESET_7_H 35
#define EE_PRESET_7_L 36
#define EE_PRESET_8_H 37
#define EE_PRESET_8_L 38
#define EE_PRESET_9_H 39
#define EE_PRESET_9_L 40
#define EE_PRESET_10_H 41
#define EE_PRESET_10_L 42



#define SND LATCbits.LATC4 //порт динаміка
#define LED_ON LATCbits.LATC5 // підсвітка
#define SND_TIME_K 10 // Довжина звуку
#define SND_PAUSE_K 80 // пауза між виводом звуку
#define SND_TIME_B 15 // Довжина звуку
#define SND_PAUSE_B 50 // пауза між виводом звуку
#define SND_TIME_ALL 10 // Довжина звуку
#define SND_PAUSE_ALL 25 // пауза між виводом звуку
#define DEBUG_OUT


void Main_init(void);
void Delay_ms(uint16_t delay);
void outValPreset(void);

//
#endif	

