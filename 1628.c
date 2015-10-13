#include "1628.h"

uint8_t  DispSegCode[]= {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};	 //共阴段码

void SM1628_WriteOneByte(uint8_t WriteByte)
{
	uint8_t n;
	for(n = 0; n < 8; n++)
	{
		SM1628_CLK_L();
		if( WriteByte & 0x01 )
			SM1628_DIO_H();
		else
			SM1628_DIO_L();
		SM1628_CLK_H();
		WriteByte >>= 1;
	}
	SM1628_DIO_H();
}

void SM1628_SendCommand(uint8_t SendCommand)
{
	SM1628_STB_H();
//	Delay_ms(1) ;
	SM1628_STB_L();
	SM1628_WriteOneByte( SendCommand );

}

void SM1628_SendData(uint8_t Addr, uint8_t Data)
{
	SM1628_STB_H();
//	Delay_ms(1) ;
	SM1628_STB_L();
	SM1628_WriteOneByte( Addr | 0xC0 );
	SM1628_WriteOneByte( Data );
}

void SM1628_Display(uint8_t Data1, uint8_t Data2, uint8_t Data3, uint8_t Data4, uint8_t Brightness)
{
	SM1628_SendCommand(0x80 + Brightness);
	SM1628_SendCommand(0x44);
	SM1628_SendData(0x06, DispSegCode[Data1]);
	SM1628_SendData(0x04, DispSegCode[Data2]);
	SM1628_SendData(0x02, DispSegCode[Data3]);
	SM1628_SendData(0x00, DispSegCode[Data4]);
}

void SM1628_Init(void)
{
	SM1628_DIO_H();
	SM1628_CLK_H();
	SM1628_STB_H();
	SM1628_SendCommand(0x00);
//	SM1628_SendCommand(0x88);
	printf("SM1628 Init ok...\r\n");
}

void SM1628_PutDisplayValue(uint16_t DispVal, uint8_t Brightness)
{
	SM1628_Display(DispVal / 1000	% 10, DispVal / 100 % 10, DispVal / 10 % 10, DispVal / 1 % 10, Brightness);
}
