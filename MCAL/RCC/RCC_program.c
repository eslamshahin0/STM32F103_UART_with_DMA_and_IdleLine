/**
 * *************************************************************************
 *  @file      RCC_program.c
 *  @author    Eslam Shahin (eslamshahin552000@gmail.com)
 *  @version   v2.0
 *  @date      08/08/2020
 *  @brief     This file have the implementation of RCC module in stm32
 *             , this module is used to enable different peripherals 
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
#include "RCC_private.h"
#include "RCC_config.h"

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
 * @brief       initialize the system clock according to the user
 *              configurations from <RCC_config.h>
 * @param[in]   void
 * @return   	void
 *
 * This function is used to config the Three different clock sources
 * can be used to drive the system clock (SYSCLK)
 *  <br>
 * • HSI oscillator clock <br>
 * • HSE oscillator clock <br>
 * • PLL clock <br>
 *
 */

void RCC_voidInitSysClock(void)
{
	#if     RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL
		/* Enable HSE with no bypass */
		RCC_CR   = 0x00010000; 
		RCC_CFGR = 0x00000001;
		/* Wait till HSE be ready */
		while(GET_BIT(RCC_CR,17) !=1);

	#elif   RCC_CLOCK_TYPE == RCC_HSE_RC
		/* Enable HSE with bypass */
		/* Bypass means that the pin XTAL1 is not enabled 
		and the External RC is used 
		*/
		RCC_CR   = 0x00050000; 
		RCC_CFGR = 0x00000001;
		/* Wait till HSE RC be ready */
		while(GET_BIT(RCC_CR,17) !=1);
		

	#elif   RCC_CLOCK_TYPE == RCC_HSI
		RCC_CR   = 0x00000081; /* Enable HSI + Trimming = 0 */
		RCC_CFGR = 0x00000000;
		/* Wait till HSI RC be ready */
		while(GET_BIT(RCC_CR,1) !=1);

	#elif   RCC_CLOCK_TYPE == RCC_PLL

		#if   RCC_PLL_INPUT == RCC_PLL_IN_HSI_DIV_2
			RCC_CR   = 0x01000081;
			RCC_CFGR = 0x00000002;
			RCC_CFGR &= 0xffc3ffff;//Clear the 4 bits of PLLMUL
			RCC_CFGR |= ((RCC_PLL_MUL_VAL-2)<<18);

		#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE_DIV_2
		/* on External Crystal OSC*/
			RCC_CR   = 0x01010080;
			RCC_CFGR = 0x00030002;
			RCC_CFGR &= 0xffc3ffff;//Clear the 4 bits of PLLMUL
			RCC_CFGR |=((RCC_PLL_MUL_VAL-2)<<18);

		#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE
			RCC_CR=0x01010080;
			RCC_CFGR=0x00010002;
			RCC_CFGR &=0xffc3ffff;//Clear the 4 bits of PLLMUL
			RCC_CFGR|=((RCC_PLL_MUL_VAL-2)<<18);

		#endif

	#else
		#error " WRONG CONFIGURATION OF CLOCK "
	#endif
}

/**
 * @brief       Enable the peripheral clock
 * @param[in]   Copy_u8BusId  The bus that has the peripheral
 * @param[in]	Copy_u8BusId  The peripheral on the bus
 * @return      void
 *
 * This function is used to enable the module clock to be able
 * to use it
 */
void RCC_voidEnableClock(BusName_t Copy_u8BusId , PeripheralID_t Copy_u8PerId)
{
	switch (Copy_u8BusId)
	{
		case AHB  : SET_BIT(RCC_AHBENR  ,Copy_u8PerId);   break;
		case APB1 : SET_BIT(RCC_APB1ENR ,Copy_u8PerId);   break;
		case APB2 : SET_BIT(RCC_APB2ENR ,Copy_u8PerId);   break;
		default       : break;
	}

}

/**
 * @brief       Disable the peripheral clock
 * @param[in]   Copy_u8BusId  The bus that has the peripheral
 * @param[in]	Copy_u8BusId  The peripheral on the bus
 * @return      void
 *
 * This function is used to disable the module clock to save power
 * when you finish using it
 */
void RCC_voidDisableClock(BusName_t Copy_u8BusId , PeripheralID_t Copy_u8PerId)
{
	switch (Copy_u8BusId)
	{
		case AHB  : CLEAR_BIT(RCC_AHBENR  ,Copy_u8PerId);   break;
		case APB1 : CLEAR_BIT(RCC_APB1ENR ,Copy_u8PerId);   break;
		case APB2 : CLEAR_BIT(RCC_APB2ENR ,Copy_u8PerId);   break;
		default       : break;
	}

}

