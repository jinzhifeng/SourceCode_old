/*  github.com/jinzhifeng  */
/*  QQ356290462            */
#ifndef __PCD8544_H
#define __PCD8544_H

#include "stm32f4xx_hal.h"


#define Lcd_Pcd8544_SDIN_SET()						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET)
#define Lcd_Pcd8544_SDIN_CLR() 						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET)

#define Lcd_Pcd8544_SCLK_SET()						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET)
#define Lcd_Pcd8544_SCLK_CLR() 						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET)

#define Lcd_Pcd8544_DC_SET()							HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET)
#define Lcd_Pcd8544_DC_CLR() 							HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET)

#define Lcd_Pcd8544_SCE_SET()							HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET)
#define Lcd_Pcd8544_SCE_CLR() 						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET)

#define Lcd_Pcd8544_RST_SET()							HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET)
#define Lcd_Pcd8544_RST_CLR() 						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET)

#define Lcd_Pcd8544_BACKLIGHT_SET()				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET)
#define Lcd_Pcd8544_BACKLIGHT_CLR() 			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET)

void Lcd_Pcd8544_WriteByte(uint8_t WriteByte, uint8_t CommandOrDataSelect);
void Lcd_Pcd8544_Init(void);
void Lcd_Pcd8544_Delayms(uint32_t n);
void Lcd_Pcd8544_ClrScreen(void);
void Lcd_Pcd8544_SetPos(uint16_t Xpos, uint16_t Ypos);
void Lcd_Pcd8544_PutEnglishChar(uint8_t EnglishChar);
void Lcd_Pcd8544_PutEnglishString(uint16_t X, uint16_t Y, uint8_t *EnglishString);
#endif


/*  github.com/jinzhifeng  */
/*  QQ356290462            */
