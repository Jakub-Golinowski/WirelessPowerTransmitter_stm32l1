#ifndef BQ500511_STRINGPARSER_H_
#define BQ500511_STRINGPARSER_H_

#include "mini-printf.h"
#include "stm32l1xx_hal.h"

#include "BQ500511_Parser.h"

#define PARSED_STRING_BUFFER_LENGTH 100

extern volatile uint8_t g_ParsedStringBuffer[PARSED_STRING_BUFFER_LENGTH];

size_t JG_StringParse_DeviceId();
size_t JG_StringParse_PLDMonitor();
size_t JG_StringParse_RxStats();
size_t JG_StringParse_TxStats();
size_t JG_SubStringParse_19Q13(uint8_t* OutStringBuffer, uint32_t IntegerPart19Bits, uint16_t DecimalPart13Bits);
size_t JG_SubStringParse_6Q10(uint8_t* OutStringBuffer, uint8_t IntegerPart6Bits, uint16_t DecimalPart10Bits);
size_t JG_SubStringParse_13Q3(uint8_t* OutStringBuffer, uint16_t IntegerPart13Bits, uint8_t DecimalPart3Bits);
size_t JG_SubStringParse_10Q6(uint8_t* OutStringBuffer, uint16_t IntegerPart10Bits, uint8_t DecimalPart6Bits);
size_t JG_SubStringParse_9Q7(uint8_t* OutStringBuffer, uint16_t IntegerPart9Bits, uint8_t DecimalPart7Bits);
size_t JG_SubStringParse_1Q15(uint8_t* OutStringBuffer, uint8_t IntegerPart1Bit, uint16_t DecimalPart15Bits);
#endif /* BQ500511_STRINGPARSER_H_ */
