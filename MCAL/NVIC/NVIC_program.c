/**
 * *************************************************************************
 *  @file      NVIC_program.c			
 *  @author    Eslam Shahin (eslamshahin552000@gmail.com)                          
 *  @version   v2.0                                            
 *  @date      4/09/2020	                                 
 *  @brief     This file have the implementation of NVIC functions 
 *             in stm32f103
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
#include "NVIC_interface.h"
#include "NVIC_config.h"
#include "NVIC_private.h"

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
 * @fn               
 * @brief   		 
 * @param               		 
 * @return 			 
 * PRE-CONDITION     
 * POST-CONDITION     	  
 */
void NVIC_voidSetGlobalGroupAndSub(eInterrupt_Group_t GroupAndSub){
	
	SCB_AIRCR= GroupAndSub;
}

void NVIC_voidEnableInterrupt (eInterrupt_ID_IVT_t IntNumber){
	
	if ( IntNumber <=31){
		NVIC_ISER0|=(1<<IntNumber);
	}
	
	else if(IntNumber <=59){
		NVIC_ISER1|=(1<<(IntNumber - 32));
	}
	
	else{
		/* Rturn Error */
	}
	
}

void NVIC_voidDisableInterrupt(eInterrupt_ID_IVT_t IntNumber){
	
	if ( IntNumber <=31){
		SET_BIT( NVIC_ICER0 , IntNumber);
	}
	else if(IntNumber <=59){
		SET_BIT( NVIC_ICER1 ,( IntNumber - 32));
	}
	else{
		/* Rturn Error */
	}
	
}

void NVIC_voidSetPendingFlag  (eInterrupt_ID_IVT_t IntNumber){

	if ( IntNumber <=31){
		NVIC_ISPR0|=(1<<IntNumber);
	}
	
	else if(IntNumber <=59){
		NVIC_ISPR1|=(1<<(IntNumber - 32));
	}
	
	else{
		/* Rturn Error */
	}
	
}
void NVIC_voidClearPendingFlag(eInterrupt_ID_IVT_t IntNumber){
	
	if ( IntNumber <=31){
		NVIC_ICPR0|=(1<<IntNumber);
	}
	
	else if(IntNumber <=59){
		NVIC_ICPR1|=(1<<(IntNumber - 32));
	}
	
	else{
		/* Rturn Error */
	}
	
}

u8   NVIC_u8GetActiveFlag(eInterrupt_ID_IVT_t IntNumber){
	
	u8 Local_u8Result=0;
		if ( IntNumber <=31){
		Local_u8Result = GET_BIT(NVIC_IABR0,IntNumber);
	}
	
	else if(IntNumber <=59){
	Local_u8Result = GET_BIT(NVIC_IABR1,(IntNumber-32));
	}
	
	else{
		/* Rturn Error */
	}
	
	return Local_u8Result;
	
}
void NVIC_voidSetPriorty(eInterrupt_ID_IVT_t IntNumber,u8 copy_u8GroupAndSubPriorty ){
	 /* For External prephrals */
//	NVIC_IPR[IntNumber]|= 0b0000 << 4 ; /* To write it in MSBs */
	NVIC_IPR[IntNumber]|= copy_u8GroupAndSubPriorty << 4 ; /* To write it in MSBs */
	
}
 

/*************** END OF FUNCTIONS *********************************************/
