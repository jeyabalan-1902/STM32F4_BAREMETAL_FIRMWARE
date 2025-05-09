/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Jeyabalan K
 * @brief          : Baremetal registers for LED Toggling
 ******************************************************************************
 */


/**
 * LED Pin :  PA5
 */

#include <stdint.h>

#define PERIPHERAL_BASE     (0x40000000UL)
#define AHB1_OFFSET         (0x00020000UL)
#define AHB1_BASE           (PERIPHERAL_BASE + AHB1_OFFSET)

#define GPIOA_OFFSET        (0x0000UL)
#define GPIOA_BASE          (AHB1_BASE + GPIOA_OFFSET)

#define RCC_OFFSET          (0x3800UL)
#define RCC_BASE            (AHB1_BASE + RCC_OFFSET)


#define GPIOAEN             (1U << 0)
#define PIN5                (1U << 5)
#define LED_PIN             PIN5

#define __IO volatile

typedef struct
{
	__IO uint32_t MODER;        /*!< GPIO port mode register,                            Address offset: 0x00      */
	__IO uint32_t OTYPER;       /*!< GPIO port output type register,                     Address offset: 0x04      */
	__IO uint32_t OSPEEDR;      /*!< GPIO port output speed register,                    Address offset: 0x08      */
	__IO uint32_t PUPDR;        /*!< GPIO port pull-up/pull-down register,               Address offset: 0x0C      */
	__IO uint32_t IDR;          /*!< GPIO port input data register,                      Address offset: 0x10      */
	__IO uint32_t ODR;          /*!< GPIO port output data register,                     Address offset: 0x14      */
	__IO uint32_t BSRR;         /*!< GPIO port bit set/ reset register,                  Address offset: 0x18      */
	__IO uint32_t LCKR;         /*!< GPIO port configuration lock register,              Address offset: 0x1C      */
	__IO uint32_t AFR[2];       /*!< GPIO port alternate function register,              Address offset: 0x20-0x24 */
}GPIO_Typedef;

typedef struct
{
	__IO uint32_t CR;
	__IO uint32_t PLLCFGR;
	__IO uint32_t CFGR;
	__IO uint32_t CIR;
	__IO uint32_t AHB1RSTR;
	__IO uint32_t AHB2RSTR;
	__IO uint32_t AHB3RSTR;
	uint32_t RESERVED0;
	__IO uint32_t APB1RSTR;
	__IO uint32_t APB2RSTR;
	uint32_t RESERVED1[2];
	__IO uint32_t AHB1ENR;
	__IO uint32_t AHB2ENR;
	__IO uint32_t AHB3ENR;
	uint32_t RESERVED2;
	__IO uint32_t APB1ENR;
	__IO uint32_t APB2ENR;
	uint32_t RESERVED3[2];
	__IO uint32_t AHB1LPENR;
	__IO uint32_t AHB2LPENR;
	__IO uint32_t AHB3LPENR;
	uint32_t RESERVED4;
	__IO uint32_t APB1LPENR;
	__IO uint32_t APB2LPENR;
	uint32_t RESERVED5[2];
	__IO uint32_t BDCR;
	__IO uint32_t CSR;
	uint32_t RESERVED6[2];
	__IO uint32_t SSCGR;
	__IO uint32_t PLLI2SCFGR;
	uint32_t RESERVED7[1];
	__IO uint32_t PLLSAICFGR;
	__IO uint32_t DCKCFGR;
	__IO uint32_t CKGATENR;
	__IO uint32_t DCKCFGR2;
}RCC_Typedef;

#define RCC   ((RCC_Typedef*) RCC_BASE)
#define GPIOA ((GPIO_Typedef*) GPIOA_BASE)

void delay(uint32_t t)
{
	while(t--);
}

int main(void)
{
	RCC->AHB1ENR |= GPIOAEN;                // Enable clock for GPIOA
	GPIOA->MODER |= (1U << 10);             // Set PA5 as output
	GPIOA->MODER &= ~(1U << 11);

	while(1)
	{
		GPIOA->ODR |= LED_PIN;              // Set PA5 high
		for(int i = 0; i <= 1000000; i++){}
		GPIOA->ODR &= ~(LED_PIN);
		for(int i = 0; i <= 1000000; i++){}
	}
}
