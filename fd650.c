/*  github.com/jinzhifeng  */
/*  QQ : 356290462         */
/* jin-zhifeng@hotmail.com */
#include "fd650.h"

/* the numbering of the frontpanel LED:
           --0--
         5|     |1
           --6--
         4|     |2
           --3-- .7
*/
uint8_t  FD650_DispSegCode[]= {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};	 //共阴段码
const LED_Bitmap_Typedef BCD_decode_tab[] =
{
	{'0', 0x3F}, {'1', 0x06}, {'2', 0x5B}, {'3', 0x4F},
	{'4', 0x66}, {'5', 0x6D}, {'6', 0x7D}, {'7', 0x07},
	{'8', 0x7F}, {'9', 0x6F}, {'a', 0x77}, {'A', 0x77},
	{'b', 0x7C}, {'B', 0x7C}, {'c', 0x58}, {'C', 0x39},
	{'d', 0x5E}, {'D', 0x5E}, {'e', 0x79}, {'E', 0x79},
	{'f', 0x71}, {'F', 0x71}, {'L', 0x38}, {'P', 0x73},
	{'r', 0x50}, {'t', 0x78}, {'n', 0x54}, {'o', 0x5c},
	{'U', 0x3e}, {'s', 0x6D}, {'H', 0x76}, {'h', 0x74},
	{'-', 0x40}, {'N', 0x37}, {'O', 0x3F},
};//BCD码字映射


void FD650_Start(void)
/**
* \brief       FD650_Start
*
* \param       None
*
* \retval      None
*/
{
	FD650_SDA_D_OUT(); 	//SDA输出模式
	FD650_SDA_SET();
	FD650_SCL_SET();
	FD650_DELAY();
	FD650_SDA_CLR();
	FD650_DELAY();
	FD650_SCL_CLR();
}

void FD650_Stop(void)
/**
* \brief       FD650_Stop
*
* \param       None
*
* \retval      None
*/
{
	FD650_SDA_D_OUT(); 	//SDA输出模式
	FD650_SDA_CLR();
	FD650_DELAY();
	FD650_SCL_SET();
	FD650_DELAY();
	FD650_SDA_SET();
	FD650_DELAY();
	FD650_SDA_D_IN();		//SDA输入模式
}

void FD650_WriteOneByte(uint8_t WriteByte)
/**
* \brief       Write One Byte data
*
* \param       WriteByte
*
* \retval      None
*/
{
	uint8_t i;
	FD650_SDA_D_OUT(); 	//SDA输出模式
	for(i = 0; i != 8; i++)
	{
		if(WriteByte & 0x80)
		{
			FD650_SDA_SET();
		}
		else
		{
			FD650_SDA_CLR();
		}
	  FD650_DELAY();
		FD650_SCL_SET();
		WriteByte <<= 1;
		FD650_DELAY();
	  FD650_SCL_CLR();
	}
	FD650_SDA_D_IN();		//SDA输入模式
	FD650_SDA_SET();
	FD650_DELAY();
	FD650_SCL_SET();
	FD650_DELAY();
	FD650_SCL_CLR();
}

uint8_t FD650_ReadOneByte(void)
/**
* \brief       Read One Byte data
*
* \param       WriteByte
*
* \retval      None
*/
{
	uint8_t i, ReadByte = 0;
	FD650_SDA_SET();
	FD650_SDA_D_IN();		//SDA输入模式
	for(i = 0; i != 8; i++)
	{
		FD650_DELAY();
		FD650_SCL_SET();
		FD650_DELAY();
		ReadByte <<= 1;
		if(FD650_SDA_READ()) ReadByte++;
		FD650_SCL_CLR();
	}
	FD650_SDA_SET();
	FD650_DELAY();
	FD650_SCL_SET();
	FD650_DELAY();
	FD650_SCL_CLR();
	return ReadByte;
}

void FD650_WriteCommand(uint16_t WriteCommand)
/**
* \brief       通过发送命令参数
*
* \param       WriteCommand
*
* \retval      None
*/
{
	FD650_Start();
	FD650_WriteOneByte(((uint8_t)((WriteCommand >> 7) & 0x3E) | 0x40));
	FD650_WriteOneByte((uint8_t)WriteCommand);
	FD650_Stop();
}

void FD650_Display_All(void)
/**
* \brief       display all
*
* \param       None
*
* \retval      None
*/
{
	FD650_WriteCommand(FD650_SYSON_8);
	FD650_WriteCommand(FD650_DIG0 | 0xFF);
	FD650_WriteCommand(FD650_DIG1 | 0xFF);
	FD650_WriteCommand(FD650_DIG2 | 0xFF);
	FD650_WriteCommand(FD650_DIG3 | 0xFF);
}

void FD650_Display_Clean(void)
/**
* \brief       not display all
*
* \param       None
*
* \retval      None
*/
{
	FD650_WriteCommand(FD650_SYSON_8);
	FD650_WriteCommand(FD650_DIG0 | 0x00);
	FD650_WriteCommand(FD650_DIG1 | 0x00);
	FD650_WriteCommand(FD650_DIG2 | 0x00);
	FD650_WriteCommand(FD650_DIG3 | 0x00);
}

void FD650_Display(uint8_t Data1, uint8_t Data2, uint8_t Data3, uint8_t Data4, uint8_t Brightness)
/**
* \brief       not display all
*
* \param       None
*
* \retval      None
*/
{
	FD650_WriteCommand(FD650_SYSON | Brightness);
	FD650_WriteCommand(FD650_DIG0 | FD650_DispSegCode[Data1]);
	FD650_WriteCommand(FD650_DIG1 | FD650_DispSegCode[Data2]);
	FD650_WriteCommand(FD650_DIG2 | FD650_DispSegCode[Data3]);
	FD650_WriteCommand(FD650_DIG3 | FD650_DispSegCode[Data4]);
}

void FD650_PutDisplayValue(uint16_t DispVal, uint8_t Brightness)
{
	FD650_Display(DispVal / 1000	% 10, DispVal / 100 % 10, DispVal / 10 % 10, DispVal / 1 % 10, Brightness);
}


/*  github.com/jinzhifeng  */
/*  QQ : 356290462         */
/* jin-zhifeng@hotmail.com */
