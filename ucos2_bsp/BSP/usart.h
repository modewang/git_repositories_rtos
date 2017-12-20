//#if !defined  (_COM_H)
//#define _COM_H
#ifndef __USART_H__
#define __USART_H__

#include "stm32f10x.h"
#include "../uCOS-II/Ports/os_cpu.h"



void USART1_InitConfig(uint32_t BaudRate);

#endif

