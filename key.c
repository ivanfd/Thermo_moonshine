#include "key.h"
volatile uint8_t key_pressed;

uint8_t keyLong = KEY_SHORT;


void key_press(void)
{
    static uint16_t count = 0;
    uint8_t key;
    if (((KEY_PORT & (1 << KEY_OK)) == 0) && ((KEY_PORT & (1 << KEY_UP)) == 0))
        key = KEY_BOTH_EVENT;
    else if ((KEY_PORT & (1 << KEY_OK)) == 0)
        key = KEY_OK_EVENT;
    else if ((KEY_PORT & (1 << KEY_UP)) == 0)
        key = KEY_UP_EVENT;
    else
        key = KEY_NULL;


    if (key) {// якщо перемінна key не нульова
        if (count > DELAYKEY2) {
            count = DELAYKEY2 - 20;
            key_pressed = key;
            keyLong = KEY_LONG;
            return;
        } else count++;

        if (count == DELAYKEY) {
            key_pressed = key;
            keyLong = KEY_SHORT;
            return;
        }
    } else count = 0;
        
        //якщо кнопка утримується довго
//        if (count == DELAYKEY) {
//            count = DELAYKEY + 10;
//            key_pressed = key;   //записуємо її номер в буфер 
//
//            return;
//        } else
//            if (count < (DELAYKEY + 5))
//            count++;
//
//    }
//    else count = 0;
}

//Отримати код кнопки

uint8_t key_GetKey(void)
{
  uint8_t key = key_pressed;
  
  key_pressed = KEY_NULL;
  return key;
}
