#include <LPC21xx.H>
#include "adc.h"
#include "lcd.h"
#include "can.h"
#include "defines.h"
#include "adc_defines.h"
#include "delay.h"

u32 Distance;
void read_distance()
{
	u8 samples = 3;
	
	  //while(samples--)
	  {
	  
		Distance=Gp2d12_sensor(CH0);
		delay_ms(500);
      }
	cmdLCD(0xc0);
	strLCD("Dist - ");
	u32LCD(Distance);
	strLCD("cm");
	//delay_s(4);
}
main()   
{   
	struct CAN_Frame rxFrame , txFrame;
	txFrame.ID=5;   txFrame.vbf.RTR=0; //data frame   
 	txFrame.Data2=0X00;       
	Init_CAN1();   
    initLCD();
    Init_ADC();
	cmdLCD(0x0c);
	while(1)   
	{   
		
		 delay_ms(500);
         CAN1_Rx(&rxFrame);
		 cmdLCD(0x01);
		 charLCD('A');
		 u32LCD(rxFrame.ID);

		if(rxFrame.ID == 3)
		{	
			read_distance();
			txFrame.vbf.DLC=4;  
	   		txFrame.Data1=Distance;  
			CAN1_Tx(txFrame);
		}

				    
	}    
	
}   

