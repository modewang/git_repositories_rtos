#include <stdio.h>

#include "stm32f10x.h"
#include "bsp.h"

int main(void)
{
	BSP_Init();
	
	
	printf("usart test.\r\n");
	BSP_Printf_Clock();
	BSP_Led_Test();
	while (1);
	
	return 0;
}
