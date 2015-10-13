/*  github.com/jinzhifeng  */
/*  QQ356290462            */
#include "st7920.h"

/* 延时子程序 */
void Lcd_Delayms(uint32_t n)
{
	uint32_t j,k;
	for(j = 0; j < n; j++)
		for(k = 0; k < 1000; k++);
}

/*	写8个bit指令到LCD  */
void Lcd_WriteCommand(uint8_t WriteCommand)
{
	while(Lcd_BusyFlag());
	Lcd_RS_L();	//0指令1数据
	Lcd_RW_L();	//0写1读
	Lcd_EN_H();	// RS = 0,RW = 0,E = 1 -> 0

	GPIOE->ODR = (GPIOE->ODR & 0x00FF) | (WriteCommand << 8);
//	GPIOE->BSRRH = 0xFF00;	//RESET PE8-15 //用于stm32f4标准库
//	GPIOE->BSRRL = WriteCommand << 8;	//用于stm32f4标准库

	Lcd_EN_L();
}

/*	写8个bit数据到LCD  */
void Lcd_WriteData(uint8_t WriteData)
{
	while(Lcd_BusyFlag());
	Lcd_RS_H();	//0指令1数据
	Lcd_RW_L();	//0写1读
	Lcd_EN_H();	//RS = 1,RW = 0,E = 1 -> 0

	GPIOE->ODR = (GPIOE->ODR & 0x00FF) | (WriteData << 8);
//	GPIOE->BSRRH = 0xFF00;	//RESET PE8-15	//用于stm32f4标准库
//	GPIOE->BSRRL = WriteData << 8;	//用于stm32f4标准库

	Lcd_EN_L();
}

/*	读LCD忙碌标志  */
uint8_t Lcd_BusyFlag(void)
{
	uint8_t BusyFlag;
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;	//切换为输入模式以便检测LCD的DB7电平
	GPIO_InitStruct.Pin = GPIO_PIN_15 ;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	Lcd_RS_L();	//0指令1数据
	Lcd_RW_H();	//0写1读
	Lcd_EN_H();	//RS = 0,RW = 1,E = 1->0
	Lcd_Delayms(1);
	if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_15))
	{
		BusyFlag = 1;
	}
	else
	{
		BusyFlag = 0;
	}
	Lcd_EN_L();

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;	//恢复为输出模式
	GPIO_InitStruct.Pin = GPIO_PIN_15 ;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	return BusyFlag;
}

/*	LCD初始化函数  */
void Lcd_Init(void)
{
	Lcd_PSB_H();							//并口模式(0串口1并口)
	Lcd_Delayms(100);
	Lcd_nRST_L();							//0复位1正常
	Lcd_Delayms(100);
	Lcd_nRST_H();
	Lcd_Delayms(100);
	Lcd_WriteCommand(0x30);		//基本指令操作
	Lcd_Delayms(20);
	Lcd_WriteCommand(0x0C);		//显示开,关光标
	Lcd_Delayms(20);
	Lcd_WriteCommand(0x01);		//清除LCD的显示内容
	Lcd_Delayms(20);
}

/*	LCD显示坐标函数  */
void Lcd_DisplayPos(uint8_t Xpos, uint8_t Ypos)
{
	switch (Xpos)
	{
		case 1: Xpos = 0x80;break;
		case 2: Xpos = 0x90;break;
		case 3: Xpos = 0x88;break;
		case 4: Xpos = 0x98;break;
		default: break;
	}
	Lcd_WriteCommand(Xpos + Ypos);
}

/*	将GDRAM内容全部清零  */
void Lcd_ClrGDRAM(void)
{
  uint8_t i,j;
	Lcd_WriteCommand(0x01);		//清除LCD的显示内容
  Lcd_WriteCommand(0x34);

  for(i = 0; i < 32; i++)
  {
    Lcd_WriteCommand(0x80+i);
    Lcd_WriteCommand(0x80);
    for(j = 0; j < 16; j++)
		{
			Lcd_WriteData(0x00); 	
		}
  }

  for(i=0;i<32;i++)
  {
    Lcd_WriteCommand(0x80+i);
    Lcd_WriteCommand(0x88);
    for(j = 0; j < 16; j++)
		{
			Lcd_WriteData(0x00);	
		}
  }
	Lcd_WriteCommand(0x36);
}

/*	图片显示函数　 */
void Lcd_DisplayBMP(uint8_t *bmp)
{
  uint8_t i,j;
	Lcd_ClrGDRAM();	//先清GDRAM数据
	Lcd_WriteCommand(0x34);
  for(i = 0;i	<	32;	i++)
  {
    Lcd_WriteCommand(0x80+i);
    Lcd_WriteCommand(0x80);
    for(j = 0; j < 16; j++)
		{
			Lcd_WriteData(*bmp++);
		}
  }

  for(i=0;i<32;i++)
  {
    Lcd_WriteCommand(0x80+i);
    Lcd_WriteCommand(0x88);
    for(j	=	0; j < 16; j++)
		{
			Lcd_WriteData(*bmp++);
		}
  }
		Lcd_WriteCommand(0x36);
}

/*	字符串显示函数  */
void Lcd_DisplayString(uint8_t x, uint8_t y, uint8_t ClrString,	uint16_t displaytime, char *String)
{
	uint8_t n;
	Lcd_WriteCommand(0x30);		//基本指令操作
	if(ClrString) Lcd_WriteCommand(0x01);		//如果ClrSting为1则清除LCD的显示内容
	Lcd_DisplayPos(x, y);
	for(n = 0; n < 16; n++)
	{
		Lcd_WriteData(*String++);
		Lcd_Delayms(displaytime);
	}
}


/*  github.com/jinzhifeng  */
/*  QQ356290462            */
