/*
 * Oled12864_ssd1306.h
 *
 *  Created on: 2017年5月20日
 *      Author: jinzhifeng
 *      https://github.com/jinzhifeng
 */

#ifndef OLED12864_SSD1306_H_
#define OLED12864_SSD1306_H_

#include "iic.h"


#define Max_Column		128
#define Max_Row			64
#define	Brightness		0xFF


//Oled控制用函数
void Oled_WriteCommand(uint8_t OledCommand);
void Oled_WriteData(uint8_t OledData);
void Oled_Display_On(void);
void Oled_Display_Off(void);
void Oled_Init(void);
void Oled_Clear(void);
void Oled_DrawPoint(uint8_t x, uint8_t y, uint8_t t);
void Oled_Fill(uint8_t x1, uint8_t Y1, uint8_t x2, uint8_t y2, uint8_t dot);
void Oled_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size);
void Oled_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size);
void Oled_ShowString(uint8_t x, uint8_t y, uint8_t *p, uint8_t Char_Size);
void Oled_Set_Pos(uint8_t x, uint8_t y);
void Oled_ShowCHinese(uint8_t x, uint8_t y, uint8_t no);
void Oled_DrawBMP(uint8_t x0, uint8_t y0, uint8_t x1,
uint8_t Y1, uint8_t BMP[]);
void fill_picture(uint8_t fill_Data);


#endif /* Oled12864_SSD1306_H_ */
