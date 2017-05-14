#ifndef UART_DIAGNOSTICS_H_
#define UART_DIAGNOSTICS_H_

#include "BQ500511_Parser.h"
#include "BQ500511_StringParser.h"
#include "stm32l1xx_hal.h"

extern UART_HandleTypeDef huart3;

void JG_UART_TransmitDMA_ParsedString(size_t NumberOfBytesToSend);
void JG_UART_Transmit_ParsedString(size_t NumberOfBytesToSend);

#endif /* UART_DIAGNOSTICS_H_ */
