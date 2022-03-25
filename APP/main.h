#ifndef __MAIN_H__
#define __MAIN_H__

#include "STD_TYPES.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"
#include "DMA_interface.h"
#include "USART_interface.h"


#define UART1_DR_ADRR 0x40013804

void DMAcpfCompleteTransfer();
void DMAcpfHalfTransfer();
void UARTcpfIdleLine();

#endif
