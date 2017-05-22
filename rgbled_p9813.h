/*
 * rgbled_P9813.h
 *
 *  Created on: 2017年5月18日
 *      Author: jinzhifeng
 *      https://github.com/jinzhifeng
 */

#ifndef RGBLED_P9813_H_
#define RGBLED_P9813_H_

#include "stm32f7xx_hal.h"

#define RGBLed_P9813_Clk_Set()		HAL_GPIO_WritePin(RGBLed_clk_GPIO_Port, RGBLed_clk_Pin, GPIO_PIN_SET)	   //RGBled_P9813-Clk端口分配
#define RGBLed_P9813_Clk_Clr()		HAL_GPIO_WritePin(RGBLed_clk_GPIO_Port, RGBLed_clk_Pin, GPIO_PIN_RESET)	   //RGBled_P9813-Clk端口分配
#define RGBLed_P9813_Data_Set()		HAL_GPIO_WritePin(RGBLed_data_GPIO_Port, RGBLed_data_Pin, GPIO_PIN_SET)	   //RGBled_P9813-Data端口分配
#define RGBLed_P9813_Data_Clr()		HAL_GPIO_WritePin(RGBLed_data_GPIO_Port, RGBLed_data_Pin, GPIO_PIN_RESET)	   //RGBled_P9813-Data端口分配

#define RGBLed_PowerON()			HAL_GPIO_WritePin(RGBLed_pwren_GPIO_Port, RGBLed_pwren_Pin, GPIO_PIN_SET)	   //RGBled_P9813-PowerEnable端口分配
#define RGBLed_PowerOFF()			HAL_GPIO_WritePin(RGBLed_pwren_GPIO_Port, RGBLed_pwren_Pin, GPIO_PIN_RESET)	   //RGBled_P9813-PowerEnable端口分配

#define RGBLed_P9813_Delay()	//	HAL_Delay(1);




void Send32BitZero(void);
uint8_t CovertToOnesComplement(uint8_t Data);
void RGBLed_P9813_SendRGBData(uint8_t rDATA, uint8_t gDATA, uint8_t bDATA);
void RGBLed_P9813_Init(void);
void RGBLed_P9813_SetRGBValue(uint8_t rValue, uint8_t gValue, uint8_t bValue);

#endif /* RGBLED_P9813_H_ */
