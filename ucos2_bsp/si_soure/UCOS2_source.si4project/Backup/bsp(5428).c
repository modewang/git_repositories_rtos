//#include "..\App\includes.h"
#include "bsp.h"
#include "usart.h"

/*
*********************************************************************************************************
QQ: 958664258
21IC用户名：banhushui
交流平台：http://blog.21ic.com/user1/5817/index.html
淘宝店铺：http://shop58559908.taobao.com
旺旺：半壶水电子
编译器版本：MDK3.5
硬件平台：BHS-STM32--->
http://item.taobao.com/auction/item_detail-db2-a29ff4d34829cbddeffe864fc1741d21.jhtml
*********************************************************************************************************
*/

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void RCC_Configuration(void)
{
		/* Enable GPIO_LED clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB 
	| RCC_APB2Periph_AFIO | RCC_APB2Periph_USART1, ENABLE);
}



/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void GPIO_Configuration(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;

		//8个LED接在PB8-PB15
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
  
		//usart的2个io（TX和RX）的初始化
		/* Configure USART1 Rx (PA.10) as input floating */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		/* Configure USART1 Tx (PA.09) as alternate function push-pull */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static void delay_led(void)
{
	uint32_t a, b;
	
	for (a=0; a<1000; a++)
		for (b=0; b<5000; b++);
}

void BSP_Led_Test(void)
{
	uint32_t cnt = 0;
	
	for (cnt=0; cnt<3; cnt++)
	{
		GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_RESET);		// 熄灭LED1
		delay_led();
		GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_SET);			// 点亮LED1
		delay_led();
	}
	
}


/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void NVIC_Configuration(void)
{
//  NVIC_InitTypeDef NVIC_InitStructure;

//#ifdef  VECT_TAB_RAM
#if defined (VECT_TAB_RAM)
		/* Set the Vector Table base location at 0x20000000 */ 
		NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#elif defined(VECT_TAB_FLASH_IAP)
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x2000);
#else  /* VECT_TAB_FLASH  */
		/* Set the Vector Table base location at 0x08000000 */ 
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif 

		/* Configure the NVIC Preemption Priority Bits */  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
}

void BSP_Init(void)
{
		/* System Clocks Configuration */
		RCC_Configuration();   

		GPIO_Configuration();
		
		/* NVIC configuration */
		NVIC_Configuration();
		
		USART1_InitConfig(9600);
}

CPU_INT32U  BSP_CPU_ClkFreq (void)
{
    RCC_ClocksTypeDef  rcc_clocks;

    RCC_GetClocksFreq(&rcc_clocks);

    return ((CPU_INT32U)rcc_clocks.HCLK_Frequency);
}

// printf打印出各种时钟信息
void BSP_Printf_Clock(void)
{
	RCC_ClocksTypeDef  rcc_clocks;

	RCC_GetClocksFreq(&rcc_clocks);

	printf("SYSCLK_Frequency = %u\r\n", rcc_clocks.SYSCLK_Frequency);
	printf("HCLK_Frequency = %u\r\n", rcc_clocks.HCLK_Frequency);
	printf("PCLK1_Frequency = %u\r\n", rcc_clocks.PCLK1_Frequency);
	printf("PCLK2_Frequency = %u\r\n", rcc_clocks.PCLK2_Frequency);
	printf("ADCCLK_Frequency = %u\r\n", rcc_clocks.ADCCLK_Frequency);
}


INT32U  OS_CPU_SysTickClkFreq (void)
{
	INT32U  freq;


	freq = BSP_CPU_ClkFreq();
	return (freq);
}


#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/

