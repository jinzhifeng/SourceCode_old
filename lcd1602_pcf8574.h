/*
 * lcd1602_pcf8574.h
 *
 *  Created on: 2017Äê5ÔÂ16ÈÕ
 *      Author: jinzhifeng
 *      https://github.com/jinzhifeng
 */

#ifndef LCD1602_PCF8574_H_
#define LCD1602_PCF8574_H_

#include "stm32f7xx_hal.h"
#include "iic.h"

#define Lcd1602_Pcf8574_Delay()     HAL_Delay(1);

void Lcd1602_Pcf8574_Init(void);
void Lcd1602_Pcf8574_WriteByte(uint8_t WriteByte);
void Lcd1602_Pcf8574_WriteCommand(uint8_t Command);
void Lcd1602_Pcf8574_WriteData(uint8_t Dat);
void Lcd1602_Pcf8574_Disp(void);

#endif /* LCD1602_PCF8574_H_ */
