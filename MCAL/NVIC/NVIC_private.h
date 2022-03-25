/**
 * ***************************************************************
 *  @file      NVIC_private.h			
 *  @author    Eslam Shahin (eslamshahin552000@gmail.com)                          
 *  @version   v2.0                                            
 *  @date      4/09/2020		                                   
 *  @brief     NVIC registers
 *                          	                                 
 *
 *  @note      This program is distributed in the hope  that it  
 * 	           will be useful,but WITHOUT ANY WARRANTY; without     
 *	           even the implied warranty of  MERCHANTABILITY or     
 *	           FITNESS FOR A PARTICULAR PURPOSE.  
 *                                                      
 * ***************************************************************                                                                
 */
 
#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_

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
/* NVIC BASE */
#define NVIC_BASE_ADRESS 		0xE000E100

/* NVIC Adresses in memory map */
#define NVIC_ISER0         *(( volatile u32*)NVIC_BASE_ADRESS ) 		 /* For Enable ex_interupts from 0 to 31*/
#define NVIC_ISER1         *(( volatile u32*)(NVIC_BASE_ADRESS + 0X04) )  /* For Enable ex_interupts from 32 to 63*/

#define NVIC_ICER0         *(( volatile u32*)(NVIC_BASE_ADRESS + 0X80 ))  /* For Disable ex_interupts from 0 to 31*/
#define NVIC_ICER1         *(( volatile u32*)(NVIC_BASE_ADRESS + 0X84 ))  /* For Disable ex_interupts from 32 to 63*/

#define NVIC_ISPR0         *(( volatile u32*)(NVIC_BASE_ADRESS + 0X100 )) /* Force interrupts into the pending state */
#define NVIC_ISPR1         *(( volatile u32*)(NVIC_BASE_ADRESS + 0X104 )) /* Force interrupts into the pending state */

#define NVIC_ICPR0         *(( volatile u32*)(NVIC_BASE_ADRESS + 0X180 )) /* Clear the pending state */
#define NVIC_ICPR1         *(( volatile u32*)(NVIC_BASE_ADRESS + 0X184 )) /* Clear the pending state */
																	  
#define NVIC_IABR0         *(( volatile u32*)(NVIC_BASE_ADRESS + 0X184 )) /* indicate which interrupts are active 0 to 31 */
#define NVIC_IABR1         *(( volatile u32*)(NVIC_BASE_ADRESS + 0X184 )) /* indicate which interrupts are active 32 to 63 */

#define NVIC_IPR		   ((volatile u8* )(NVIC_BASE_ADRESS + 0x300) )	 /* a 4-bit priority field for each interrupt */

/* Sys Control Block Core Prephral (Application interrupt and reset control register) */
#define SCB_AIRCR		   *(( volatile u32*)(0XE000ED00 + 0X0C) )
		
/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Variables
*******************************************************************************/


#endif /*File_H_*/

/*** End of File **************************************************************/