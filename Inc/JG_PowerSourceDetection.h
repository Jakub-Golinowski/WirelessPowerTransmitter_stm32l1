#ifndef JG_POWERSOURCEDETECTION_H_
#define JG_POWERSOURCEDETECTION_H_

#include "stm32l1xx_hal.h"

extern volatile uint16_t g_ADCMeasurements[2];
extern UART_HandleTypeDef huart3;
void JG_ParseAndSendADCMeasurementsToUART();


#endif /* JG_POWERSOURCEDETECTION_H_ */
