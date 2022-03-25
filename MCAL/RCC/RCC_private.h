/**
 * ***************************************************************
 *  @file      RCC_private.h			
 *  @author    Eslam Shahin (eslamshahin552000@gmail.com)                          
 *  @version   v2.0                                            
 *  @date      08/08/2020		                                   
 *  @brief     The Registers adresses for the RCC module on 
 *             STM32F103
 *                          	                                 
 *  @note      This program is distributed in the hope  that it  
 * 	           will be useful,but WITHOUT ANY WARRANTY; without     
 *	           even the implied warranty of  MERCHANTABILITY or     
 *	           FITNESS FOR A PARTICULAR PURPOSE.  
 *                                                      
 * ***************************************************************                                                                
 */
 
#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
/* Register Definitions */
#define RCC_BASE_ADRESS  0x40021000
/* The RCC_CR , RCC_CFGR , RCC_AHBENR , RCC_APB2ENR and RCC_APB1ENR Registers
   are responsible for the peripherals clock */

#define RCC_CR 			 *((volatile u32*)(RCC_BASE_ADRESS + 0X00))  //1
#define RCC_CFGR         *((volatile u32*)(RCC_BASE_ADRESS + 0x04))  //2
#define RCC_CIR			 *((volatile u32*)(RCC_BASE_ADRESS + 0x08))
#define RCC_APB2RSTR 	 *((volatile u32*)(RCC_BASE_ADRESS + 0x0C))
#define RCC_APB1RSTR	 *((volatile u32*)(RCC_BASE_ADRESS + 0x10))
#define RCC_AHBENR		 *((volatile u32*)(RCC_BASE_ADRESS + 0x14)) //3
#define RCC_APB2ENR		 *((volatile u32*)(RCC_BASE_ADRESS + 0x18)) //4
#define RCC_APB1ENR		 *((volatile u32*)(RCC_BASE_ADRESS + 0x1C)) //5
#define RCC_BDCR 		 *((volatile u32*)(RCC_BASE_ADRESS + 0x20))
#define RCC_CSR		 	 *((volatile u32*)(RCC_BASE_ADRESS + 0x24))

/******************************************************************************
* Configuration Constants
*******************************************************************************/
/* Clock Types */
#define RCC_HSE_CRYSTAL      0
#define RCC_HSE_RC           1
#define RCC_HSI              2
#define RCC_PLL              3

/* PLL Options */
#define RCC_PLL_IN_HSI_DIV_2  0
#define RCC_PLL_IN_HSE_DIV_2  1
#define RCC_PLL_IN_HSE        2

/******************************************************************************
* Macros
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

#endif /*File_H_*/

/*** End of File **************************************************************/
