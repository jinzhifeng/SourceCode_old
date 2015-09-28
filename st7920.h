#ifndef __ST7920_H
#define __ST7920_H

#include "stm32f4xx_hal.h"

/* ST7920 PORT Define */
#define Lcd_RS_H() 		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET)
#define Lcd_RS_L() 		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET)

#define Lcd_RW_H() 		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET)
#define Lcd_RW_L() 		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET)

#define Lcd_EN_H() 		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET)
#define Lcd_EN_L() 		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET)

#define Lcd_PSB_H() 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET)
#define Lcd_PSB_L() 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET)

#define Lcd_nRST_H() 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET)
#define Lcd_nRST_L() 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET)

/* ST7920 Function Define */
void Lcd_Delayms(uint32_t n);
void Lcd_WriteCommand(uint8_t WriteCommand);
void Lcd_WriteData(uint8_t WriteData);
uint8_t Lcd_BusyFlag(void);
void Lcd_Init(void);
void Lcd_DisplayPos(uint8_t Xpos,	uint8_t Ypos);
void Lcd_ClrGDRAM(void);
void Lcd_DisplayBMP(uint8_t *bmp);
void Lcd_DisplayString(uint8_t x, uint8_t y, uint8_t ClrString,	uint16_t displaytime, char *String);


#endif
