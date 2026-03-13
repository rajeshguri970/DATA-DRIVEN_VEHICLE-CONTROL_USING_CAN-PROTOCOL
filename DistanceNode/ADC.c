//ADC.c
#include <LPC21xx.h>
#include "types.h"
#include "defines.h"
#include "adc_defines.h"
#include "delay.h"

void Init_ADC(void)
{
	PINSEL1|=0x15400000;
  ADCR=PDN_BIT|CLKDIV|CHANNEL_SEL;	

}

f32 Read_ADC(u8 chNo)
{
  u16 adcVal=0;
	f32 eAR;
	WRITEBYTE(ADCR,0,chNo);
	SETBIT(ADCR,ADC_START_BIT);
	delay_us(3);
	while(!READBIT(ADDR,DONE_BIT));
	CLRBIT(ADCR,ADC_START_BIT);
	adcVal=(ADDR>>6)&0x3FF;
	//eAR=((adcVal*3.3)/1023);
//	eAR=(adcVal*(1024.0/5.0));
	eAR = adcVal * (5.0/1023.0);
	return eAR;
}
f32 Gp2d12_sensor(u8 chNo){
  f32 range,ADC_data;  
//	lm=Read_ADC(chNo)*100;
	  ADC_data=Read_ADC(chNo);
	  if(ADC_data >3.0)
	  	return 0.0;
	else if(ADC_data<1.0)
		return 1234.0;
	 // range=(6787.0/(lm-3.0))-4.0;
	  range = 27.86 / (ADC_data-0.42);
	return range;
}
