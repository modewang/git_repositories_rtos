#include "..\APP\includes.h"
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

#ifdef __GNUC__ 
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

void uart_send_byte(unsigned char d)
{
	/* 发送一个字节数据到USART1 */
	USART_SendData(USART1, (uint8_t)d);
		
	/* 等待发送完毕 */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}



void USART1_InitConfig(uint32 BaudRate)
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
  /* Enable USART1 Receive and Transmit interrupts */

  /* Enable the USART1 */
  USART_Cmd(USART1, ENABLE);//仿真看到执行这里，TC标志居然被设置为1了，不知道实际在flash中运行是否是这样
}
