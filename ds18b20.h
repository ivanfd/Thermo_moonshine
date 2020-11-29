#ifndef DS18B20_H
#define	DS18B20_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include "onewire.h"
#include "main.h"

//#define DS18B20_ONE // чи один датчик на лінії
#define DS18B20_MANY // багато датчиків на лінії


const char fract[] = {0,1,1,2,2,3,4,4,5,6,6,7,7,8,9,9}; // дискретність, знак після коми
                                                        //  0/16..., 1/16..., 2/16......
#ifdef DS18B20_ONE
uint8_t readTemp_Single(uint16_t *buf, uint8_t *minus,  uint8_t *time_flag, uint8_t *timer_val);
#endif
#ifdef DS18B20_MANY
uint8_t readTemp_Single(uint8_t num_d, uint16_t *buf, uint8_t *minus, uint8_t *time_flag, uint8_t *timer_val);
#endif
void init_ds18b20(void);

#endif	/* XC_HEADER_TEMPLATE_H */

