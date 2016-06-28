#include <stm32f4xx_hal.h>
#include "1628.h"

#ifdef __cplusplus
extern "C"
#endif
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void GPIO_Init(void);
void scan_encoder(void);

#define PINA	HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13)
#define PINB	HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14)
uint8_t counter = 0;

int main(void)
{
	HAL_Init();
	GPIO_Init();
	
	SM1628_Init();

	for (;;)
	{
		scan_encoder();
		SM1628_PutDisplayValue(counter, 10);
	}
}

void GPIO_Init(void)
{
	__GPIOB_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Pin = GPIO_PIN_13 | GPIO_PIN_14;

	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);


	__GPIOC_CLK_ENABLE();

	GPIO_InitStructure.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;	//sm1628 gpio初始化设置

	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void scan_encoder(void)
{
	static  uint8_t  Curr_encoder_b;  //定义一个变量来储存当前B信号
	static  uint8_t  Last_encoder_b;  //定义一个变量来储存上次B脚信号
	static  uint8_t  updata = 0;
	if (PINA && PINB)           //编码器无转动退出
	{
		updata = 0;
		return;
	}
	Last_encoder_b = PINB;       //记录B信号
	while (!PINA)                //等待A由低变高
	{
		Curr_encoder_b = PINB;     //记录等待期间的B信号（指当前B信号）
		updata = 1;
	}
	if (updata)
	{
		updata = 0;
		if ((Last_encoder_b == 0) && (Curr_encoder_b == 1)) //B从0到1为正转
		{
			if (counter == 255)
				return;
			counter++;          //正转计数加
		}
		else if ((Last_encoder_b == 1) && (Curr_encoder_b == 0)) //B从1到0为反转
		{
			if (counter == 0)
				return;
			counter--;         //反转计数减
		}
	}
}
