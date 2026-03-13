//mainTxNode.c
#include <lpc21xx.h>    
#include "types.h"    
#include "can.h"   
#include "delay.h" 
#include "external_interrupt.h"
#include "pin_function_defines.h"
#include "defines.h"
#include "lcd.h"
#include "ds18b20.h"
#define BUZZER 20 //P1.20

void ds18b20_fn(){
	int temp;
	unsigned char tp,tpd;
	 	
    temp=ReadTemp();  //READING TEMPERATURE FROM DS18B20 USING 1-WIRE PROTOCOL
	tp  = temp>>4;	  //GETTING INTEGER PART
	tpd=temp&0x08?0x35:0x30;//GETTING FRACTIONAL PART
	tpd=tpd-'0';
	cmdLCD(0x94);
	charLCD(0x03);//temp symbol
	strLCD(" Temp ");
	tp-=55;
	
	s32LCD(tp);
	charLCD('.');
	s32LCD(tpd);
	
	charLCD(0xdf);//degree .
	charLCD('C');
}

char flag =0;
u32 Msg_id=0;
u8 Engine_start=0;
 
int main(void)    
{
	struct CAN_Frame txFrame,rxFrame;     
    txFrame.ID=0;
	txFrame.vbf.RTR=0; //data frame   
    txFrame.Data2=0X00;
	

    
	Init_CAN1();//CAN INITIALIZATION
	initLCD();//LCD initialization
   	cmdLCD(0x0c);
	load_custom_chars();//CGRAM SYMBOL STORE

	//BUZZER
	IODIR1|=1<<BUZZER;
	IOSET1=1<<BUZZER;

	//EXTERNAL INTERRUPT....
   	Enable_EINT0();
	Enable_EINT1();
	Enable_EINT2();
	Enable_EINT3();
	
	//DISPLAY....... 1ST LINE 	 
	cmdLCD(0x80);
	strLCD("********AUDI********");
	//2ND LINE.......
	cmdLCD(0xc0);
	strLCD("WINDOW ");
	charLCD(0X00);//up arrow
	charLCD(0X02);//window
	charLCD(0X01);//down arrow
	 
	strLCD("   ");
	charLCD(0X05);	//ENGINE SYMBOL
	charLCD(' ');

	//4TH LINE.......
    cmdLCD(0xd4);
	strLCD("FORWARD       ");
	
	//TEMPATURE FUNCTION...
	ds18b20_fn();
  
    while(1)    
    { 
		   
  		 if(Engine_start){
				cmdLCD(0xCF); 
				strLCD("ON ");
				// CHECK EXTERNAL INTERRUPT STATUS....
				if(READBIT(IOPIN0,14)&&(flag==1)){
		       			flag=0;
		 		}
				if(READBIT(IOPIN0,15)&&(flag==2)){
		       			flag=0;
		 		}

				//TRANSFER TX FRAME.....
		 		delay_ms(500);   
				txFrame.ID= Msg_id;  
        		txFrame.vbf.DLC=1;  
	     		txFrame.Data1=flag;  
		 		CAN1_Tx(txFrame);   
				
						     	
				if(txFrame.ID==3){
		 	 		 	cmdLCD(0xD4);
			 			strLCD("REVERSE ");
						cmdLCD(0xDC);
			 			charLCD(0X04);//robot symbol
			 			charLCD(0X04);//robot symbol
						charLCD(0X04);//robot symbol
			 			CAN1_Rx(&rxFrame);
			 			 
						if((rxFrame.ID==5)&&(rxFrame.Data1<1234)){
			      				cmdLCD(0xDC);
				  				charLCD(' ');
				  				charLCD(' ');
				  			 	charLCD(' ');

				  				IOCLR1=1<<BUZZER;//BUZZER

				  				delay_ms(250);

				  				cmdLCD(0xDC);
				  				charLCD(0X04);//robot symbol
								delay_ms(50);
			      				charLCD(0X04);//robot symbol
								delay_ms(50);
								charLCD(0X04);//robot symbol
				  
				 				IOSET1=1<<BUZZER;//BUZZER           								
			             }								  		 
		        }
		 		else if(txFrame.ID==2){
				        //4TH LINE.......
   			        	cmdLCD(0xd4);
				        strLCD("FORWARD       ");
		       		
						if(flag==1){
			   	       			cmdLCD(0Xc7);
					  			charLCD(' ');
							    delay_ms(250);
					   		    cmdLCD(0xc7);  
					   			charLCD(0X00);
			   			}
			   			else if(flag==2){
			   		   			cmdLCD(0Xc9);
					   			charLCD(' ');
					   			delay_ms(250);
					   			cmdLCD(0xc9);  
					   			charLCD(0X01);			   
			   			}		 
		 		}
	}
	else{
	
	     cmdLCD(0xCF); 
		 strLCD("OFF");  
	}
		     
  }
      
}

