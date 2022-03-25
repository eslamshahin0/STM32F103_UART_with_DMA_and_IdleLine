#include "main.h"

u8 DataToReceive[50];
u8 DataToTransmit[]="Hello Eslam From DMA transmit \r\n";
int main() {

	RCC_voidInitSysClock();

	/* Config USART */
	GPIO_voidInit(GPIOA);
	GPIO_voidSetPinDirection(RX1, INPUT_FLOATING);
	GPIO_voidSetPinDirection(TX1, OUTPUT_SPEED_2MHZ_AFPP);

	sUART_Config_t UART_Config;
	UART_Config.USART_Num = USART_1;
	UART_Config.UART_Status = USART_Enable;
	UART_Config.BaudRate = BAUD_9600;
	UART_Config.Parity = No_Parity;
	UART_Config.DataDirection = Transmit_Recieve;

	USART_voidInit(&UART_Config);
	USART_voidRXIdleInterruptEnable(USART_1);
	USART_voidDMAEnableTransming(USART_1);
	USART_voidDMAEnableReceiving(USART_1);

	/* Enable DMA clock */
	DMA_voidInit( USE_DMA_1);

	sDMA_Config_t UART_DMA_TransmitStruct;
	UART_DMA_TransmitStruct.DMA_Number = USE_DMA_1;
	UART_DMA_TransmitStruct.ChannelPriority = DMA_VERY_HIGH;
	UART_DMA_TransmitStruct.DMA_Channel = DMA_Channel4;
	UART_DMA_TransmitStruct.DataDirection = ReadFromMemory;
	UART_DMA_TransmitStruct.M2M_Mode = DMA_DISABLE;
	UART_DMA_TransmitStruct.MemoryIncrement = DMA_ENABLE;
	UART_DMA_TransmitStruct.CircularMode = DMA_DISABLE;
	UART_DMA_TransmitStruct.MemorySize = DMA_1byte;
	UART_DMA_TransmitStruct.PeripheralIncrement = DMA_DISABLE;
	UART_DMA_TransmitStruct.PeripheralSize = DMA_1byte;
	UART_DMA_TransmitStruct.TransferCompleteInterrupt = DMA_ENABLE;
	UART_DMA_TransmitStruct.HalfTransferInterrupt = DMA_ENABLE;
	UART_DMA_TransmitStruct.TransferErrorInterrupt = DMA_ENABLE;

	sDMA_Config_t UART_DMA_ReceiveStruct;
	UART_DMA_ReceiveStruct.DMA_Number = USE_DMA_1;
	UART_DMA_ReceiveStruct.ChannelPriority = DMA_VERY_HIGH;
	UART_DMA_ReceiveStruct.DMA_Channel = DMA_Channel5;
	UART_DMA_ReceiveStruct.DataDirection = ReadFromPeripheral;
	UART_DMA_ReceiveStruct.M2M_Mode = DMA_DISABLE;
	UART_DMA_ReceiveStruct.MemoryIncrement = DMA_ENABLE;
	UART_DMA_ReceiveStruct.CircularMode = DMA_ENABLE;
	UART_DMA_ReceiveStruct.MemorySize = DMA_1byte;
	UART_DMA_ReceiveStruct.PeripheralIncrement = DMA_DISABLE;
	UART_DMA_ReceiveStruct.PeripheralSize = DMA_1byte;
	/*Enable this if you know the length of receiving bytes , otherwise we will use idle line interrupt */
	//UART_DMA_ReceiveStruct.TransferCompleteInterrupt = DMA_DISABLE ;
	//UART_DMA_ReceiveStruct.HalfTransferInterrupt = DMA_DISABLE;
	//UART_DMA_ReceiveStruct.TransferErrorInterrupt = DMA_DISABLE;

	/* Init channels */
	DMA_voidInitChannel(&UART_DMA_TransmitStruct);
	DMA_voidInitChannel(&UART_DMA_ReceiveStruct);

	/* Assign call back function to corresponding flag */
	DMA_voidSetCallBack(USE_DMA_1, DMA_Channel4, HalfTransferInterrupt, DMAcpfHalfTransfer);
	DMA_voidSetCallBack(USE_DMA_1, DMA_Channel4, TransferCompleteInterrupt, DMAcpfCompleteTransfer);
	USART_voidSetCallBack(USART_1,UARTcpfIdleLine);
	/* Enable DMA Interrupt for UART Transmitting  */
	NVIC_voidEnableInterrupt(DMA1_Channel4);
	/* Enable DMA Interrupt for UART receiving  */
	//NVIC_voidEnableInterrupt(DMA1_Channel5);
	/* Enable Idle line interrupt  */
	NVIC_voidEnableInterrupt(USART1);

	/* Start Transmitting and receiving*/
	DMA_voidStartTransfer(&UART_DMA_TransmitStruct,(u32)UART1_DR_ADRR, (u32)DataToTransmit,32);
	DMA_voidStartTransfer(&UART_DMA_ReceiveStruct,(u32)UART1_DR_ADRR, (u32)DataToReceive,50);

	while (1) {


	}
}

void DMAcpfCompleteTransfer() {
	/*You will be here when DMA transfer all data */
}
void DMAcpfHalfTransfer() {
	/*You will be here when DMA transfer Half of data length*/
}

void UARTcpfIdleLine() {
 /*You will be here when idle line detected*/
	// TO DO : restart the DMA_voidStartTransfer() to start receiving from beginning
}

