#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"

#define UART2EN     (1U << 17)
#define GPIOAEN     (1U << 0)

#define CR1_TE      (1U << 3)
#define CR1_UE      (1U << 13)

#define SR_TXE      (1U << 7)

#define SYS_FREQ    16000000UL
#define APB1_CLK    SYS_FREQ

#define UART_BAUDRATE   115200

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static void UART2_Tx_init(void);
void UART2_Transmit(int ch);

int main(void)
{
	UART2_Tx_init();

	while(1)
	{
		printf("hello from baremetal firmware...\n\r");
		for(int i = 0; i <= 1000000; i++){}
	}
}

int __io_putchar(int ch)
{
	UART2_Transmit(ch);
	return ch;
}

void UART2_Transmit(int ch)
{
	while(!(USART2->SR & SR_TXE)){}
	USART2->DR = (ch & 0xFF);
}

static void UART2_Tx_init(void)
{
	RCC->AHB1ENR |= GPIOAEN;    //Enabling AHB1 clock for PORT A, because UART 2 uses PA2 - TX and PA3 - RX

	/* setting PA2 - TX as alternate function mode by using set 1 bit 4 and 5 as configuration 1:0*/
	GPIOA->MODER &= ~(1U << 4);
	GPIOA->MODER |= (1U << 5);

	/* Setting PA2 alternate function type :
	 * PA2 is a AF7 in alternate function mapping register.
	 * PA2 comes under alternate function low register because first 8 pins on any port it comes under AFRL, next 8 pins comes under the AFRH register
	 * for enabling AF7 we need to set bit formation as 0111 to the particular alternate function pin register.
	 * Alternate function register, each pin have 4 bits.
	 */
	GPIOA->AFR[0] |= (1U << 8);   //1
	GPIOA->AFR[0] |= (1U << 9);   //1
	GPIOA->AFR[0] |= (1U << 10);  //1
	GPIOA->AFR[0] &= ~(1U << 11);  //0

	RCC->APB1ENR |= UART2EN;    //Enabling APB1 clock for UART2

	/*Configure baud rate*/
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	/*configure the transfer direction like rx or tx*/
	USART2->CR1 = CR1_TE;

	/*enabling the uart module*/
	USART2->CR1 |= CR1_UE;
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_bd(PeriphClk,BaudRate);
}


static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}
