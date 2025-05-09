#include "stm32f4xx.h"


#define GPIOAEN       (1U << 0)
#define GPIOCEN       (1U << 2)

#define PIN13         (1U << 13)
#define PIN5          (1U << 5)

#define BTN_PIN        PIN13
#define LED_PIN        PIN5

int main(void)
{
	RCC->AHB1ENR |= (GPIOAEN) | (GPIOCEN);

	GPIOA->MODER |= (1U << 10);     /* Output configuration*/
	GPIOA->MODER &= ~(1U << 11);

	GPIOC->MODER &= ~(1U << 26);    /* Input configuration*/
	GPIOC->MODER &= ~(1U << 27);
	while(1)
	{
		if(GPIOC->IDR & (BTN_PIN))
		{
			GPIOA->BSRR |= (1U << 21);
		}
		else
		{
			GPIOA->BSRR |= (1U << 5);
		}
	}
}
