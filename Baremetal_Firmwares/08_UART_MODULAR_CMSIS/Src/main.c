#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart2.h"

int main(void)
{
	UART2_Tx_init();

	while(1)
	{
		printf("hello from bare metal firmware...\n\r");
		for(int i = 0; i <= 1000000; i++){}
	}
}



