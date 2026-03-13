#include <LPC21xx.H>
#include "types.h"
#include "delay.h"
#include  "lcd_defines.h"
#include "defines.h"

//u8 CGRAM_LUT[]={0X0E,0X0E,0X15,0X0E,0X0E,0X04,0X0A,0X11}; //robot
/*u8 CGRAM_LUT[]={
	0X0E,0X1F,0X11,0X11,0X11,0X11,0X1F,0X1F,
	0X0E,0X1F,0X11,0X11,0X11,0X1F,0X1F,0X1F,
	0X0E,0X1F,0X11,0X11,0X1F,0X1F,0X1F,0X1F,
  0X0E,0X1F,0X11,0X1F,0X1F,0X1F,0X1F,0X1F,
  0X0E,0X1F,0X1F,0X1F,0X1F,0X1F,0X1F,0X1F
};*/

void writeLCD(u8 byte){
//select write operation using rw pin
	//SCLRBIT(IOCLR0,LCD_RW);//p0.17
	
	//write onto data pins any byte (cmd/ascii/value)
   WRITEBYTE(IOPIN0,LCD_DATA,byte);
	
	//provide to high to low transition on enable pin
	//EN high
	SSETBIT(IOSET0,LCD_EN);	//p0.9
	//>=450ns
	delay_us(1);
	//EN low
	SCLRBIT(IOCLR0,LCD_EN);//p0.9
	//delay bt/w consective bytes
	delay_ms(2);
}

void cmdLCD(u8 cmd){
   //select cmd/ins reg 
		SCLRBIT(IOCLR0,LCD_RS);//p0.8
	//and write cmd into it
		writeLCD(cmd);
}

void initLCD(void){
	
  //cfg gpio pins connected to LCD_DATA pins as output pins
		WRITEBYTE(IODIR0,LCD_DATA,0XFF);
  //cfg gpio pin connected to LCD_RS as output pin
		SETBIT(IODIR0,LCD_RS);
  //cfg gpio pin connected to LCD_RW as output pin
	//SETBIT(IODIR1,LCD_RW);
	//cfg gpio pin connected to LCD_EN as output pin
		SETBIT(IODIR0,LCD_EN);
	//wait for 15ms delay after power on/up
		delay_ms(15);
	//function set cmd
		cmdLCD(0x30);
	//wait for >=4.1ms
		delay_ms(5);
	//function set cmd
	 cmdLCD(0x30);
	//wait for >=100us delay
		delay_us(100);
	//function set cmd
	 cmdLCD(0x30);
	
	//establish 8 -bit mode cmd with 2 line
   cmdLCD(0x38);	//cmdLCD(MODE_8BIT_2LINE);
	
	//Disp + cursor cmd as per user requirement
		cmdLCD(0x0f);//cmdLCD(DSP_ON_CUR_BLINK);	
	//clear screen/dsp cmd
		cmdLCD(0x01);//cmdLCD(CLEAR_LCD);	
	//entry mode/move cursor direction
		cmdLCD(0x06);//cmdLCD(SHIFT_CUR_RIGHT);
	
}

void charLCD(u8 ascii){

	//select data reg 
   SSETBIT(IOSET0,LCD_RS);		//p0.8
	//& write asciiVal to ddram via data reg
	writeLCD(ascii);
}	

void strLCD(char *str){
	while(*str)
	{
		charLCD(*str++);
	}
}
void u32LCD(u32 n){
			u8 arr[10];
			s8 i=0;
	    if(n==0){
				charLCD('0');
				return;
			}	    
	    while(n){
			arr[i++]=n%10+48;
				n=n/10;
			}
			for(--i;i>=0;i--){
					charLCD(arr[i]);
				//delay_ms(500);
			}
}
void s32LCD(s32 n){
   if(n<0){
	  charLCD('-');
		n=-n;
	 }
	 u32LCD(n);
	
}
void f32LCD(f32 fnum,u32 ndp)
{  u32 inum;
  
	if(fnum<0){
	  charLCD('-');
		fnum=-fnum;
	 }
   inum = fnum;
	 u32LCD(inum);
	
	 charLCD('.');
	
	 while(ndp--){
		fnum=(fnum-inum)*10;
		inum=fnum;
		//delay_ms(500);
		charLCD(inum+0x30);
	}
	
}
void setcurpos(u8 line,u8 pos){
  if(line==1){
	cmdLCD((0x80+pos));
	}
	else{
	cmdLCD((0xc0+pos));
	}
}
/*void buildCGRAM(u8 *p,u8 byte){
  u8 i;  
	cmdLCD(0x40);
	for(i=0;i<byte;i++){
	charLCD(CGRAM_LUT[i]);
	}
	
	cmdLCD(0x80);
	cmdLCD(0x0c);
	delay_ms(500);
	while(1){
		charLCD(0);
		delay_ms(500);
		cmdLCD(0x02);
		charLCD(1);
  		delay_ms(500);
		cmdLCD(0x02);
		charLCD(2);
		delay_ms(500);
		cmdLCD(0x02);
  		charLCD(3);
		delay_ms(500);
		cmdLCD(0x02);
  		charLCD(4);  
		delay_ms(500);
		cmdLCD(0x02);
	}
} */
