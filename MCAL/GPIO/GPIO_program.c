/**
 * *************************************************************************
 *  @file      GPIO_program.c			
 *  @author    Eslam Shahin (eslamshahin552000@gmail.com)                          
 *  @version   v3.0
 *  @date      03/09/2020                                   
 *  @brief     This file have the implementation of GPIO module 
 *				in STM32F103
 *                          	                                 
 *
 *  @note      This program is distributed in the hope  that it  
 * 	           will be useful,but WITHOUT ANY WARRANTY; without     
 *	           even the implied warranty of  MERCHANTABILITY or     
 *	           FITNESS FOR A PARTICULAR PURPOSE.  
 *                                                      
 * *************************************************************************                                                                
 */
 
/******************************************************************************
* Includes
*******************************************************************************/
// Include libraries
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// Include files 
#include "RCC_interface.h"

#include "GPIO_interface.h"
#include "GPIO_config.h"
#include "GPIO_private.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Static Function Prototypes
*******************************************************************************/


/******************************************************************************
* Function Definitions
*******************************************************************************/

/**             
 * @brief   initlize GPIO module    		 
 * @param   Port the port tyoe             		 
 * @return  void 	    	  
 */

void GPIO_voidInit(eGPIO_Port_t Port)
{
	switch (Port)
	{
		case GPIOA:
		RCC_voidEnableClock(APB2, APB2_IOPAEN);
		break;
		case GPIOB:
		RCC_voidEnableClock(APB2, APB2_IOPBEN);
		break;
		case GPIOC:
		RCC_voidEnableClock(APB2, APB2_IOPCEN);
		break;
		default :
		break;
	}
	/*
	for (u8 i=0;i<TOTAL_PINS;i++){
#if INITIALIZATION_MODE == ALL_OUTPUT_LOW 
		GPIO_voidSetPinDirection(i,OUTPUT);
		GPIO_voidSetPinValue(i,LOW);
#elif INITIALIZATION_MODE == ALL_OUTPUT_HIGH 
		GPIO_voidSetPinDirection(i,OUTPUT);
		GPIO_voidSetPinValue(i,HIGH);
#elif INITIALIZATION_MODE == ALL_INPUT
		GPIO_voidSetPinDirection(i,INPUT_FLOATING);
#endif
	}
	*/
}

/**             
 * @brief   Set specific pin mode     		 
 * @param   Pin Pin number with gpio
 * @param   Mode  Pin mode 
 * @return  void 	    	  
 */
void GPIO_voidSetPinDirection  ( ePinNum_t Pin , ePin_Mode_t Mode )
{
	u8 Copy_u8Port = Pin/16;
	u8 Copy_u8Pin  = Pin%16;
	
	if(Copy_u8Pin <= 7 )
	{
		/* For the lower pins register (every pin has a 4 bits to config )*/
		GPIOx[Copy_u8Port]->CRL &= ~ ( ( 0b1111 )    << ( Copy_u8Pin * 4 ));
		GPIOx[Copy_u8Port]->CRL |= ( Mode ) << ( Copy_u8Pin * 4 );
	}
	else if(Copy_u8Pin <=15 )
	{
		/* For the higher pins register (every pin has a 4 bits to config )*/
		Copy_u8Pin = Copy_u8Pin - 8; /* to reset count to deal with the register easy*/
		GPIOx[Copy_u8Port]->CRH &= ~ ( ( 0b1111 )    << ( Copy_u8Pin * 4 ) );
		GPIOx[Copy_u8Port]->CRH |=   ( Mode )        << ( Copy_u8Pin * 4 );
	}
}

/**             
 * @brief   Set specific logic output     		 
 * @param   Pin Pin number with gpio
 * @param   Value  Voltage Level
 * @return  void 	    	  
 */
void GPIO_voidSetPinValue ( ePinNum_t Pin , ePin_Voltage_Level_t Value )
{
	u8 Copy_u8Port = Pin/16;
	u8 Copy_u8Pin  = Pin%16;
	
	if( Value ==  HIGH )
	{
		GPIOx[Copy_u8Port]->BSRR=(1<<Copy_u8Pin); /* To set the equal bit in the ODR register in one step*/
	}
	else if( Value == LOW )
	{
		GPIOx[Copy_u8Port]->BRR=(1<<Copy_u8Pin); /* To reset the equal bit in the ODR register in one step*/
	}
}

/**
 * @brief   Set the port value in one time
 * @param   Pin Pin number with gpio
 * @return  void
 */
void GPIO_voidSetPortValue ( eGPIO_Port_t Port , u16 Value )
{
	GPIOx[Port]->ODR=Value;
}

/**             
 * @brief   Get specific pin logic input     		 
 * @param   Pin Pin number with gpio
 * @return  void 	    	  
 */
u8   GPIO_u8GetPinValue( ePinNum_t Pin )
{
	u8 Copy_u8Port = Pin/16;
	u8 Copy_u8Pin  = Pin%16;

	return GET_BIT(GPIOx[Copy_u8Port]->IDR , Copy_u8Pin );
}

/**
 * @brief   Toggle specific pin
 * @param   Pin Pin number with gpio
 * @return  void
 */
void GPIO_voidTogglePin (ePinNum_t Pin){
	u8 Copy_u8Port = Pin/16;
	u8 Copy_u8Pin  = Pin%16;

	TOG_BIT (GPIOx[Copy_u8Port]->ODR , Copy_u8Pin) ;

}

/**             
 * @brief   Lock specific pin (disable to change the pin mode agin till reset)     		 
 * @param   Pin Pin number with gpio
 * @return  void 	    	  
 */
void GPIO_voidLockPin( ePinNum_t Pin )
{
	u8 Copy_u8Port = Pin/16;
	u8 copy_u8Pin  = Pin%16;

	SET_BIT(GPIOx[Copy_u8Port]->LCKR , copy_u8Pin );
	/* LCKK Bit num 16  It can only be modified using the Lock Key Writing Sequence. */
	/* Starting Write Sequence to enable Lock */
	SET_BIT(GPIOx[Copy_u8Port]->LCKR , 16 );
	CLEAR_BIT(GPIOx[Copy_u8Port]->LCKR , 16 );
	SET_BIT(GPIOx[Copy_u8Port]->LCKR , 16 );
	(void)GET_BIT(GPIOx[Copy_u8Port]->LCKR , 16 );
}


/*************** END OF FUNCTIONS *********************************************/
