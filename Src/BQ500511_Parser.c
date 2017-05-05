#include "BQ500511_Parser.h"
#include <string.h>

volatile uint8_t g_DeviceIdBuffer[BQ500511A_DEVICE_ID_BUFFER_LENGTH];

volatile uint8_t g_ReportedReceivedPower_128thOfMaxPower;
volatile uint8_t g_RawReportedMaxPower_mW;
volatile uint32_t g_ThresholdSetFromResistor_mW_int;
volatile uint16_t g_ThresholdSetFromResistor_mW_decimal;
volatile uint32_t g_CalculatedParasiticLoss_mW_int;
volatile uint32_t g_CalculatedParasiticLoss_mW_decimal;
volatile uint8_t g_DCInputVoltage_V_int;
volatile uint16_t g_DCInputVoltage_V_decimal;
volatile uint16_t g_DCInputCurrent_mA_int;
volatile uint8_t g_DCInputCurrent_mA_decimal;
volatile uint32_t g_CalculatedInputPower_mW_int;
volatile uint16_t g_CalculatedInputPower_mW_decimal;
volatile uint16_t g_FODPeak_V;
volatile uint16_t g_OutputFrequency_kHz_int;
volatile uint16_t g_OutputFrequency_kHz_decimal;

volatile uint16_t g_PLD_Threshold;

volatile uint8_t g_RxPropBuffer[BQ500511A_RX_PROP_BUFFER_LENGTH];

volatile uint16_t g_RxPropCount;

volatile uint8_t g_SignalStrengthByte;
volatile uint8_t g_EndPowerTransferByte;
volatile uint8_t g_ControlErrorByte;
volatile uint8_t g_ReceivedPowerByte;
volatile uint8_t g_ChargeStatusByte;
volatile uint8_t g_HoldoffByte;
volatile uint8_t g_ConfigurationBuffer[BQ500511A_CONFIGURATION_BUFFER_LENGTH];
volatile uint8_t g_IdentificationBffer[BQ500511A_IDENTIFICATION_BUFFER_LENGTH];
volatile uint8_t g_ExtendedIdentificationBuffer[BQ500511A_EXTENDED_IDENTIFICATION_BUFFER_LENGTH];

volatile uint8_t g_VoltageIn_V_int;
volatile uint16_t g_VoltageIn_V_decimal;
volatile uint16_t g_CurrentOut_mA_int;
volatile uint16_t g_CurrentOut_mA_decimal;
volatile uint16_t g_InternalTemperature_degC_int;
volatile uint8_t g_InternalTemperature_degC_decimal;
volatile uint16_t g_GoodMessageCounter;
volatile uint16_t g_BadMessageCounter;
volatile uint16_t g_Frequency_kHz_int;
volatile uint16_t g_Frequency_kHz_decimal;
volatile uint8_t g_DutyCycle_percent_int;
volatile uint16_t g_DutyCycle_percent_decimal;
volatile uint8_t g_LedModeByte;
volatile uint16_t g_LedStatusByte;
volatile uint32_t g_FODThreshold_mW_int;
volatile uint16_t g_FODThreshold_mW_decimal;
volatile uint32_t g_ParasiticLossDetected_mW_int;
volatile uint16_t g_ParasiticLossDetected_mW_decimal;
volatile uint8_t g_CS100Byte;

void JG_Parse_DeviceBuffer(){
	memcpy((uint8_t*)g_DeviceIdBuffer, (uint8_t*)(g_DeviceIDRawBuffer+1),BQ500511A_DEVICE_ID_BUFFER_LENGTH);
}

