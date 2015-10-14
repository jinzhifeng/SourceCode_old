/*  github.com/jinzhifeng  */
/*  QQ356290462            */
#ifndef __DS18B20_H
#define __DS18B20_H

#include "stm32f4xx_hal.h"

/*	概述
DS18B20数字温度传感器提供9-12位摄氏度温度测量数据，可编程非易失存储器设置温度监测的上限和下限，提供温度报警。
DS18B20通过1-Wire总线通信，只需要一条数据线 (和地线) 即可与处理器进行数据传输。器件可以工作在-55°C至+125°C范围，在-10°C至+85°C范围内测量精度为±0.5°C。
此外，DS18B20还可以直接利用数据线供电 (寄生供电)，无需外部电源。
每个DS18B20具有唯一的64位序列号，从而允许多个DS18B20挂接在同一条1-Wire总线。
可以方便地采用一个微处理器控制多个分布在较大区域的DS18B20。该功能非常适合HVAC环境控制、楼宇/大型设备/机器/过程监测与控制系统内部的温度测量等应用。 	
关键特性:
					独特的1-Wire?接口仅占用一个通信端口
					内置温度传感器和EEPROM减少外部元件数量
					测量温度范围：-55°C至+125°C (-67°F至+257°F)
					-10°C至+85°C温度范围内测量精度为±0.5°C
					9位至12位可编程分辨率
					无需外部元件
					寄生供电模式下只需要2个操作引脚(DQ和GND)
					多点通信简化分布式温度测量
					每个器件具有唯一的64位序列号，存储在器件ROM内
					用户可灵活定义温度报警门限，通过报警搜索指令找到温度超出门限的器件
					提供8引脚SO(150 mils)、8引脚μSOP、3引脚TO-92封装										
*/

typedef enum	//声明一个枚举类型
{
	DS18B20_Exist,
	DS18B20_NotExist = 0
}DS18B20_CheckState;	//定义枚举类型名称

/* DS18B20 PORT Define */
#define DS18B20_DQ_SET() 				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET)		//PD13
#define DS18B20_DQ_CLR() 				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET)	//PD13
#define ReadPin_DS18B20_DQ() 	HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_8)								//PD13

#define SEARCH_ROM 0xF0
#define READ_ROM 0x33
#define MATCH_ROM 0x55
#define SKIP_ROM 0xCC
#define ALARM_SEARCH 0xEC
 
#define READ_SCRATCHPAD 0xBE
#define CONVERT_T 0x44
#define WRITE_SCRATCHPAD 0x4E
#define COPY_SCRATCHPAD 0x48
#define RECALL_EE 0xB8
#define READ_POWER_SUPPLY 0xB4

/* DS18B20 Function Define */
DS18B20_CheckState DS18B20_Init(void);
volatile void DS18B20_DelayXus(uint32_t DelayXus);
uint8_t DS18B20_ReadOneByte(void);
void DS18B20_WriteOneByte(uint8_t WriteByte);
float Get_DS18B20_Temperature(void);

#endif

/*  github.com/jinzhifeng  */
/*  QQ356290462            */
