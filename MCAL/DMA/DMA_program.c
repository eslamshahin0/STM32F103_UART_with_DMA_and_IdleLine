/**
 * *************************************************************************
 *  @file      DMA_program.c			
 *  @author    Eslam Shahin (eslamshahin552000@gmail.com)                          
 *  @version   v2.1
 *  @date      17/09/2020                                 
 *  @brief     This file have the implementation of Direct memory access in
 *  			STM32F103C8
 *                          	                                 
 *
 *  @note      This program is distributed in the hope  that it  
 * 	           will be useful,but WITHOUT ANY WARRANTY; without     
 *	           even the implied warranty of  MERCHANTABILITY or     
 *	           FITNESS FOR A PARTICULAR PURPOSE.  
 *                                                      
 * *************************************************************************                                                                
 */
 /*Change log v2.1
  * Add DMA2 to the driver
  * Set the callback functions option
  * Change the Register definitions to array of struct
  *
  * */
/******************************************************************************
* Includes
*******************************************************************************/
// Include libraries
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// Include files 
#include "RCC_interface.h"
#include "DMA_interface.h"
#include "DMA_config.h"
#include "DMA_private.h"

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
static void (*DMA1_Fptr[7][3]) (void)= {NULLPTR};
static void (*DMA2_Fptr[5][3]) (void)= {NULLPTR};
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

/**
 * @brief   Enable DMAx Clock
 * @param   DMA_Number DMAx Number
 * @return  void
 */
void DMA_voidInit(eDMA_Number_t DMA_Number){
	RCC_voidEnableClock(AHB,0+DMA_Number);
}

/**
 * @brief   Configure all parameters required to use DMAx channel
 * @param   DMA_Config the address of configuration struct
 * @return  void
 */
void DMA_voidInitChannel(sDMA_Config_t * DMA_Config)
{
	/* Enable Channel */
	CLEAR_BIT(DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR ,0);
	/* memory to memory mode  */
	if (DMA_Config->M2M_Mode == DMA_ENABLE )
		SET_BIT(DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR ,14);
	else 
		CLEAR_BIT(DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR ,14);
	
	/* Channel priority  */
	DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR &=0XFFFFCFFF;
	DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR |= (DMA_Config->ChannelPriority)<<12;
	
	/* Memory size */
	DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR &=0XFFFFF3FF;
	DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR |= (DMA_Config->MemorySize)<<10;
	
	/* Peripheral Size */
	DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR &=0XFFFFFCFF;
	DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR |= (DMA_Config->PeripheralSize)<<8;
	
	/* Memory Increment  */
	if (DMA_Config->MemoryIncrement == DMA_ENABLE )
		SET_BIT(DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR ,7);
	else 
		CLEAR_BIT(DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR ,7);
	
	/* Peripheral Increment  */
	if (DMA_Config->PeripheralIncrement == DMA_ENABLE )
		SET_BIT(DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR ,6);
	else 
		CLEAR_BIT(DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR ,6);
	
	/* Read From Memory  */
	if (DMA_Config->DataDirection == ReadFromMemory )
		SET_BIT(DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR ,4);
	else 
		CLEAR_BIT(DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR ,4);
	
	/* TransferErrorInterrupt   */
	if (DMA_Config->TransferErrorInterrupt == DMA_ENABLE )
		SET_BIT(DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR ,3);
	else 
		CLEAR_BIT(DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR ,3);
	
	/* HalfTransferInterrupt  */
	if (DMA_Config->HalfTransferInterrupt == DMA_ENABLE )
		SET_BIT(DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR ,2);
	else 
		CLEAR_BIT(DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR ,2);
	
		/* TransferCompleteInterrupt  */
	if (DMA_Config->TransferCompleteInterrupt == DMA_ENABLE )
		SET_BIT(DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR ,1);
	else 
		CLEAR_BIT(DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR ,1);

	/* Circle */
if (DMA_Config->CircularMode== DMA_ENABLE )
	SET_BIT(DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR ,5);
else
	CLEAR_BIT(DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR ,5);

		
}

/**
 * @brief   Start DMAx channel with addresses to transfer data
 * @param   DMA_Config the address of configuration struct
 * @param   Pu32SourceAdrr      source address
 * @param   Pu32DestinationAdrr Destination address
 * @param   NumberOfBlocks number of units to transfer
 * @return  void
 */
