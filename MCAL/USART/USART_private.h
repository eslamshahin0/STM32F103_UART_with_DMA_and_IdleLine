/**
 * ***************************************************************
 *  @file      USART_private.h			
 *  @author    Eslam Shahin (eslamshahin552000@gmail.com)                          
 *  @version   v2.0                                            
 *  @date      20/09/2020		                                   
 *  @brief     USART modules register adresses
 *                          	                                 
 *
 *  @note      This program is distributed in the hope  that it  
 * 	           will be useful,but WITHOUT ANY WARRANTY; without     
 *	           even the implied warranty of  MERCHANTABILITY or     
 *	           FITNESS FOR A PARTICULAR PURPOSE.  
 *                                                      
 * ***************************************************************                                                                
 */
 
#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

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
#define USART1_BASE_ADRESS 	0x40013800
#define USART2_BASE_ADRESS 	0x40004400
#define USART3_BASE_ADRESS 	0x40004800

/******************************************************************************
* Typedefs
*******************************************************************************/
typedef struct
{
	volatile u32 SR;           /* 00 */
	volatile u32 DR;           /* 04 */
	volatile u32 BRR;          /* 08 */
	volatile u32 CR1;          /* 0C */
	volatile u32 CR2;          /* 10 */
	volatile u32 CR3;          /* 14 */
	volatile u32 GTPR;		   /* 18 */
	
}USART_t;

USART_t * UARTx [USART_TOTAL_NUMBERS] = {
    (USART_t *)USART1_BASE_ADRESS,
    (USART_t *)USART2_BASE_ADRESS,
    (USART_t *)USART3_BASE_ADRESS
};


#endif /*File_H_*/

/*** End of File **************************************************************/
