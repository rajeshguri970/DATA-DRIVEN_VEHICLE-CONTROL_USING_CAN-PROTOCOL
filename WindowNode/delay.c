
void delay_us(unsigned int dly)
{
	for(dly=dly*12;dly>0;dly--);                                
}
void delay_ms(unsigned int dly)
{
	for(dly=dly*12000;dly>0;dly--);                                
}
void delay_s(unsigned int dly)
{
	for(dly=dly*12000000;dly>0;dly--);                                
}