void DMA_voidStartTransfer(sDMA_Config_t * DMA_Config,u32  Pu32SourceAdrr , u32  Pu32DestinationAdrr , u16 NumberOfBlocks)
{

	DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CPAR=Pu32SourceAdrr;
	DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CMAR=Pu32DestinationAdrr;
	DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CNDTR=NumberOfBlocks;	/* Num of data blocks*/
	SET_BIT(DMAx[DMA_Config->DMA_Number]->Channel[DMA_Config->DMA_Channel].CRR,0); 	/* Enable DMA */
	
}
	
/**
 * @brief   Assign the call back function to be executed when corresponding interrupt happen
 * @param   DMA_Number DMAx number
 * @param   DMA_Channel  DMAx Channel
 * @param   DMA_InterruptSource DMAx Interrupt Source
 * @param   LocalFptr pointer to the function will be executed due to corresponding interrupt event
 * @return  void
 */
void DMA_voidSetCallBack(eDMA_Number_t DMA_Number ,eDMA_Channel_t DMA_Channel,eDMA_InterruptSource_t DMA_InterruptSource , void (*LocalFptr)(void) ){
	if(DMA_Number==USE_DMA_1)
		DMA1_Fptr[DMA_Channel][DMA_InterruptSource] = LocalFptr ;
	else
		DMA2_Fptr[DMA_Channel][DMA_InterruptSource] = LocalFptr;
	
}

