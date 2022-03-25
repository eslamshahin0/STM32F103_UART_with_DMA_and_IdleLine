/**
 * ***************************************************************
 *  @file      RCC_interface.h			
 *  @author    Eslam Shahin (eslamshahin552000@gmail.com)                          
 *  @version   v2.0                                            
 *  @date      08/08/2020		                                   
 *  @brief     [Write a brief of this file ]
 *                          	                                 
 *
 *  @note      This program is distributed in the hope  that it  
 * 	           will be useful,but WITHOUT ANY WARRANTY; without     
 *	           even the implied warranty of  MERCHANTABILITY or     
 *	           FITNESS FOR A PARTICULAR PURPOSE.  
 *                                                      
 * ***************************************************************                                                                
 */
 
#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

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
/// For selecting the bus 
typedef enum 
{
    AHB  ,
    APB1 ,
    APB2 
	
}BusName_t;

/// The clock source for the AHB 
typedef enum 
{
    SYSCLK_NOT_DIV 	= 0b0000 ,
    SYSCLK_DIV_2	= 0b1000 ,
    SYSCLK_DIV_4	= 0b1001 ,
    SYSCLK_DIV_8 	= 0b1010 ,
    SYSCLK_DIV_16 	= 0b1011 ,
    SYSCLK_DIV_64 	= 0b1100 ,
    SYSCLK_DIV_128 	= 0b1101 ,
    SYSCLK_DIV_256 	= 0b1110 ,
    SYSCLK_DIV_512	= 0b1111 
	
}AHB_ClockSpeed_t;

/// The clock source for APB 
typedef enum 
{

	AHP_CLOCK_NOT_DIV	=  0b000 ,	
    AHP_CLOCK_DIV_2		=  0b100 ,
    AHP_CLOCK_DIV_4		=  0b101 ,	
    AHP_CLOCK_DIV_8		=  0b110 ,
    AHP_CLOCK_DIV_16    =  0b111 
	
}APB_ClockSpeed_t;

/// Peripheral IDs on different buses
typedef enum 
{
    AHB_DMA1      = 0  ,
    AHB_DMA2      = 1  ,
    AHB_SRAM      = 2  ,
    AHB_FLITF     = 4  ,
    AHB_CRCE      = 6  ,
    AHB_FSMC      = 8  ,
    AHB_SDIO      = 10 ,

    APB1_TIM2EN	  = 0  ,
    APB1_TIM3EN	  = 1  ,
    APB1_TIM4EN	  = 2  ,
    APB1_TIM5EN	  = 3  ,
    APB1_TIM6EN	  = 4  ,
    APB1_TIM7EN	  = 5  ,
    APB1_TIM12EN  = 6  ,	
    APB1_TIM13EN  = 7  ,
    APB1_TIM14EN  = 8  ,
    APB1_WWDGEN	  = 11 ,
    APB1_SPI2EN	  = 14 ,
    APB1_SPI3EN	  = 15 ,
    APB1_USART2EN = 17 ,
    APB1_USART3EN = 18 ,
    APB1_UART4EN  = 19 ,
    APB1_UART5EN  = 20 ,
    APB1_I2C1EN	  = 21 ,
    APB1_I2C2EN	  = 22 ,
    APB1_USBEN 	  = 23 ,
    APB1_CANEN	  = 25 ,
    APB1_BKPEN	  = 27 ,
    APB1_PWREN	  = 28 ,
    APB1_DACEN	  = 29 ,
	
    APB2_AFIOEN	  = 0  ,
    APB2_IOPAEN   = 2  ,
    APB2_IOPBEN   = 3  ,
    APB2_IOPCEN   = 4  ,
    APB2_IOPDEN   = 5  ,
    APB2_IOPEEN   = 6  ,
    APB2_IOPFEN   = 7  ,
    APB2_IOPGEN   = 8  ,
    APB2_ADC1EN   = 9  ,
    APB2_ADC2EN   = 10 ,
    APB2_TIM1EN   = 11 ,
    APB2_SPI1EN   = 12 ,
    APB2_TIM8EN   = 13 , 
    APB2_USART1EN = 14 , 
    APB2_ADC3EN   = 15 ,
    APB2_TIM9EN   = 19 ,
    APB2_TIM10EN  = 20 ,
    APB2_TIM11EN  = 21 
	 
}PeripheralID_t;

/// Modify the value of thr HSI RC 8MHz 
typedef enum {
	
	HSI_INCRISE,
	HSI_DECRISE
	
}TrimType_t;

/// Microcontroller clock output
typedef enum {
	
	NO_CLOCK ,
	SYSCLK   ,
	HSI	     ,
	HSE      ,
	PLL_DIV_2
	
}OutputClockSource_t;

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

void RCC_voidInitSysClock(void);

void RCC_voidEnableClock(BusName_t Copy_u8BusId, PeripheralID_t Copy_u8PerId);
void RCC_voidDisableClock(BusName_t Copy_u8BusId, PeripheralID_t Copy_u8PerId);

void RCC_voidSetAHBusClock(AHB_ClockSpeed_t copy_busSpeedDivFactor);
void RCC_voidSetAPBusClock(BusName_t copy_u8busid, APB_ClockSpeed_t copy_busSpeedDivFactor);

void RCC_voidEnableClockSecurity(void);
void RCC_voidDisableClockSecurity(void);

void RCC_voidHSITirm(TrimType_t TrimValue);

void RCC_voidClockOutput(OutputClockSource_t ClockSource);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*File_H_*/

/*** End of File **************************************************************/
