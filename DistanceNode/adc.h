//adc.h
#ifndef _ADC_H_
#define _ADC_H_

#include "types.h"
void Init_ADC(void);
f32 Read_ADC(u8 chNo);
f32 Gp2d12_sensor(u8 chNo);

#endif