void DMA1_Channel1_IRQHandler(){
	
	/* Check the Complete transfer flag */
	if (GET_BIT(DMAx[USE_DMA_1]->ISR,1)==1){
		if (DMA1_Fptr[0][0] != NULLPTR) {
			DMA1_Fptr[0][0]();
	    }
		/* Clears the TCIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_1]->IFCR ,1);
	}
	 	/* Check the half transfer flag */
	else if (GET_BIT(DMAx[USE_DMA_1]->ISR,2)==1){
		if (DMA1_Fptr[0][1] != NULLPTR) {
			DMA1_Fptr[0][1]();
	    }
		/* Clears the THIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_1]->IFCR ,2);
	}	 	
	/* Check the Error transfer flag */
	else if (GET_BIT(DMAx[USE_DMA_1]->ISR,3)==1){
		if (DMA1_Fptr[0][2] != NULLPTR) {
			DMA1_Fptr[0][2]();
	    }
		/* Clears the EHIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_1]->IFCR ,3);
	}

}
void DMA1_Channel2_IRQHandler(){
	
	/* Check the Complete transfer flag */
	if (GET_BIT(DMAx[USE_DMA_1]->ISR,5)==1){
		if (DMA1_Fptr[1][0] != NULLPTR) {
			DMA1_Fptr[1][0]();
	    }
		/* Clears the TCIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_1]->IFCR ,5);
	}
	 	/* Check the half transfer flag */
	else if (GET_BIT(DMAx[USE_DMA_1]->ISR,6)==1){
		if (DMA1_Fptr[1][1] != NULLPTR) {
			DMA1_Fptr[1][1]();
	    }
		/* Clears the THIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_1]->IFCR ,6);
	}	 	
	/* Check the Error transfer flag */
	else if (GET_BIT(DMAx[USE_DMA_1]->ISR,7)==1){
		if (DMA1_Fptr[1][2] != NULLPTR) {
			DMA1_Fptr[1][2]();
	    }
		/* Clears the EHIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_1]->IFCR ,7);
	}

}
void DMA1_Channel3_IRQHandler(){
	/* Check the Complete transfer flag */
	if (GET_BIT(DMAx[USE_DMA_1]->ISR,9)==1){
		if (DMA1_Fptr[2][0] != NULLPTR) {
			DMA1_Fptr[2][0]();
	    }
		/* Clears the TCIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_1]->IFCR ,9);
	}
	 	/* Check the half transfer flag */
	else if (GET_BIT(DMAx[USE_DMA_1]->ISR,10)==1){
		if (DMA1_Fptr[2][1] != NULLPTR) {
			DMA1_Fptr[2][1]();
	    }
		/* Clears the THIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_1]->IFCR ,10);
	}	 	
	/* Check the Error transfer flag */
	else if (GET_BIT(DMAx[USE_DMA_1]->ISR,11)==1){
		if (DMA1_Fptr[2][2] != NULLPTR) {
			DMA1_Fptr[2][2]();
	    }
		/* Clears the EHIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_1]->IFCR ,11);
	}

}
void DMA1_Channel4_IRQHandler(){
	/* Check the Complete transfer flag */
	if (GET_BIT(DMAx[USE_DMA_1]->ISR,13)==1){
		if (DMA1_Fptr[3][0] != NULLPTR) {
			DMA1_Fptr[3][0]();
	    }
		/* Clears the TCIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_1]->IFCR ,13);
	}
	 	/* Check the half transfer flag */
	 if (GET_BIT(DMAx[USE_DMA_1]->ISR,14)==1){
		if (DMA1_Fptr[3][1] != NULLPTR) {
			DMA1_Fptr[3][1]();
	    }
		/* Clears the THIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_1]->IFCR ,14);
	}	 	
	/* Check the Error transfer flag */
	if (GET_BIT(DMAx[USE_DMA_1]->ISR,15)==1){
		if (DMA1_Fptr[3][2] != NULLPTR) {
			DMA1_Fptr[3][2]();
	    }
		/* Clears the EHIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_1]->IFCR ,15);
	}
	
}
void DMA1_Channel5_IRQHandler(){
	/* Check the Complete transfer flag */
	if (GET_BIT(DMAx[USE_DMA_1]->ISR,17)==1){
		if (DMA1_Fptr[4][0] != NULLPTR) {
			DMA1_Fptr[4][0]();
	    }
		/* Clears the TCIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_1]->IFCR ,17);
	}
	 	/* Check the half transfer flag */
	 if (GET_BIT(DMAx[USE_DMA_1]->ISR,18)==1){
		if (DMA1_Fptr[4][1] != NULLPTR) {
			DMA1_Fptr[4][1]();
	    }
		/* Clears the THIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_1]->IFCR ,18);
	}	 	
	/* Check the Error transfer flag */
	 if (GET_BIT(DMAx[USE_DMA_1]->ISR,19)==1){
		if (DMA1_Fptr[4][2] != NULLPTR) {
			DMA1_Fptr[4][2]();
	    }
		/* Clears the EHIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_1]->IFCR ,19);
	}

}
void DMA1_Channel6_IRQHandler(){
	/* Check the Complete transfer flag */
	if (GET_BIT(DMAx[USE_DMA_1]->ISR,21)==1){
		if (DMA1_Fptr[5][0] != NULLPTR) {
			DMA1_Fptr[5][0]();
	    }
		/* Clears the TCIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_1]->IFCR ,21);
	}
	 	/* Check the half transfer flag */
	 if (GET_BIT(DMAx[USE_DMA_1]->ISR,22)==1){
		if (DMA1_Fptr[5][1] != NULLPTR) {
			DMA1_Fptr[5][1]();
	    }
		/* Clears the THIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_1]->IFCR ,22);
	}	 	
	/* Check the Error transfer flag */
	 if (GET_BIT(DMAx[USE_DMA_1]->ISR,23)==1){
		if (DMA1_Fptr[5][2] != NULLPTR) {
			DMA1_Fptr[5][2]();
	    }
		/* Clears the EHIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_1]->IFCR ,23);
	}

}
void DMA1_Channel7_IRQHandler(){
	/* Check the Complete transfer flag */
	if (GET_BIT(DMAx[USE_DMA_1]->ISR,25)==1){
		if (DMA1_Fptr[6][0] != NULLPTR) {
			DMA1_Fptr[6][0]();
	    }
		/* Clears the TCIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_1]->IFCR ,25);
	}
	 	/* Check the half transfer flag */
	 if (GET_BIT(DMAx[USE_DMA_1]->ISR,26)==1){
		if (DMA1_Fptr[6][1] != NULLPTR) {
			DMA1_Fptr[6][1]();
	    }
		/* Clears the THIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_1]->IFCR ,26);
	}	 	
	/* Check the Error transfer flag */
	 if (GET_BIT(DMAx[USE_DMA_1]->ISR,27)==1){
		if (DMA1_Fptr[6][2] != NULLPTR) {
			DMA1_Fptr[6][2]();
	    }
		/* Clears the EHIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_1]->IFCR ,27);
	}

}

void DMA2_Channel1_IRQHandler(){
	/* Check the Complete transfer flag */
	if (GET_BIT(DMAx[USE_DMA_2]->ISR,5)==1){
		if (DMA2_Fptr[1][0] != NULLPTR) {
			DMA2_Fptr[1][0]();
	    }
		/* Clears the TCIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_2]->IFCR ,5);
	}
	 	/* Check the half transfer flag */
	 if (GET_BIT(DMAx[USE_DMA_2]->ISR,6)==1){
		if (DMA2_Fptr[1][1] != NULLPTR) {
			DMA2_Fptr[1][1]();
	    }
		/* Clears the THIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_2]->IFCR ,6);
	}	 	
	/* Check the Error transfer flag */
	 if (GET_BIT(DMAx[USE_DMA_2]->ISR,7)==1){
		if (DMA2_Fptr[1][2] != NULLPTR) {
			DMA2_Fptr[1][2]();
	    }
		/* Clears the EHIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_2]->IFCR ,7);
	}
}
void DMA2_Channel3_IRQHandler(){
	/* Check the Complete transfer flag */
	if (GET_BIT(DMAx[USE_DMA_2]->ISR,9)==1){
		if (DMA2_Fptr[2][0] != NULLPTR) {
			DMA2_Fptr[2][0]();
	    }
		/* Clears the TCIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_2]->IFCR ,9);
	}
	 	/* Check the half transfer flag */
	 if (GET_BIT(DMAx[USE_DMA_2]->ISR,10)==1){
		if (DMA2_Fptr[2][1] != NULLPTR) {
			DMA2_Fptr[2][1]();
	    }
		/* Clears the THIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_2]->IFCR ,10);
	}	 	
	/* Check the Error transfer flag */
	 if (GET_BIT(DMAx[USE_DMA_2]->ISR,11)==1){
		if (DMA2_Fptr[2][2] != NULLPTR) {
			DMA2_Fptr[2][2]();
	    }
		/* Clears the EHIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_2]->IFCR ,11);
	}

}
void DMA2_Channel4_IRQHandler(){
	/* Check the Complete transfer flag */
	if (GET_BIT(DMAx[USE_DMA_2]->ISR,13)==1){
		if (DMA2_Fptr[3][0] != NULLPTR) {
			DMA2_Fptr[3][0]();
	    }
		/* Clears the TCIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_2]->IFCR ,13);
	}
	 	/* Check the half transfer flag */
	 if (GET_BIT(DMAx[USE_DMA_2]->ISR,14)==1){
		if (DMA2_Fptr[3][1] != NULLPTR) {
			DMA2_Fptr[3][1]();
	    }
		/* Clears the THIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_2]->IFCR ,14);
	}	 	
	/* Check the Error transfer flag */
	 if (GET_BIT(DMAx[USE_DMA_2]->ISR,15)==1){
		if (DMA2_Fptr[3][2] != NULLPTR) {
			DMA2_Fptr[3][2]();
	    }
		/* Clears the EHIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_2]->IFCR ,15);
	}
}

void DMA2_Channel5_IRQHandler(){
	/* Check the Complete transfer flag */
	if (GET_BIT(DMAx[USE_DMA_2]->ISR,17)==1){
		if (DMA2_Fptr[4][0] != NULLPTR) {
			DMA2_Fptr[4][0]();
	    }
		/* Clears the TCIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_2]->IFCR ,17);
	}
	 	/* Check the half transfer flag */
	else if (GET_BIT(DMAx[USE_DMA_2]->ISR,18)==1){
		if (DMA2_Fptr[4][1] != NULLPTR) {
			DMA2_Fptr[4][1]();
	    }
		/* Clears the THIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_2]->IFCR ,18);
	}	 	
	/* Check the Error transfer flag */
	 if (GET_BIT(DMAx[USE_DMA_2]->ISR,19)==1){
		if (DMA2_Fptr[4][2] != NULLPTR) {
			DMA2_Fptr[4][2]();
	    }
		/* Clears the EHIF flag in the DMA_ISR register*/
		SET_BIT(DMAx[USE_DMA_2]->IFCR ,19);
	}
}

 

/*************** END OF FUNCTIONS *********************************************/
