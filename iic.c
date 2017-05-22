/*
 * iic.c
 *
 *  Created on: 2017年5月16日
 *      Author: jinzhifeng
 *      https://github.com/jinzhifeng
 */
#include "iic.h"

void IIC_Start(void)
/**
* \brief       IIC_Start
*
* \param       None
*
* \retval      None
*/
/* I2c起始信号：当SCL为高期间，SDA由高到低的跳变（即SCL为高，SDA下降沿跳变）*/
{
	IIC_SdaOutPutMode(); //SDA输出模式
	IIC_SCL_Set();	//SCL拉高

	IIC_SDA_Set(); //SDA下降沿
	IIC_Delay();
	IIC_SDA_Clr();
	IIC_Delay();

    IIC_SCL_Clr();	//钳住I2C总线，准备发送或者接收数据(也可以不拉低,但是每次写bit或者读bit之前要先拉低)
}

void IIC_Stop(void)
/**
* \brief       IIC_Stop
*
* \param       None
*
* \retval      None
*/
/* I2c停止信号：当SCL为高期间，SDA由低到高的跳变（即SCL为高，SDA上升沿跳变）*/
{
	IIC_SdaOutPutMode(); //SDA输出模式
	IIC_SCL_Set();	//SCL拉高

	IIC_SDA_Clr(); //SDA上升沿跳变
	IIC_Delay();
	IIC_SDA_Set();
	IIC_Delay();
}


uint8_t IIC_ReadOneByte(void)
/**
* \brief       主机从器件读一个8位字节的数据
*
* \param       None
*
* \retval      ReadByte
*/
{
	uint8_t i, ReadOneByte = 0;
	IIC_SdaInPutMode(); //SDA读数据先设置为输入模式
	for(i = 0; i != 8; i++)
	{
		IIC_SCL_Set();
		IIC_Delay();
		ReadOneByte <<= 1;
		if(IIC_ReadSdaPin()) ReadOneByte++; //ReadOneByte = ReadOneByte | 0x01;
		IIC_SCL_Clr();
    IIC_Delay();
	}
	IIC_SdaOutPutMode(); //读完8位数据后复位为输出模式
	return ReadOneByte;
}

IIC_ACK_Typedef IIC_WriteOneByte(uint8_t WriteOneByte)
/**
* \brief       主机向设备写一个8位字节的数据
*
* \param       WriteOneByte
*
* \retval      IIC_AckState	(IIC_ACK：接收器接收一个字节成功，IIC_NACK：接收器接收一个字节失败)
*/
/* 发送器每发送一个字节，就在时钟脉冲9期间释放数据线，由接收器反馈一个应答信号。
	应答信号为低电平时，规定为有效应答位（ACK简称应答位），表示接收器已经成功地接收了该字节；
  应答信号为高电平时，规定为非应答位（NACK），一般表示接收器接收该字节没有成功。
  对于反馈有效应答位ACK的要求是，接收器在第9个时钟脉冲之前的低电平期间将SDA线拉低，并且确保在该时钟的高电平期间为稳定的低电平。
  如果接收器是主控器，则在它收到最后一个字节后，发送一个NACK信号，以通知被控发送器结束数据发送，并释放SDA线，以便主控接收器发送一个停止信号P
*/
{
	uint8_t i;
	IIC_ACK_Typedef IIC_AckState;
	IIC_SdaOutPutMode(); //SDA输出模式
	for(i = 0; i != 8; i++)
	{
		if(WriteOneByte & 0x80)
		{
			IIC_SDA_Set();
		}
		else
		{
			IIC_SDA_Clr();
		}
		IIC_Delay();
		IIC_SCL_Set();
		IIC_Delay();
		IIC_SCL_Clr(); //每个时钟脉冲期间传输一个数据位。SDA上的数据

		WriteOneByte <<= 1; //准备下一位（从高位往低位写）
	}

	IIC_SdaInPutMode(); //SDA输入模式
	IIC_Delay();
	IIC_SCL_Set();


	if(IIC_ReadSdaPin() == 0)
	{
		IIC_AckState = IIC_ACK;
//		printf("IIC_ACK：设备接收数据成功！\r\n");
	}
	else
	{
		IIC_AckState = IIC_NACK;
		printf("IIC_NACK：设备接收数据失败！\r\n");
	}
	IIC_Delay();
	IIC_SCL_Clr();
	IIC_Delay();
	IIC_SdaOutPutMode(); 	//SDA输出模式
	return IIC_AckState;	//返回设备应答位
}

void IIC_SdaOutPutMode(void)  //SDA_GPIO口设置为输出模式
{
	  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __GPIOF_CLK_ENABLE();
  GPIO_InitStruct.Pin = Lcd1602_sda_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  HAL_GPIO_Init(Lcd1602_sda_GPIO_Port, &GPIO_InitStruct);
}

void IIC_SdaInPutMode(void)  //SDA_GPIO口设置为输入模式（上拉）
{
	  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __GPIOF_CLK_ENABLE();
  GPIO_InitStruct.Pin = Lcd1602_sda_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  HAL_GPIO_Init(Lcd1602_sda_GPIO_Port, &GPIO_InitStruct);
}

volatile void IIC_DelayXus(uint32_t DelayXus)
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
  DelayXus *= (HAL_RCC_GetHCLKFreq() / 1000000);
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
