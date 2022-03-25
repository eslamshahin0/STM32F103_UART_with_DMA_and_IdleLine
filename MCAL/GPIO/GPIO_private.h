/**
 * ***************************************************************
 *  @file      GPIO_private.h			
 *  @author    Eslam Shahin (eslamshahin552000@gmail.com)                          
 *  @version   v2.0                                            
 *  @date      03/09/2020	                                   
 *  @brief     GPIO Register's addresses
 *                          	                                 
 *
 *  @note      This program is distributed in the hope  that it  
 * 	           will be useful,but WITHOUT ANY WARRANTY; without     
 *	           even the implied warranty of  MERCHANTABILITY or     
 *	           FITNESS FOR A PARTICULAR PURPOSE.  
 *                                                      
 * ***************************************************************                                                                
 */
 
#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define ALL_OUTPUT_LOW   0
#define ALL_OUTPUT_HIGH  1
#define ALL_INPUT        2

/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/
#define GPIOA_Base_Address        0x40010800  
#define GPIOB_Base_Address        0x40010C00   
#define GPIOC_Base_Address        0x40011000      

/******************************************************************************
* Typedefs
*******************************************************************************/
typedef struct
{
	volatile u32 CRL  ;        /*00*/
	volatile u32 CRH  ;        /*04*/
	volatile u32 IDR  ;        /*08*/
	volatile u32 ODR  ;        /*0C*/
	volatile u32 BSRR ;        /*10*/
	volatile u32 BRR  ;        /*14*/
	volatile u32 LCKR ;        /*18*/

}sGPIO_t;

sGPIO_t * GPIOx[3]={
	(( sGPIO_t*)GPIOA_Base_Address),
	(( sGPIO_t*)GPIOB_Base_Address),
	(( sGPIO_t*)GPIOC_Base_Address),
};
/******************************************************************************
* Variables
*******************************************************************************/

#endif /*File_H_*/

/*** End of File **************************************************************/
