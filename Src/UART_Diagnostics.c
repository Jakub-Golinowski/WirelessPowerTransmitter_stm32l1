#include "UART_Diagnostics.h"

void JG_UART_TransmitDMA_ParsedString(size_t NumberOfBytesToSend){
	assert_param(NumberOfBytesToSend < PARSED_STRING_BUFFER_LENGTH);
	HAL_UART_Transmit_DMA(&huart3, (uint8_t*)g_ParsedStringBuffer, NumberOfBytesToSend);
}

void JG_UART_Transmit_ParsedString(size_t NumberOfBytesToSend){
	assert_param(NumberOfBytesToSend < PARSED_STRING_BUFFER_LENGTH);
	HAL_UART_Transmit(&huart3, (uint8_t*)g_ParsedStringBuffer, NumberOfBytesToSend, 100);
}