void JG_Parse_PLDMonitor(){
	memcpy((uint8_t*)&g_ReportedReceivedPower_128thOfMaxPower, (uint8_t*)(g_PLDMonitorRawBuffer + 1), 1);

	memcpy((uint8_t*)&g_RawReportedMaxPower_mW, (uint8_t*)(g_PLDMonitorRawBuffer + 2), 1);

	uint8_t ThresholdSetFromResistor_RawFourBytes[4];
	memcpy((uint8_t*)&ThresholdSetFromResistor_RawFourBytes, (uint8_t*)(g_PLDMonitorRawBuffer + 3), 4);
	JG_SubParse_FourBytesTo19Q13((uint32_t*)&g_ThresholdSetFromResistor_mW_int, (uint16_t*)&g_ThresholdSetFromResistor_mW_decimal,ThresholdSetFromResistor_RawFourBytes);

	uint8_t CalculatedParasiticLoss_RawFourBytes[4];
	memcpy((uint8_t*)&CalculatedParasiticLoss_RawFourBytes, (uint8_t*)(g_PLDMonitorRawBuffer + 7), 4);
	JG_SubParse_FourBytesTo19Q13((uint32_t*)&g_CalculatedParasiticLoss_mW_int, (uint16_t*)&g_CalculatedParasiticLoss_mW_decimal,CalculatedParasiticLoss_RawFourBytes);

	uint8_t DCInputVoltage_RawTwoBytes[2];
	memcpy((uint8_t*)&DCInputVoltage_RawTwoBytes, (uint8_t*)(g_PLDMonitorRawBuffer + 11), 2);
	JG_SubParse_TwoBytesTo6Q10((uint8_t*)&g_DCInputVoltage_V_int, (uint16_t*)&g_DCInputVoltage_V_decimal, DCInputVoltage_RawTwoBytes);

	uint8_t DCInputCurrent_RawFourBytes[4];
	memcpy((uint8_t*)&DCInputCurrent_RawFourBytes, (uint8_t*)(g_PLDMonitorRawBuffer + 13), 2);
	JG_SubParse_TwoBytesTo13Q3((uint16_t*)&g_DCInputCurrent_mA_int, (uint8_t*)&g_DCInputCurrent_mA_decimal, DCInputCurrent_RawFourBytes);

	uint8_t CalculatedInputPower_RawFourBytes[4];
	memcpy((uint8_t*)&CalculatedInputPower_RawFourBytes, (uint8_t*)(g_PLDMonitorRawBuffer + 15), 4);
	JG_SubParse_FourBytesTo19Q13((uint32_t*)&g_CalculatedInputPower_mW_int, (uint16_t*)&g_CalculatedInputPower_mW_decimal, CalculatedInputPower_RawFourBytes);

	memcpy((uint16_t*)&g_FODPeak_V, (uint8_t*)(g_PLDMonitorRawBuffer + 21), 2);

	uint8_t OutputFrequency_RawTwoBytes[2];
	memcpy((uint8_t*)OutputFrequency_RawTwoBytes, (uint8_t*)(g_PLDMonitorRawBuffer + 28), 2);
	JG_SubParse_TwoBytesTo10Q6((uint16_t*)&g_OutputFrequency_kHz_int, (uint8_t*)&g_OutputFrequency_kHz_decimal, OutputFrequency_RawTwoBytes);
}



void JG_SubParse_FourBytesTo19Q13(uint32_t* OutIntegerPart19Bits, uint16_t* OutDecimalPart13Bits, uint8_t* RawFourBytesArrayMSBFirst){

	uint8_t Mask_3MSbValid = 0xE0;
	uint8_t Mask_5LSbValid = 0x1F;

	uint32_t TmpOutIntegerPart19Bits = 0;
	uint16_t TmpOutDecimalPart13Bits = 0;
	uint8_t Tmp_RawFourBytesMSBFirst[4] = {0};

	memcpy((uint8_t*)&Tmp_RawFourBytesMSBFirst, RawFourBytesArrayMSBFirst, 4);

	TmpOutIntegerPart19Bits = ((uint32_t)Tmp_RawFourBytesMSBFirst[0] << (8 + 3)) + ((uint32_t)Tmp_RawFourBytesMSBFirst[1] << + 3)	+ (((uint32_t)Tmp_RawFourBytesMSBFirst[2] & Mask_3MSbValid) >> 5);
	TmpOutDecimalPart13Bits = (((uint16_t)Tmp_RawFourBytesMSBFirst[2] & Mask_5LSbValid) << 8) + (uint16_t)Tmp_RawFourBytesMSBFirst[3];

	*OutIntegerPart19Bits = TmpOutIntegerPart19Bits;
	*OutDecimalPart13Bits = TmpOutDecimalPart13Bits;
}

