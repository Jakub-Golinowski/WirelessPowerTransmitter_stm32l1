#include "JG_BinaryProtocolCommands.h"
#include <stdio.h>

/* Global Variables ------------------------------------------------------------------*/
volatile uint8_t g_CommandReceivedCounter;
volatile uint8_t g_CommandBufferFullFlag;
volatile uint8_t g_RepeatModeFlag;
volatile uint8_t g_ExtendedRepeatModeFlag;

volatile uint8_t aTxBuffer_GV[BINARY_PROTOCOL_RESPONSE_BUFFER_LENGTH];

volatile uint8_t command_buffer_tail_index_GV;
volatile uint8_t command_buffer_head_index_GV;
volatile uint8_t command_buffer_GV[COMMAND_BUFFER_SIZE];

volatile uint8_t g_FODThresholdNewValueBuffer[FOD_THRESHOLD_NEW_VALUE_BUFFER_SIZE];
volatile uint8_t g_FODThresholdNewValueBuffer_Index;
volatile uint8_t g_FODThresholdSingleByte = 0;
/* Function Definitions ------------------------------------------------------------------*/
int8_t JG_CommandBuffer_GetCommand(uint8_t * receivedData)
{
	if(command_buffer_head_index_GV == command_buffer_tail_index_GV)
		return -1; //Return error code when the buffer is empty

	command_buffer_tail_index_GV = (command_buffer_tail_index_GV+1) & COMMAND_BUFFER_MASK; //Increment tail index and & with mask, so it never exceeds the buffer size - 1

	*receivedData = command_buffer_GV[command_buffer_tail_index_GV];		//Insert byte from Data Register to circular buffer

	return 1;
}



void JG_ProcessCurrentCommand(uint8_t Command)
{
	switch(Command)
	{
		case JG_Command_IdentificationCommandCode :
		{
			HAL_UART_Transmit_DMA(&huart3,(uint8_t*)JG_Command_IdentificationCommandRespone,JG_Command_IdentificationCommandResponseLength);
			HAL_UART_Receive_IT(&huart3, (uint8_t*)&ReceivedCommandByte, 1);
			break;
		}

		case JG_Command_RepeatModeEnableCommandCode:
		{
			HAL_UART_Transmit_DMA(&huart3,(uint8_t*)JG_Command_RepeatModeEnableCommandResponseBeginning,JG_Command_RepeatModeEnableCommandResponseBeginningLength);
			g_ExtendedRepeatModeFlag = 0;
			g_RepeatModeFlag = 1;
			HAL_UART_Receive_IT(&huart3, (uint8_t*)&ReceivedCommandByte, 1);
			break;
		}

		case JG_Command_SingleDiagCommandCode:
		{
			//Wysy³aj¹c zapytanie o pojedyncz¹ ramkê diagnostyczn¹ automatycznie wychodzimy z RepeatMode. Typowe oczekiwanie u¿ytkownika.
			g_RepeatModeFlag = 0;
			g_ExtendedRepeatModeFlag = 0;
			size_t size = JG_StringParse_MATLABDiagnostics();
			HAL_UART_Transmit(&huart3,(uint8_t*)g_ParsedStringBuffer,size, 100);
			HAL_UART_Receive_IT(&huart3, (uint8_t*)&ReceivedCommandByte, 1);
			break;
		}
		case JG_Command_FODThresholdSetCommandCode:
		{
			//Wysy³aj¹c zapytanie o zmianê progu FOD automatycznie wychodzimy z RepeatMode. Typowe oczekiwanie u¿ytkownika.
			g_RepeatModeFlag = 0;
			g_ExtendedRepeatModeFlag = 0;
			//Wyzeruj index bufora nowej wartoœci i WejdŸ w tryb odbierania nowej wartoœci FOD
			g_FODThresholdNewValueBuffer_Index = 0;
			g_FODThresholdReadModeFlag = 1;
			HAL_UART_Transmit(&huart3,(uint8_t*)JG_Command_FODThresholdSetCommandResponse,JG_Command_FODThresholdSetCommandResponeLength, 100);
			//Odbierz przez UART pojedynczy bajt
			HAL_UART_Receive_IT(&huart3, (uint8_t*)&g_FODThresholdSingleByte, 1);

			break;

		}
		case JG_Command_SetUSBJ1AsPowerSourceCommandCode:
		{
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);
			HAL_UART_Transmit(&huart3,(uint8_t*)JG_Command_SetUSBJ1AsPowerSourceResponse,JG_Command_SetUSBJ1AsPowerSourceResponeLength, 100);


			HAL_UART_Receive_IT(&huart3, (uint8_t*)&ReceivedCommandByte, 1);
			break;
		}
		case JG_Command_SetDCJackJ2AsPowerSourceCommandCode:
		{
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET);
			HAL_UART_Transmit(&huart3,(uint8_t*)JG_Command_SetDCJackJ2AsPowerSourceResponse,JG_Command_SetDCJackJ2AsPowerSourceResponeLength, 100);

			HAL_UART_Receive_IT(&huart3, (uint8_t*)&ReceivedCommandByte, 1);
			break;
		}
		case JG_Command_ADCResultsQueryCommandCode:
		{
			JG_ParseAndSendADCMeasurementsToUART();

			HAL_UART_Receive_IT(&huart3, (uint8_t*)&ReceivedCommandByte, 1);
			break;

		}
		default :
			{
				HAL_UART_Transmit_DMA(&huart3,(uint8_t*)JG_Command_UnknownCommandRespone,JG_Command_UnknownCommandResponseLength);
				HAL_UART_Receive_IT(&huart3, (uint8_t*)&ReceivedCommandByte, 1);
			}
	}
}
