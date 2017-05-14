#include "Tests.h"

void JG_TEST_SubStringParse_19Q13(){

	//Test sprawdza poprawnoœc konwersji liczby 13 bitowej na dziesietna wartosc liczby po przecinku.
	//Test zosta³ przeprowadzony z powodzeniem.
	for(int i = 1; i <= 0x1FFF; i=i+10)
	{
	uint8_t TestStringBuffer[20] = {0};

	uint32_t IntegerPart19Bits = i;
	uint16_t DecimalPart13Bits = i;

	size_t  size = JG_SubStringParse_19Q13(TestStringBuffer, IntegerPart19Bits, DecimalPart13Bits);

	HAL_UART_Transmit(&huart3, TestStringBuffer, size, 100);
	HAL_UART_Transmit(&huart3, (uint8_t*)"\r\n", 2, 100);

	}

}

void JG_TEST_SubStringParse_6Q10(){

	//Test sprawdza poprawnoœc konwersji liczby 10 bitowej na dziesietna wartosc liczby po przecinku.
	//Test zosta³ przeprowadzony z powodzeniem.
	for(int i = 1; i <= 0x3FF; i=i+10)
	{
	uint8_t TestStringBuffer[20] = {0};

	uint8_t IntegerPart6Bits = 5;
	uint16_t DecimalPart10Bits = i;

	size_t  size = snprintf((char*)&TestStringBuffer, 20, "i = %d | ", (uint16_t)DecimalPart10Bits);
	HAL_UART_Transmit(&huart3, TestStringBuffer, size, 100);
	size = JG_SubStringParse_6Q10(TestStringBuffer, IntegerPart6Bits, DecimalPart10Bits);
	HAL_UART_Transmit(&huart3, TestStringBuffer, size, 100);
	HAL_UART_Transmit(&huart3, (uint8_t*)"\r\n", 2, 100);

	}

}

void JG_TEST_SubStringParse_13Q3(){

	//Test sprawdza poprawnoœc konwersji liczby 3 bitowej na dziesietna wartosc liczby po przecinku.
	for(int i = 1; i <= 0x7; i=i+1)
	{
	uint8_t TestStringBuffer[20] = {0};

	uint8_t IntegerPart13Bits = 5;
	uint16_t DecimalPart3Bits = i;

	size_t  size = snprintf((char*)&TestStringBuffer, 20, "i = %d | ", (uint16_t)DecimalPart3Bits);
	HAL_UART_Transmit(&huart3, TestStringBuffer, size, 100);
	size = JG_SubStringParse_13Q3(TestStringBuffer, IntegerPart13Bits, DecimalPart3Bits);
	HAL_UART_Transmit(&huart3, TestStringBuffer, size, 100);
	HAL_UART_Transmit(&huart3, (uint8_t*)"\r\n", 2, 100);

	}
}

void JG_TEST_SubStringParse_10Q6(){

	//Test sprawdza poprawnoœc konwersji liczby 6 bitowej na dziesietna wartosc liczby po przecinku.
	for(int i = 1; i <= 0x3F; i=i+1)
	{
	uint8_t TestStringBuffer[20] = {0};

	uint8_t IntegerPart10Bits = 5;
	uint16_t DecimalPart6Bits = i;

	size_t  size = snprintf((char*)&TestStringBuffer, 20, "i = %d | ", (uint16_t)DecimalPart6Bits);
	HAL_UART_Transmit(&huart3, TestStringBuffer, size, 100);
	size = JG_SubStringParse_10Q6(TestStringBuffer, IntegerPart10Bits, DecimalPart6Bits);
	HAL_UART_Transmit(&huart3, TestStringBuffer, size, 100);
	HAL_UART_Transmit(&huart3, (uint8_t*)"\r\n", 2, 100);

	}

}

void JG_TEST_SubStringParse_9Q7(){

	//Test sprawdza poprawnoœc konwersji liczby 7 bitowej na dziesietna wartosc liczby po przecinku.
	for(int i = 1; i <= 0x7F; i=i+1)
	{
	uint8_t TestStringBuffer[20] = {0};

	uint8_t IntegerPar9Bits = 5;
	uint16_t DecimalPart7Bits = i;

	size_t  size = snprintf((char*)&TestStringBuffer, 20, "i = %d | ", (uint16_t)DecimalPart7Bits);
	HAL_UART_Transmit(&huart3, TestStringBuffer, size, 100);
	size = JG_SubStringParse_9Q7(TestStringBuffer, IntegerPar9Bits, DecimalPart7Bits);
	HAL_UART_Transmit(&huart3, TestStringBuffer, size, 100);
	HAL_UART_Transmit(&huart3, (uint8_t*)"\r\n", 2, 100);

	}

}

void JG_TEST_SubStringParse_1Q15(){

	//Test sprawdza poprawnoœc konwersji liczby 15 bitowej na dziesietna wartosc liczby po przecinku.
	for(int i = 1; i <= 0x7FFF; i=i+10)
	{
	uint8_t TestStringBuffer[20] = {0};

	uint8_t IntegerPar1Bit = 5;
	uint16_t DecimalPart15Bits = i;

	size_t  size = snprintf((char*)&TestStringBuffer, 20, "i = %d | ", (uint16_t)DecimalPart15Bits);
	HAL_UART_Transmit(&huart3, TestStringBuffer, size, 100);
	size = JG_SubStringParse_1Q15(TestStringBuffer, IntegerPar1Bit, DecimalPart15Bits);
	HAL_UART_Transmit(&huart3, TestStringBuffer, size, 100);
	HAL_UART_Transmit(&huart3, (uint8_t*)"\r\n", 2, 100);

	}

}


