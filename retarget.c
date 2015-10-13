/*----------------------------------------------------------------------------
* Name: Retarget.c
* Purpose: 'Retarget' layer for target-dependent low level functions
* Note(s):
*----------------------------------------------------------------------------
* This file is part of the uVision/ARM development tools.
* This software may only be used under the terms of a valid, current,
* end user licence from KEIL for a compatible version of KEIL software
* development tools. Nothing else gives you the right to use this software.
*
* This software is supplied "AS IS" without warranties of any kind.
*
* Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
*----------------------------------------------------------------------------*/

#include <stdio.h>
#include <rt_misc.h>
#include "stm32f4xx_hal.h"
#include "usart.h"

#pragma import(__use_no_semihosting_swi)

#define   huartX    huart2	//依据打印串口选择

extern int sendchar (int c);
extern int getkey (void);


struct __FILE { int handle; };
FILE __stdout;
FILE __stdin;


int fputc(int c, FILE *f) {
	uint8_t Character;
	Character=c;
  return (HAL_UART_Transmit(&huartX, &Character, 1, 1000));
}

int fgetc(FILE *f) {
	uint8_t c;
	while(!__HAL_UART_GET_FLAG(&huartX,UART_FLAG_RXNE));
	HAL_UART_Receive(&huartX, &c, 1, 1000);
  return (c);
}


int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}


void _ttywrch(int c) {
  uint8_t Character;
	Character=c;
  HAL_UART_Transmit(&huartX, &Character, 1, 1000);
}


void _sys_exit(int return_code) {
label: goto label; /* endless loop */
}
