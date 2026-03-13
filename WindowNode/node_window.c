//node_window.c
#include <lpc21xx.h>   
#include"can.h"    
#include "delay.h"

main()   
{   
	struct CAN_Frame rxFrame;   
	u8 window_level=0 , open_close_window=0;
	IODIR0 |=0xFF;
	IOSET0 =0xFF;
	 Init_CAN1();   
	while(1)   
	{   //delay_ms(500);
       CAN1_Rx(&rxFrame);
			 if(rxFrame.ID == 2)
			{
				open_close_window = rxFrame.Data1;		
				if(open_close_window==1)
				{
						for(;window_level<8;window_level++)
						{
							IOCLR0 = 1<<window_level;
							delay_ms(1000);
							window_level++;
							break;
							//CAN1_Rx(&rxFrame);
							//open_close_window = rxFrame.Data1;
/*							if(open_close_window==2)
							{
								window_level++;
								break;
							}
  */
						}
				}
				if(open_close_window == 2)
				{
					for(;window_level>0;window_level--)
					{
						IOSET0 = 1<<(window_level-1);
						delay_ms(1000);
						window_level--;
						break;
						//CAN1_Rx(&rxFrame);
						//open_close_window = rxFrame.Data1;
						/*if(open_close_window==1)
						{
							window_level--;
							break;
						} */
					}

			
				}
		}
					 
	}    
	
}   

