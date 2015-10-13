#ifndef __1628_H
#define __1628_H

#include "stm32f4xx_hal.h"

/* SM1628 PORT Define */
#define SM1628_DIO_H() 		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET)
#define SM1628_DIO_L() 		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET)

#define SM1628_CLK_H() 		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET)
#define SM1628_CLK_L() 		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET)

#define SM1628_STB_H()  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET)
#define SM1628_STB_L()  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET)

/* SM1628 Function Define */
void SM1628_Init(void);
void SM1628_WriteOneByte(uint8_t WriteByte);
void SM1628_SendCommand(uint8_t SendCommand);
void SM1628_SendData(uint8_t Addr, uint8_t Data);
void SM1628_Display(uint8_t Data1, uint8_t Data2, uint8_t Data3, uint8_t Data4, uint8_t Brightness);
void SM1628_PutDisplayValue(uint16_t DispVal, uint8_t Brightness);

#endif
