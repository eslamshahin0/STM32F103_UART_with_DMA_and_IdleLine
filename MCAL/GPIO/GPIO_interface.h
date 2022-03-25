/**
 * ***************************************************************
 *  @file      GPIO_interface.h			
 *  @author    Eslam Shahin (eslamshahin552000@gmail.com)                          
 *  @version   v2.0                                            
 *  @date      03/09/2020		                                   
 *  @brief     GPIO APIs
 *                          	                                 
 *
 *  @note      This program is distributed in the hope  that it  
 * 	           will be useful,but WITHOUT ANY WARRANTY; without     
 *	           even the implied warranty of  MERCHANTABILITY or     
 *	           FITNESS FOR A PARTICULAR PURPOSE.  
 *                                                      
 * ***************************************************************                                                                
 */
 
#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

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
typedef enum
{
	GPIOA,
	GPIOB,
	GPIOC,

}eGPIO_Port_t;



typedef enum 
{
	INPUT_ANLOG             = 0b0000,
	INPUT_FLOATING          = 0b0100,
	INPUT_PULLUP_PULLDOWN   = 0b1000,  
									
	OUTPUT_SPEED_10MHZ_PP   = 0b0001,
	OUTPUT_SPEED_10MHZ_OD   = 0b0101,
	OUTPUT_SPEED_10MHZ_AFPP = 0b1001,
	OUTPUT_SPEED_10MHZ_AFOD = 0b1101,
									
	OUTPUT_SPEED_2MHZ_PP    = 0b0010,
	OUTPUT_SPEED_2MHZ_OD    = 0b0110,
	OUTPUT_SPEED_2MHZ_AFPP  = 0b1010,
	OUTPUT_SPEED_2MHZ_AFOD  = 0b1110,
									
	OUTPUT_SPEED_50MHZ_PP   = 0b0011,
	OUTPUT_SPEED_50MHZ_OD   = 0b0111,
	OUTPUT_SPEED_50MHZ_AFPP = 0b1011,
	OUTPUT_SPEED_50MHZ_AFOD = 0b1111 
}ePin_Mode_t;

/** Any pin that has "X_" is unavailable in this MCU*/
typedef enum
{
	PINA0=0,
	PINA1,
	PINA2,
	PINA3,
	PINA4,
	PINA5,
	PINA6,
	PINA7,
	PINA8,
	PINA9,
	PINA10,
	PINA11,
	PINA12,
	X_PINA13,
	X_PINA14,
	PINA15,
	PINB0,
	PINB1,
	X_PINB2,
	PINB3,
	PINB4,
	PINB5,
	PINB6,
	PINB7,
	PINB8,
	PINB9,
	PINB10,
	PINB11,
	PINB12,
	PINB13,
	PINB14,
	PINB15,
	X_PINC0,
	X_PINC1,
	X_PINC2,
	X_PINC3,
	X_PINC4,
	X_PINC5,
	X_PINC6,
	X_PINC7,
	X_PINC8,
	X_PINC9,
	X_PINC10,
	X_PINC11,
	X_PINC12,
	PINC13,
	PINC14,
	PINC15,
	TOTAL_PINS,
	TX1 = 9 ,
	RX1 = 10,
	TX2 = 1 ,
	RX2 = 2 ,
	TX3 = 27,
	RX3 = 28,
	AN0 = 0 ,  //A0
	AN1 = 1 ,
	AN2 = 2 ,
	AN3 = 3 ,
	AN4 = 4 ,
	AN5 = 5 ,
	AN6 = 6 ,
	AN7 = 7 ,  //A8
	AN8 = 16 , //B0
	AN9 = 17,  //B1
	
}ePinNum_t;

typedef enum ePin_Voltage_Level_t
{
	LOW,
	HIGH
}ePin_Voltage_Level_t;

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif
/*
 ##### How to use this driver #####
 
  1- Enable the GPIOx clock using the following function : GPIO_voidInit(eGPIO_Port_t );
  2- Configure the GPIO pin using GPIO_voidSetPinDirection(ePinNum_t,ePin_Mode_t).
     Choose one mode of the following : 
	 - INPUT_ANLOG            
	 - INPUT_FLOATING         
	 - INPUT_PULLUP_PULLDOWN  
	  						
	 - OUTPUT_SPEED_10MHZ_PP  
	 - OUTPUT_SPEED_10MHZ_OD  
	 - OUTPUT_SPEED_10MHZ_AFPP
	 - OUTPUT_SPEED_10MHZ_AFOD
	 						
	 - OUTPUT_SPEED_2MHZ_PP   
	 - OUTPUT_SPEED_2MHZ_OD   
	 - OUTPUT_SPEED_2MHZ_AFPP 
	 - OUTPUT_SPEED_2MHZ_AFOD 
	 
	 - OUTPUT_SPEED_50MHZ_PP  
	 - OUTPUT_SPEED_50MHZ_OD  
     - OUTPUT_SPEED_50MHZ_AFPP
     - OUTPUT_SPEED_50MHZ_AFOD
	 
*/
void GPIO_voidInit			   ( eGPIO_Port_t Port );
void GPIO_voidSetPinDirection  ( ePinNum_t Pin , ePin_Mode_t Mode );
void GPIO_voidSetPinValue      ( ePinNum_t Pin , ePin_Voltage_Level_t Copy_u8Value );
u8   GPIO_u8GetPinValue        ( ePinNum_t Pin );
void GPIO_voidSetPortValue     ( eGPIO_Port_t Port , u16 Value );
void GPIO_voidTogglePin		   ( ePinNum_t Pin );
void GPIO_voidLockPin		   ( ePinNum_t Pin );


#ifdef __cplusplus
} // extern "C"
#endif

#endif /*File_H_*/

/*** End of File **************************************************************/
