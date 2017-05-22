/*
 * rgbled_P9813.c
 *
 *  Created on: 2017年5月18日
 *      Author: jinzhifeng
 *      https://github.com/jinzhifeng
 */
#include "rgbled_p9813.h"

//先将数据口置0，然后发生32个时钟脉冲，相当于发送32个bit 0
void Send32BitZero(void)
{
	int8_t i;
	RGBLed_P9813_Data_Clr(); //前32 位“0”为起始帧，在Cin 上升沿时打入，并且时序DIN要先于CIN；
	for(i = 0; i != 32; i++)
	{
		RGBLed_P9813_Clk_Clr();	//CLK = 0
		RGBLed_P9813_Delay();
		RGBLed_P9813_Clk_Set();	//CLK = 1
		RGBLed_P9813_Delay();
	}
}

//返回输入参数的反码值
uint8_t CovertToOnesComplement(uint8_t Data)
{
	uint8_t tempData = 0;
	tempData =  ((~Data) & 0xC0) >> 6; //将Data的数转换成反码
	return tempData;
}


void RGBLed_P9813_SendRGBData(uint8_t rDATA, uint8_t gDATA, uint8_t bDATA)
{
	uint32_t rgbdatTemp = 0;
	int8_t i;
	//先将R、G、B、值分别取反码
	rgbdatTemp |= (uint32_t)0x03 << 30; //标志位为两个“1”
	rgbdatTemp |= (uint32_t)CovertToOnesComplement(bDATA) << 28;
	rgbdatTemp |= (uint32_t)CovertToOnesComplement(gDATA) << 26;
	rgbdatTemp |= (uint32_t)CovertToOnesComplement(rDATA) << 24;
	rgbdatTemp |= (uint32_t)bDATA << 16;
	rgbdatTemp |= (uint32_t)gDATA << 8;
	rgbdatTemp |= rDATA;
//32位数据格式：11 00 00 00 00 00 0000 g7 g6 g5 g4 g3 g2 g1 g0 r7 r6 r5 r4 r3 r2 r1 r0
//
	for(i = 0; i != 32; i++)
	{
		if(rgbdatTemp & 0x80000000)
			RGBLed_P9813_Data_Set();
		else RGBLed_P9813_Data_Clr();
		rgbdatTemp <<= 1;	//先传高位后传低位

		RGBLed_P9813_Clk_Clr();	//CLK = 0
		RGBLed_P9813_Delay();
		RGBLed_P9813_Clk_Set();	//CLK = 1
		RGBLed_P9813_Delay();
	}
}


void RGBLed_P9813_Init(void)
{
	Send32BitZero();
	RGBLed_P9813_SetRGBValue(0, 0, 0);
	RGBLed_P9813_SetRGBValue(0, 0, 0);
}

void RGBLed_P9813_SetRGBValue(uint8_t rValue, uint8_t gValue, uint8_t bValue)
{
	RGBLed_PowerON();
	Send32BitZero();
	RGBLed_P9813_SendRGBData(rValue, gValue, bValue);
	RGBLed_P9813_SendRGBData(rValue, gValue, bValue);
}
