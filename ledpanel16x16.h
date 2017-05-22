/*
 * ledpanel16x16.h
 *
 *  Created on: 2017Äê5ÔÂ6ÈÕ
 *      Author: jinzhifeng
 */

#ifndef LEDPANEL16X16_H_
#define LEDPANEL16X16_H_
#include "stm32f7xx_hal.h"
#include "font.h"

#define LedPanel_A_Set()		HAL_GPIO_WritePin(LedPanel_A_GPIO_Port, LedPanel_A_Pin, GPIO_PIN_SET);
#define LedPanel_A_Clr()		HAL_GPIO_WritePin(LedPanel_A_GPIO_Port, LedPanel_A_Pin, GPIO_PIN_RESET);
#define LedPanel_B_Set()		HAL_GPIO_WritePin(LedPanel_B_GPIO_Port, LedPanel_B_Pin, GPIO_PIN_SET);
#define LedPanel_B_Clr()		HAL_GPIO_WritePin(LedPanel_B_GPIO_Port, LedPanel_B_Pin, GPIO_PIN_RESET);
#define LedPanel_C_Set()		HAL_GPIO_WritePin(LedPanel_C_GPIO_Port, LedPanel_C_Pin, GPIO_PIN_SET);
#define LedPanel_C_Clr()		HAL_GPIO_WritePin(LedPanel_C_GPIO_Port, LedPanel_C_Pin, GPIO_PIN_RESET);
#define LedPanel_D_Set()		HAL_GPIO_WritePin(LedPanel_D_GPIO_Port, LedPanel_D_Pin, GPIO_PIN_SET);
#define LedPanel_D_Clr()		HAL_GPIO_WritePin(LedPanel_D_GPIO_Port, LedPanel_D_Pin, GPIO_PIN_RESET);
#define LedPanel_Gin_Set()		HAL_GPIO_WritePin(LedPanel_GIN_GPIO_Port, LedPanel_GIN_Pin, GPIO_PIN_SET);
#define LedPanel_Gin_Clr()		HAL_GPIO_WritePin(LedPanel_GIN_GPIO_Port, LedPanel_GIN_Pin, GPIO_PIN_RESET);
#define LedPanel_STCP_Set()		HAL_GPIO_WritePin(LedPanel_STCP_GPIO_Port, LedPanel_STCP_Pin, GPIO_PIN_SET);
#define LedPanel_STCP_Clr()		HAL_GPIO_WritePin(LedPanel_STCP_GPIO_Port, LedPanel_STCP_Pin, GPIO_PIN_RESET);
#define LedPanel_SHCP_Set()		HAL_GPIO_WritePin(LedPanel_SHCP_GPIO_Port, LedPanel_SHCP_Pin, GPIO_PIN_SET);
#define LedPanel_SHCP_Clr()		HAL_GPIO_WritePin(LedPanel_SHCP_GPIO_Port, LedPanel_SHCP_Pin, GPIO_PIN_RESET);
#define LedPanel_Rin_Set()		HAL_GPIO_WritePin(LedPanel_RIN_GPIO_Port, LedPanel_RIN_Pin, GPIO_PIN_SET);
#define LedPanel_Rin_Clr()		HAL_GPIO_WritePin(LedPanel_RIN_GPIO_Port, LedPanel_RIN_Pin, GPIO_PIN_RESET);


void WriteGrnColDatTo595(uint8_t GrnColDat);
void WriteRedColDatTo595(uint8_t RedColDat);
void WriteRGColDatTo595(uint8_t RedColDat, uint8_t GrnColDat);
void SelectRowDisp(uint8_t nRow);
void distest(void);




#endif /* LEDPANEL16X16_H_ */
