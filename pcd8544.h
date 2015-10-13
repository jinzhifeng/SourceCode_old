#ifndef __PCD8544_H
#define __PCD8544_H

#include "stm32f4xx_hal.h"


#define Lcd_Pcd8544_SDIN_H()						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET)
#define Lcd_Pcd8544_SDIN_L() 						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET)

#define Lcd_Pcd8544_SCLK_H()						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET)
#define Lcd_Pcd8544_SCLK_L() 						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET)

#define Lcd_Pcd8544_DC_H()							HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET)
#define Lcd_Pcd8544_DC_L() 							HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET)

#define Lcd_Pcd8544_SCE_H()							HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET)
#define Lcd_Pcd8544_SCE_L() 						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET)

#define Lcd_Pcd8544_RST_H()							HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET)
#define Lcd_Pcd8544_RST_L() 						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET)

#define Lcd_Pcd8544_BACKLIGHT_H()				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET)
#define Lcd_Pcd8544_BACKLIGHT_L() 			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET)

void Lcd_Pcd8544_WriteByte(uint8_t WriteByte, uint8_t CommandOrDataSelect);
void Lcd_Pcd8544_Init(void);
void Lcd_Pcd8544_Delayms(uint32_t n);
void Lcd_Pcd8544_ClrScreen(void);
void Lcd_Pcd8544_SetPos(uint16_t Xpos, uint16_t Ypos);
void Lcd_Pcd8544_PutEnglishChar(uint8_t EnglishChar);
void Lcd_Pcd8544_PutEnglishString(uint16_t X, uint16_t Y, uint8_t *EnglishString);
#endif
