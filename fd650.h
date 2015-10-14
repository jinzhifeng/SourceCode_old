/*  github.com/jinzhifeng  */
/*  QQ : 356290462         */
/* jin-zhifeng@hotmail.com */
#ifndef __FD650_H
#define __FD650_H

#include "stm32f4xx_hal.h"

/* FD650 PORT Define */
#define FD650_SDA_SET() 		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET)	   //FD650-SDA端口分配
#define FD650_SDA_CLR() 		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET)  //FD650-SDA端口分配
#define FD650_SDA_READ()		HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_15)									 //FD650-SDA端口分配
#define FD650_SDA_D_OUT()		;//SDA_GPIO口设置为输出模式（无上下拉）
#define FD650_SDA_D_IN()		;//SDA_GPIO口设置为输入模式

#define FD650_SCL_SET() 		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET)	   //FD650-SCL端口分配
#define FD650_SCL_CLR() 		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET)  //FD650-SCL端口分配


/* FD650 Function Define */
#define FD650_BIT_ENABLE					0x01					//开启/关闭位
#define FD650_BIT_SLEEP						0x04					//睡眠控制位
#define FD650_BIT_7SEG						0x08					//7段控制位
#define FD650_BIT_INTENS1					0x10					//1级亮度
#define FD650_BIT_INTENS2					0x20					//2级亮度
#define FD650_BIT_INTENS3					0x30					//3级亮度
#define FD650_BIT_INTENS4					0x40					//4级亮度
#define FD650_BIT_INTENS5					0x50					//5级亮度
#define FD650_BIT_INTENS6					0x60					//6级亮度
#define FD650_BIT_INTENS7					0x70					//7级亮度
#define FD650_BIT_INTENS8					0x00					//8级亮度

#define FD650_SYSOFF				0x0400															//关闭显示、关闭键盘
#define FD650_SYSON				( FD650_SYSOFF | FD650_BIT_ENABLE )		//开启显示、键盘
#define FD650_SLEEPOFF		FD650_SYSOFF													//关闭睡眠
#define FD650_SLEEPON			( FD650_SYSOFF | FD650_BIT_SLEEP )		//开启睡眠
#define FD650_7SEG_ON			( FD650_SYSON | FD650_BIT_7SEG )			//开启七段模式
#define FD650_8SEG_ON			( FD650_SYSON | 0x00 )								//开启八段模式
#define FD650_SYSON_1			( FD650_SYSON | FD650_BIT_INTENS1 )		//开启显示、键盘、1级亮度
//以此类推
#define FD650_SYSON_4			( FD650_SYSON | FD650_BIT_INTENS4 )		//开启显示、键盘、4级亮度
//以此类推
#define FD650_SYSON_8			( FD650_SYSON | FD650_BIT_INTENS8 )		//开启显示、键盘、8级亮度


//加载字数据命令
#define FD650_DIG0					0x1400				//数码管位0显示,需另加8位数据
#define FD650_DIG1					0x1500				//数码管位1显示,需另加8位数据
#define FD650_DIG2					0x1600				//数码管位2显示,需另加8位数据
#define FD650_DIG3					0x1700				//数码管位3显示,需另加8位数据
#define FD650_DOT						0x0080				//数码管小数点显示

//读取按键代码命令
#define FD650_GET_KEY				0x0700				//获取按键,返回按键代码

//延时宏定义
#define FD650_DELAY()				HAL_Delay(1)

typedef struct
{
	uint8_t character;
	uint8_t bitmap;
}
LED_Bitmap_Typedef;


void FD650_Start(void);
void FD650_Stop(void);
void FD650_WriteOneByte(uint8_t WriteByte);
uint8_t FD650_ReadOneByte(void);
void FD650_WriteCommand(uint16_t WriteCommand);
void FD650_Display_All(void);
void FD650_Display_Clean(void);
void FD650_Display(uint8_t Data1, uint8_t Data2, uint8_t Data3, uint8_t Data4, uint8_t Brightness);
void FD650_PutDisplayValue(uint16_t DispVal, uint8_t Brightness);

#endif

/*  github.com/jinzhifeng  */
/*  QQ : 356290462         */
/* jin-zhifeng@hotmail.com */