/**
 * @brief       Config the AHP bus speed from the system clock
 * @param[in]   copy_busSpeedDivFactor  The bus clock divided from the system clock
 * @return      void
 * 
 * For setting the AHP clock frequency from the system clock , the clock could be
 * taken directly from the cpu clock or from a devion factor 2 , 4 , 8 , 16 , 64 , 128 , 256
 * <br>
 * Please  note that the AHB maximum frequency , and the APB takes its clock from the AHB
 */
void RCC_voidSetAHBusClock(AHB_ClockSpeed_t copy_busSpeedDivFactor)
{
	/*Set and cleared by software to control the division factor of the AHB clock*/
	RCC_CFGR &=0xffffff0f;
	RCC_CFGR|=(copy_busSpeedDivFactor<<4);
}

/**
 * @brief       Config the APB1 or APB2 bus speed from AHB clock
 * @param[in]   copy_u8busid  The bus name " APB1 or APB2 "
 * @param[in]   copy_busSpeedDivFactor  The bus clock divided from the AHP clock
 * @return      void
 *
 * Setting the bus clock from the AHB clock
 */
void RCC_voidSetAPBusClock(BusName_t copy_u8busid, APB_ClockSpeed_t copy_busSpeedDivFactor)
{

	switch(copy_u8busid)
	{
		case AHB : break;

		case APB1 :
		RCC_CFGR &=0xfffff8ff;/* the software has to set correctly these bits to not exceed 36 MHz on this domain.*/
		RCC_CFGR|=(copy_busSpeedDivFactor<<8);
		break;

		case APB2 :
		RCC_CFGR &=0xffc7ff0f;/*Set and cleared by software to control the division factor of the APB high-speed clock*/
		RCC_CFGR|=(copy_busSpeedDivFactor<<11);
		break;
		default : break;

	}
	
}

/**
 * @brief       Enable Clock Security System 
 * @param[in]   void 
 * @return      void
 *
 * If you call this function , it will detect external clock stablity 
 * and if the external clock was not stable it will rise the interrupt flag 
 * then switch to HSI clock automaticly
 */
void RCC_voidEnableClockSecurity(void)
{
	SET_BIT(RCC_CR,19);
}
/**
 * @brief       Disable Clock Security System 
 * @param[in]   void 
 * @return      void
 *
 */
void RCC_voidDisableClockSecurity(void)
{
	CLEAR_BIT(RCC_CR,19);
}

/**
 * @brief       Trimming step for HSI clock
 * @param[in]   TrimValue The incrise or decrise to the HSI clock
 * @return      void
 *
 * Provide an additional user-programmable trimming value each step is 40KHz.
 * It can be programmed to adjust to variations in voltage and temperature
 * that influence the frequency of the internal HSI RC.
 * The default value is 16, which, when added to the HSICAL value, should trim the HSI to 8
 * MHz ± 1%. The trimming step (Fhsitrim) is around 40 kHz between two consecutive HSICAL
 * steps.
 */
void RCC_voidHSITirm(TrimType_t TrimValue)
{
	/* Get the Bits 7:3 */
	u32 localCurrentTrim=(RCC_CR&0x000000f8)>>3;
	if (TrimValue==HSI_INCRISE)
	{
		RCC_CR |= (localCurrentTrim+1)<<3;
	}
	else if (TrimValue==HSI_DECRISE)
	{
		RCC_CR |= (localCurrentTrim-1)<<3;
	}
	else {}
	
}
/**
 * @brief       Disable Clock Security System 
 * @param[in]   ClockSource Clock sourse for the pin 
 * @return      void
 * 
 * When the System Clock is selected to output to the MCO pin, make sure that this clock
 * does not exceed 50 MHz (the maximum IO speed)
 *
 */
void RCC_voidClockOutput(OutputClockSource_t ClockSource)
{
	/* Make the clock bits zeros*/
		RCC_CFGR &=0xfff8ffff;
		
	if (ClockSource == SYSCLK )
	{
		RCC_CFGR |=0x00040000;
	}
	else if (ClockSource == HSI)
	{
		RCC_CFGR |=0x00050000;	
	}
	else if (ClockSource == HSE)
	{
		RCC_CFGR |=0x00060000;
	}
	else if (ClockSource == PLL_DIV_2)
	{
		RCC_CFGR |=0x00070000;
	}
	else {
		/* NO CLOCK*/
	}
}
/*************** END OF FUNCTIONS *********************************************/