void JG_SubParse_TwoBytesTo6Q10(uint8_t* OutIntegerPart6Bits, uint16_t* OutDecimalPart10Bits, uint8_t* RawTwoBytesArrayMSBFirst){

	uint8_t Mask_6MSbValid = 0xFC;
	uint8_t Mask_2LSbValid = 0x3;

	uint8_t TmpOutIntegerPart6Bits = 0;
	uint16_t TmpOutDecimalPart10Bits = 0;
	uint8_t TmpRawTwoBytesMSBFirst[2] = {0};

	memcpy((uint8_t*)&TmpRawTwoBytesMSBFirst, RawTwoBytesArrayMSBFirst, 2);

	TmpOutIntegerPart6Bits = (TmpRawTwoBytesMSBFirst[0] & Mask_6MSbValid) >> 2;
	TmpOutDecimalPart10Bits = ((TmpRawTwoBytesMSBFirst[0] & Mask_2LSbValid) << 8) + TmpRawTwoBytesMSBFirst[1];

	*OutIntegerPart6Bits = TmpOutIntegerPart6Bits;
	*OutDecimalPart10Bits = TmpOutDecimalPart10Bits;
}

void JG_SubParse_TwoBytesTo13Q3(uint16_t* OutIntegerPart13Bits, uint8_t* OutDecimalPart3Bits, uint8_t* RawTwoBytesArrayMSBFirst){

	uint8_t Mask_5MSbValid = 0xF8;
	uint8_t Mask_3LSbValid = 0x07;

	uint16_t TmpOutIntegerPart13Bits = 0;
	uint8_t TmpOutDecimalPart3Bits = 0;
	uint8_t TmpRawTwoBytesMSBFirst[2] = {0};

	memcpy((uint8_t*)&TmpRawTwoBytesMSBFirst, RawTwoBytesArrayMSBFirst, 2);

	TmpOutIntegerPart13Bits = (TmpRawTwoBytesMSBFirst[0] << 5) + ((Mask_5MSbValid & TmpRawTwoBytesMSBFirst[1]) >> 3);
	TmpOutDecimalPart3Bits = (TmpRawTwoBytesMSBFirst[1] & Mask_3LSbValid);

	*OutIntegerPart13Bits = TmpOutIntegerPart13Bits;
	*OutDecimalPart3Bits = TmpOutDecimalPart3Bits;
}

void JG_SubParse_TwoBytesTo10Q6(uint16_t* OutIntegerPart10Bits, uint8_t* OutDecimalPart6Bits, uint8_t* RawTwoBytesArrayMSBFIrst){

	uint8_t Mask_2MSbValid = 0xC0;
	uint8_t Mask_6LSbValid = 0x3F;

	uint16_t TmpOutIntegerPart10Bits = 0;
	uint8_t TmpOutDecimalPart6Bits = 0;
	uint8_t TmpRawTwoBytesMSBFirst[2] = {0};

	memcpy((uint8_t*)&TmpRawTwoBytesMSBFirst, RawTwoBytesArrayMSBFIrst, 2);

	TmpOutIntegerPart10Bits = (TmpRawTwoBytesMSBFirst[0] << 2) + ((TmpRawTwoBytesMSBFirst[1] & Mask_2MSbValid) >> 6);
	TmpOutDecimalPart6Bits = (TmpRawTwoBytesMSBFirst[1] & Mask_6LSbValid);

	*OutIntegerPart10Bits = TmpOutIntegerPart10Bits;
	*OutDecimalPart6Bits = TmpOutDecimalPart6Bits;

}

//Deprecated
void JG_SubParse_ThresholdSetFromResistor(){

	uint8_t Mask_3MSbValid = 0xE0;
	uint8_t Mask_5LSbValid = 0x1F;

	uint32_t ThresholdSetFromResistor_Integer19Bits = 0;
	uint16_t ThresholdSetFromResistor_Decimal13Bits = 0;
	uint8_t ThresholdSetFromResistor_RawBytes[4] = {0};

	memcpy((uint8_t*)&ThresholdSetFromResistor_RawBytes, (uint8_t*)(g_PLDMonitorRawBuffer + 3), 4);

	ThresholdSetFromResistor_Integer19Bits = ((uint32_t)ThresholdSetFromResistor_RawBytes[0] << (8 + 3)) + ((uint32_t)ThresholdSetFromResistor_RawBytes[1] << + 3)	+ (((uint32_t)ThresholdSetFromResistor_RawBytes[2] & Mask_3MSbValid) >> 5);
	ThresholdSetFromResistor_Decimal13Bits = (((uint16_t)ThresholdSetFromResistor_RawBytes[2] & Mask_5LSbValid) << 8) + (uint16_t)ThresholdSetFromResistor_RawBytes[3];

	g_ThresholdSetFromResistor_mW_int = ThresholdSetFromResistor_Integer19Bits;
	g_ThresholdSetFromResistor_mW_decimal = ThresholdSetFromResistor_Decimal13Bits;
}
