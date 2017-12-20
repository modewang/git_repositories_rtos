#include "usart.h"

#include <stdio.h>

//#include "..\APP\includes.h"
//#include "include.h"
/**************************************************************************************
* 变量原型:
* 变量说明:    
**************************************************************************************/
/**************************************************************************************
* 函数原型:
* 函数功能:
* 输入参数:
* 输出参数:
* 函数说明:
**************************************************************************************/
// 他这套代码既想在windwos下可用，又想在linux下可用，所以就用宏定义
// 来区分环境，重定位到不同的名字。
#ifdef __GNUC__ 			// 这个宏如果定义了就表示当前是gcc环境
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf 
     set to 'Yes') calls __io_putchar() */ 
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch) 
#else 
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f) 
#endif /* __GNUC__ */ 

/*******************************************************************************
* Function Name  : PUTCHAR_PROTOTYPE
* Description    : Retargets the C library printf function to the USART.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
PUTCHAR_PROTOTYPE
{
   while (!(USART1->SR & USART_FLAG_TXE));
   USART1->DR = (ch & 0x1FF);
   
   return ch;
}


void USART1_InitConfig(uint32_t BaudRate)
{
		USART_InitTypeDef USART_InitStructure;
  
		USART_InitStructure.USART_BaudRate = BaudRate;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

		/* Configure USART1 */
		USART_Init(USART1, &USART_InitStructure);
	
		USART_Cmd(USART1, ENABLE);//仿真看到执行这里，TC标志居然被设置为1了，不知道实际在flash中运行是否是这样
}

