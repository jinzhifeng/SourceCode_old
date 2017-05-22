/*
 * ledpanel16x16.c
 *
 *  Created on: 2017年5月6日
 *      Author: admin
 */

#include "ledpanel16x16.h"

//写绿列数据到595
void WriteGrnColDatTo595(uint8_t GrnColDat)
{
	uint8_t n,tempgdat;
	tempgdat = GrnColDat;
	for(n = 0; n != 8; n++)
	{
		LedPanel_SHCP_Clr();
		if(tempgdat & 0x80)
		{
			LedPanel_Gin_Set();
		}
		else
		{
			LedPanel_Gin_Clr();
		}
		tempgdat <<= 1;
		LedPanel_SHCP_Set();
	}
}

//写红列数据到595
void WriteRedColDatTo595(uint8_t RedColDat)
{
	uint8_t n,temprdat;
	temprdat = RedColDat;
	for(n = 0; n != 8; n++)
	{
		LedPanel_SHCP_Clr();
		if(temprdat & 0x80)
		{
			LedPanel_Rin_Set();
		}
		else
		{
			LedPanel_Rin_Clr();
		}
		temprdat <<= 1;
		LedPanel_SHCP_Set();
	}
}

//写红，绿列数据到595
void WriteRGColDatTo595(uint8_t RedColDat, uint8_t GrnColDat)
{
	uint8_t n, temprdat, tempgdat;
	temprdat = RedColDat;
	tempgdat = GrnColDat;
//	 LedPanel_STCP_Clr();
	for(n = 0; n != 8; n++)
	{
		LedPanel_SHCP_Clr();
		if(temprdat & 0x80)
		{
			LedPanel_Rin_Set();
		}
		else
		{
			LedPanel_Rin_Clr();
		}
		if(tempgdat & 0x80)
		{
			LedPanel_Gin_Set();
		}
		else
		{
			LedPanel_Gin_Clr();
		}
		temprdat <<= 1;
		tempgdat <<= 1;
		LedPanel_SHCP_Set();
	}
//	 LedPanel_STCP_Set();
}

//选择行显示
void SelectRowDisp(uint8_t nRow)
{
	switch(nRow)
	{
		case 15:	LedPanel_D_Clr();LedPanel_C_Clr();LedPanel_B_Clr();LedPanel_A_Clr();break;
		case 14:	LedPanel_D_Clr();LedPanel_C_Clr();LedPanel_B_Clr();LedPanel_A_Set();break;
		case 13:	LedPanel_D_Clr();LedPanel_C_Clr();LedPanel_B_Set();LedPanel_A_Clr();break;
		case 12:	LedPanel_D_Clr();LedPanel_C_Clr();LedPanel_B_Set();LedPanel_A_Set();break;
		case 11:	LedPanel_D_Clr();LedPanel_C_Set();LedPanel_B_Clr();LedPanel_A_Clr();break;
		case 10:	LedPanel_D_Clr();LedPanel_C_Set();LedPanel_B_Clr();LedPanel_A_Set();break;
		case 9:		LedPanel_D_Clr();LedPanel_C_Set();LedPanel_B_Set();LedPanel_A_Clr();break;
		case 8:		LedPanel_D_Clr();LedPanel_C_Set();LedPanel_B_Set();LedPanel_A_Set();break;
		case 7: 	LedPanel_D_Set();LedPanel_C_Clr();LedPanel_B_Clr();LedPanel_A_Clr();break;
		case 6:		LedPanel_D_Set();LedPanel_C_Clr();LedPanel_B_Clr();LedPanel_A_Set();break;
		case 5: 	LedPanel_D_Set();LedPanel_C_Clr();LedPanel_B_Set();LedPanel_A_Clr();break;
		case 4: 	LedPanel_D_Set();LedPanel_C_Clr();LedPanel_B_Set();LedPanel_A_Set();break;
		case 3: 	LedPanel_D_Set();LedPanel_C_Set();LedPanel_B_Clr();LedPanel_A_Clr();break;
		case 2: 	LedPanel_D_Set();LedPanel_C_Set();LedPanel_B_Clr();LedPanel_A_Set();break;
		case 1: 	LedPanel_D_Set();LedPanel_C_Set();LedPanel_B_Set();LedPanel_A_Clr();break;
		case 0: 	LedPanel_D_Set();LedPanel_C_Set();LedPanel_B_Set();LedPanel_A_Set();break;
		default: 	break;
	}
}

void distest(void)
{
   static uint8_t i;


   WriteRGColDatTo595(0xff, graph[ ( 0+i )* 2 ] );
   WriteRGColDatTo595(0xff, graph[ ( 0+i )* 2 + 1 ]);

   LedPanel_STCP_Clr();
   LedPanel_STCP_Set();
   SelectRowDisp(i);

   if(15 == i++) i = 0;
   HAL_Delay(1);
}
