/*
 * uart2.h
 *
 *  Created on: Apr 23, 2025
 *      Author: kjeyabalan
 */

#ifndef UART2_H_
#define UART2_H_

#include <stdint.h>
#include "stm32f4xx.h"

void UART2_Init(void);
char uart2_receive(void);
void UART2_Transmit(int ch);



#endif /* UART2_H_ */
