/**
 * ***************************************************************
 *  @file      DMA_interface.h			
 *  @author    Eslam Shahin (eslamshahin552000@gmail.com)                          
 *  @version   v2.0                                            
 *  @date      17/09/2020	                                   
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
 
#ifndef DMA_INTERFACE_H_
#define DMA_INTERFACE_H_

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
	USE_DMA_1,
	USE_DMA_2
	
}eDMA_Number_t;
typedef enum 
{
	DMA_Channel1,DMA_Channel2,DMA_Channel3,DMA_Channel4,DMA_Channel5,DMA_Channel6,DMA_Channel7
}eDMA_Channel_t;

typedef enum {
	DMA_LOW,
	DMA_MEDIUM,
	DMA_HIGH,
	DMA_VERY_HIGH,
	
}eChannelPriority_t;

typedef enum {
	DMA_DISABLE ,
	DMA_ENABLE
	
}eModeStatus_t;

typedef enum {
	DMA_1byte,
	DMA_HalfWord,
	DMA_Word,
	
}eDataSize_t;

typedef enum {
	ReadFromPeripheral,
	ReadFromMemory,
	
}eDMA_DataDirection_t;

typedef enum {
	 TransferCompleteInterrupt,
	 HalfTransferInterrupt ,
	 TransferErrorInterrupt,
}eDMA_InterruptSource_t;

typedef struct
{	
	eDMA_Number_t 		   DMA_Number ;
	eDMA_Channel_t    	   DMA_Channel;
	eModeStatus_t      	   M2M_Mode;
	eDataSize_t        	   MemorySize;
	eDataSize_t            PeripheralSize;
	eModeStatus_t          MemoryIncrement;
	eModeStatus_t          PeripheralIncrement;
	eModeStatus_t          CircularMode;
	eChannelPriority_t     ChannelPriority;
	eDMA_DataDirection_t   DataDirection;
	eModeStatus_t          TransferErrorInterrupt;
	eModeStatus_t	       HalfTransferInterrupt ;
	eModeStatus_t          TransferCompleteInterrupt;
	
}sDMA_Config_t;

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif
/*Steps to use DMA
 * 1- Call DMA_voidInit( DMA_1); for init the module and its clock
 * 2- Create the configration struct to config the channel
 * 3- Call DMA_voidInitChannel(); and send struct adress
 * 4- Enable DMA interrupt from the NVIC
 * 5- Call  DMA_voidStartTransfer() to start transfere your data
 * EX:
	DMA_voidInit();
	sDMA_Config_t DMA_Config;
	DMA_Config.DMA_Number = DMA_1;
	DMA_Config.ChannelPriority = DMA_VERY_HIGH;
	DMA_Config.DMA_Channel = DMA_Channel1;
	DMA_Config.DataDirection = ReadFromMemory;
	DMA_Config.M2M_Mode = DMA_ENABLE;
	DMA_Config.MemoryIncrement = DMA_ENABLE;
	DMA_Config.MemorySize = DMA_Word;
	DMA_Config.PeripheralIncrement = DMA_ENABLE;
	DMA_Config.PeripheralSize = DMA_Word;
	DMA_Config.TransferCompleteInterrupt = DMA_ENABLE;
	DMA_Config.HalfTransferInterrupt = DMA_ENABLE;

	DMA_voidInitChannel(&DMA_Config);
	NVIC_voidEnableInterrupt(DMA1_Channel1);
	DMA_voidStartTransfer(&DMA_Config, ARR1, ARR2, 1000);
 */

void DMA_voidInit(eDMA_Number_t DMA_Number);
void DMA_voidInitChannel(sDMA_Config_t * DMA_Config);
void DMA_voidStartTransfer(sDMA_Config_t * DMA_Config,u32 Pu32SourceAdrr , u32  Pu32DestinationAdrr , u16 NumberOfBlocks);
void DMA_voidSetCallBack(eDMA_Number_t DMA_Number ,eDMA_Channel_t DMA_Channel,eDMA_InterruptSource_t DMA_InterruptSource , void (*LocalFptr)(void) );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*File_H_*/

/*** End of File **************************************************************/
