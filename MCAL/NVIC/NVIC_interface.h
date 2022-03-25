/**
 * ***************************************************************
 *  @file      NVIC_interface.h			
 *  @author    Eslam Shahin (eslamshahin552000@gmail.com)                          
 *  @version   v2.0                                            
 *  @date      4/09/2020		                                   
 *  @brief     NVIC APIs
 *                          	                                 
 *
 *  @note      This program is distributed in the hope  that it  
 * 	           will be useful,but WITHOUT ANY WARRANTY; without     
 *	           even the implied warranty of  MERCHANTABILITY or     
 *	           FITNESS FOR A PARTICULAR PURPOSE.  
 *                                                      
 * ***************************************************************                                                                
 */
 
#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/
/** To Config how many groups
 and sub groups in your system */
 /*
PRIGROUP[2:0]   Binary point(1) Group priority bits		Subpriority	  Group priorities    Sub priorities
	0b011			0bxxxx 		 		[7:4]			 None 			 16   				 None
	0b100			0bxxx.y		 		[7:5]			 [4]             8	  				 2
	0b101			0bxx.yy		 		[7:6]			 [5:4]			 4    				 4
	0b110			0bx.yyy		 		[7]  			 [6:4]			 2    				 8
	0b111			0b.yyyy		 		None 			 [7:4]			 None 				 16
	*/
typedef enum{
	GROUP4_SUB0_BITS = 0X05FA0300,	/* 4 bits for group */
	GROUP3_SUB1_BITS = 0X05FA0400,	/* 3 bits for group , 1 for sub group */
	GROUP2_SUB2_BITS = 0X05FA0500,	/* 2 bits for group , 2 for sub group */
	GROUP1_SUB3_BITS = 0X05FA0600,	/* 1 bits for group , 3 for sub group */
	GROUP0_SUB4_BITS = 0X05FA0700	/* 0 bits for group , 4 for sub group (Close the Nesting) */
}eInterrupt_Group_t;

typedef enum {
	WWDG			,
	PVD	            ,
	TAMPER	        ,
	RTC	            ,
	FLASH	        ,
	RCC		        ,
	EXTI0	        ,
	EXTI1 	        ,
	EXTI2	        ,
	EXTI3 	        ,
	EXTI4	        ,
	DMA1_Channel1	,
	DMA1_Channel2	,
	DMA1_Channel3 	,
	DMA1_Channel4 	,
	DMA1_Channel5 	,
	DMA1_Channel6	,
	DMA1_Channel7 	,
	ADC1_2			,
	USB_HP_CAN_TX   ,
	USB_LP_CAN_RX0  ,
	CAN_RX1 		,
	CAN_SCE 		,
	EXTI9_5 		,
	TIM1_BRK 	 	,
	TIM1_UP  		,
	TIM1_TRG_COM	,
	TIM1_CC 		,
	TIM2  			,
	TIM3  			,
	TIM4 	 		,
	I2C1_EV 		,
	I2C1_ER 		,
	I2C2_EV 		,
	I2C2_ER 		,
	SPI1 			,
	SPI2 			,
	USART1 			,
	USART2 			,
	USART3 			,
	EXTI15_10 		,
	RTCAlarm 		,
	USBWakeup       ,
	TIM8_BRK 		,
	TIM8_UP 	 	,
	TIM8_TRG_COM 	,
	TIM8_CC 		,
	ADC3 			,
	FSMC 			,
	SDIO 			,
	TIM5 			,
	SPI3 			,
	UART4			,
	UART5			,
	TIM6 			,
	TIM7 			,
	DMA2_Channel1 	,
	DMA2_Channel2 	,
	DMA2_Channel3 	,
	DMA2_Channel4_5 
}eInterrupt_ID_IVT_t;
/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

void NVIC_voidSetGlobalGroupAndSub(eInterrupt_Group_t GroupAndSub);

void NVIC_voidEnableInterrupt (eInterrupt_ID_IVT_t IntNumber);
void NVIC_voidDisableInterrupt(eInterrupt_ID_IVT_t IntNumber);

void NVIC_voidSetPendingFlag  (eInterrupt_ID_IVT_t IntNumber);
void NVIC_voidClearPendingFlag(eInterrupt_ID_IVT_t IntNumber);
u8   NVIC_u8GetActiveFlag     (eInterrupt_ID_IVT_t IntNumber);
/* This function takes the Secound Argument in 4 bits in binary 
accourding to option you used in NVIC_voidSetGlobalGroupAndSub() 
A programmable priority level of 0-15 for each interrupt. A higher level corresponds to a
lower priority, so level 0 is the highest interrupt priority */
void NVIC_voidSetPriorty(eInterrupt_ID_IVT_t IntNumber,u8 copy_u8GroupAndSubPriorty );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*File_H_*/

/*** End of File **************************************************************/
