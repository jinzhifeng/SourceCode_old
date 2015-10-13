/*  github.com/jinzhifeng  */
/*  QQ356290462            */
#include "ds18b20.h"

DS18B20_CheckState DS18B20_Init(void)
/**
* \brief       Init Ds18b20 初始化
*
* \param       None
*
* \retval      AckFlag
*/
{
	DS18B20_CheckState AckFlag;
	DS18B20_DQ_H();	//释放总线为高电平初始态
	DS18B20_DelayXus(100);
	DS18B20_DQ_L();	//拉低总线
	DS18B20_DelayXus(500);	//精确延时,维持至少480us
	DS18B20_DQ_H();	//释放总线
	DS18B20_DelayXus(50);	//等待15-60us后,检测ds18b20是否发出的60-240us低电平存在脉冲	
	if(ReadPin_DS18B20_DQ() == GPIO_PIN_RESET)	//读DS18B20是否发出低电平存在脉冲
	{
		AckFlag = DS18B20_Exist;
//		printf("检测到DS18B20温度传感器...\r\n");
	}
	else 
	{
		AckFlag = DS18B20_NotExist;
		printf("未检测到DS18B20温度传感器...请检查线路!\r\n");
	}
	DS18B20_DelayXus(100);
	return AckFlag;
}

uint8_t DS18B20_ReadOneByte(void)
/**
* \brief       主机向Ds18b20读1个字节的数据
*
* \param       None
*
* \retval      RdData
*/
{
	uint8_t i, ReadData = 0; //必须将默认值设为0，否则需要加ReadData &= 0x7F;
	for(i = 0; i < 8; i++)
	{
		DS18B20_DQ_L();	//拉低总线
		DS18B20_DelayXus(1);
		DS18B20_DQ_H();	//释放总线
		ReadData >>= 1;	//准备下一位
		if(ReadPin_DS18B20_DQ())
			ReadData |= 0x80;
		else 
			ReadData &= 0x7F;
	  DS18B20_DelayXus(65);
		DS18B20_DQ_H();	//释放总线
	}
	return ReadData;
}

void DS18B20_WriteOneByte(uint8_t WriteByte)
/**
* \brief       主机向Ds18b20写1个字节的数据
*
* \param       WriteByte
*
* \retval      None
*/
{
	uint8_t i;
	for(i = 0; i < 8; i++)
	{
		DS18B20_DQ_L();	//拉低总线
		if(WriteByte & 0x01)
			DS18B20_DQ_H();	//释放总线
		else
			DS18B20_DQ_L();	//拉低总线
		DS18B20_DelayXus(65);
		DS18B20_DQ_H();	//释放总线
		WriteByte >>= 1;	//准备下一位
	}
}

float Get_DS18B20_Temperature(void)
/**
* \brief       主机向Ds18b20读温度值
*
* \param       None
*
* \retval      Temperature
*/
{
	uint8_t TL, TH;
	float Temperature;
	DS18B20_Init();
	DS18B20_WriteOneByte(0xCC);	//跳过读序列号的操作
	DS18B20_WriteOneByte(0x44);	//启动温度转换
	DS18B20_DelayXus(20);
	DS18B20_Init();
	DS18B20_WriteOneByte(0xCC);	//跳过读序列号的操作
	DS18B20_WriteOneByte(0xBE);	//读温度寄存器,共9个byte,前两个byte为温度值
	TL = DS18B20_ReadOneByte();	//TL存低字节
	TH = DS18B20_ReadOneByte();	//TH存高字节
	TH <<= 4;
	TH += (TL & 0xF0) >> 4;
	Temperature = TH;
	
	return Temperature;
}

volatile void DS18B20_DelayXus(uint32_t DelayXus)
/**
* \brief       延时子程序,延时DelayXus微秒
*
* \param       DelayXus
*
* \retval      None
*/
{
	uint32_t dwCurCounter = 0;
  uint32_t dwPreTickVal = SysTick->VAL;
  uint32_t dwCurTickVal;
  DelayXus = DelayXus * (HAL_RCC_GetHCLKFreq() / 1000000);
  for(;;)
  {
		dwCurTickVal = SysTick -> VAL;
    if(dwCurTickVal < dwPreTickVal)
		{
      dwCurCounter = dwCurCounter + dwPreTickVal - dwCurTickVal;
    }
    else
		{
      dwCurCounter = dwCurCounter + dwPreTickVal + SysTick->LOAD - dwCurTickVal;
    }
    dwPreTickVal = dwCurTickVal;
    if(dwCurCounter >= DelayXus)
		{
      return;
    }
  }
}

/*  github.com/jinzhifeng  */
/*  QQ356290462            */
