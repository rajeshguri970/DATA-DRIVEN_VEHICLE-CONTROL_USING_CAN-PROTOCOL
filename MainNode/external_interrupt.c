//external_interrupt.c
#include <lpc21xx.h>
#include "pin_function_defines.h"
#include "defines.h"
#include "delay.h"
#include "external_interrupt.h"
#include "types.h"

extern char flag;
extern u32  Msg_id;
extern u8 Engine_start;

void eint0_isr(void) __irq
{
//	CPLBIT(IOPIN1,EINT0_LED);//isr activity
	flag=3;
     Msg_id=3; 
	SSETBIT(EXTINT,0);//clear EINT0 flag
	VICVectAddr=0;//dummy write to clear 
	              //interrupt flag in VIC
  delay_ms(100);	

}

void eint1_isr(void) __irq
{
//	CPLBIT(IOPIN1,EINT1_LED);//isr activity
     Msg_id=2; 
	flag=1;
	SSETBIT(EXTINT,1);//clear EINT1 flag
	VICVectAddr=0;//dummy write;
  delay_ms(100);	

}	


void eint2_isr(void) __irq
{
//	CPLBIT(IOPIN1,EINT2_LED);//isr activity
      Msg_id=2; 
     flag=2;
	SSETBIT(EXTINT,2);//clear  EINT2 flag
	VICVectAddr=0;//dummy write;
  delay_ms(100);	
}	

void eint3_isr(void) __irq
{
//	CPLBIT(IOPIN1,EINT3_LED);//isr activity
    Engine_start^=1;
	SSETBIT(EXTINT,3);//clear flag
	VICVectAddr=0;//dummy write;
	delay_ms(100);
}	

void Enable_EINT0(void)
{
	//CFGPIN(PINSEL0,1,FUNC4);
	CFGPIN(PINSEL1,0,FUNC2);
	
//	SETBIT(IODIR1,EINT0_LED);
	SSETBIT(VICIntEnable,14);
	VICVectCntl0=0x20|14;
	VICVectAddr0=(unsigned)eint0_isr;
	SCLRBIT(EXTINT,0);
  SETBIT(EXTMODE,0);
  //SETBIT(EXTPOLAR,0);
	
}

void Enable_EINT1(void)
{
//	CFGPIN(PINSEL0,3,FUNC4);
	CFGPIN(PINSEL0,14,FUNC3);
//	SETBIT(IODIR1,EINT1_LED);
	SSETBIT(VICIntEnable,15);
	VICVectCntl1=0x20|15;
	VICVectAddr1=(unsigned)eint1_isr;
	SCLRBIT(EXTINT,1);
  SETBIT(EXTMODE,1);
  //SETBIT(EXTPOLAR,1);	
}

void Enable_EINT2(void)
{
	//CFGPIN(PINSEL0,7,FUNC4);
	CFGPIN(PINSEL0,15,FUNC3);
//	SETBIT(IODIR1,EINT2_LED);
	SSETBIT(VICIntEnable,16);
	VICVectCntl2=0x20|16;
	VICVectAddr2=(unsigned)eint2_isr;
	SCLRBIT(EXTINT,2);
  SETBIT(EXTMODE,2);
  //SETBIT(EXTPOLAR,2);	
}

void Enable_EINT3(void)
{
	CFGPIN(PINSEL1,4,FUNC4);
//	SETBIT(IODIR1,EINT3_LED);
	SSETBIT(VICIntEnable,17);
	VICVectCntl3=0x20|17;
	VICVectAddr3=(unsigned)eint3_isr;
	SCLRBIT(EXTINT,3);
  SETBIT(EXTMODE,3);
//  SETBIT(EXTPOLAR,3);	
}

