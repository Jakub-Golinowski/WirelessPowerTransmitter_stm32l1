#include "BQ500511_Parser.h"
#include <string.h>

volatile uint8_t g_DeviceIdBuffer[BQ500511A_DEVICE_ID_BUFFER_LENGTH];

volatile uint8_t g_ReportedReceivedPower_128thOfMaxPower;
volatile uint8_t g_RawReportedMaxPower;
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
volatile uint32_t g_ReceiverMaxPower_W;
volatile uint8_t g_PowerTransferControlType;
volatile uint8_t g_NumberOfAdditionalPackets;
volatile uint8_t g_WindowSize_ms;
volatile uint8_t g_WindowOffset_ms;
volatile uint8_t g_IdentificationBffer[BQ500511A_IDENTIFICATION_BUFFER_LENGTH];
volatile uint8_t g_MajorQiVersion;
volatile uint8_t g_MinorQiVersion;
volatile uint16_t g_ManufacturerCode;
volatile uint8_t g_ExtendedMode;
volatile uint32_t g_BasicDeviceIdentifier;
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

	memcpy((uint8_t*)&g_RawReportedMaxPower, (uint8_t*)(g_PLDMonitorRawBuffer + 2), 1);

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

	uint8_t FODPeak_RawTwoBytes[2];
	memcpy((uint8_t*)&FODPeak_RawTwoBytes, (uint8_t*)(g_PLDMonitorRawBuffer + 21), 2);
	g_FODPeak_V = ((uint16_t)FODPeak_RawTwoBytes[0] << 8) + (uint16_t)FODPeak_RawTwoBytes[1];

	uint8_t OutputFrequency_RawTwoBytes[2];
	memcpy((uint8_t*)OutputFrequency_RawTwoBytes, (uint8_t*)(g_PLDMonitorRawBuffer + 28), 2);
	JG_SubParse_TwoBytesTo10Q6((uint16_t*)&g_OutputFrequency_kHz_int, (uint8_t*)&g_OutputFrequency_kHz_decimal, OutputFrequency_RawTwoBytes);
}

void JG_Parse_PLDThreshold(){
	memcpy((uint16_t*)&g_PLD_Threshold, (uint16_t*)g_PLDThresholdRawBuffer, 2);
}

void JG_Parse_RxProp(){
	memcpy((uint8_t*)&g_RxPropBuffer,(uint8_t*)(g_RxPropRawBuffer + 1), BQ500511A_RX_PROP_BUFFER_LENGTH);
}

void JG_Parse_RxPropCount(){
	memcpy((uint16_t*)&g_RxPropCount, (uint8_t*)g_RxPropCountRawBuffer, 2);
}

void JG_Parse_RxStats(){

	memcpy((uint8_t*)&g_SignalStrengthByte, (uint8_t*)g_RxStatsRawBuffer + 1, 1);

	memcpy((uint8_t*)&g_EndPowerTransferByte, (uint8_t*)g_RxStatsRawBuffer + 2, 1);

	memcpy((uint8_t*)&g_ControlErrorByte, (uint8_t*)g_RxStatsRawBuffer + 3, 1);

	memcpy((uint8_t*)&g_ReceivedPowerByte, (uint8_t*)g_RxStatsRawBuffer + 4, 1);

	memcpy((uint8_t*)&g_ChargeStatusByte, (uint8_t*)g_RxStatsRawBuffer + 5, 1);

	memcpy((uint8_t*)&g_HoldoffByte, (uint8_t*)g_RxStatsRawBuffer + 6, 1);

	memcpy((uint8_t*)&g_ConfigurationBuffer, (uint8_t*)g_RxStatsRawBuffer + 7, 5);
	JG_SubParse_Configuration();

	memcpy((uint8_t*)&g_IdentificationBffer, (uint8_t*)g_RxStatsRawBuffer + 12, 7);
	JG_SubParse_Identification();

	memcpy((uint8_t*)&g_ExtendedIdentificationBuffer, (uint8_t*)g_RxStatsRawBuffer + 19, 4);

}

void JG_Parse_TxStats(){

	uint8_t VoltageIn_RawTwoBytes[2];
	memcpy((uint8_t*)&VoltageIn_RawTwoBytes, (uint8_t*)(g_TxStatsRawBuffer + 1), 2);
	JG_SubParse_TwoBytesTo6Q10((uint8_t*)&g_VoltageIn_V_int, (uint16_t*)&g_VoltageIn_V_decimal, VoltageIn_RawTwoBytes);

	uint8_t CurrentOut_RawTwoBytes[2];
	memcpy((uint8_t*)&CurrentOut_RawTwoBytes, (uint8_t*)(g_TxStatsRawBuffer + 3), 2);
	JG_SubParse_TwoBytesTo13Q3((uint16_t*)&g_CurrentOut_mA_int, (uint8_t*)&g_CurrentOut_mA_decimal, CurrentOut_RawTwoBytes);

	uint8_t InternalTemperature_RawTwoBytes[2];
	memcpy((uint8_t*)&InternalTemperature_RawTwoBytes, (uint8_t*)(g_TxStatsRawBuffer + 7), 2);
	JG_SubParse_TwoBytesTo9Q7((uint16_t*)&g_InternalTemperature_degC_int, (uint8_t*)&g_InternalTemperature_degC_decimal, InternalTemperature_RawTwoBytes);


	uint8_t GoodMessageCounter_RawTwoBytes[2];
	memcpy((uint8_t*)&GoodMessageCounter_RawTwoBytes, (uint8_t*)(g_TxStatsRawBuffer + 11), 2);
	g_GoodMessageCounter = ((uint16_t)GoodMessageCounter_RawTwoBytes[0] << 8) + (uint16_t)GoodMessageCounter_RawTwoBytes[1];

	uint8_t BadMessageCounter_RawTwoBytes[2];
	memcpy((uint8_t*)&BadMessageCounter_RawTwoBytes, (uint8_t*)(g_TxStatsRawBuffer + 15), 2);
	g_BadMessageCounter = ((uint16_t)BadMessageCounter_RawTwoBytes[0] << 8) + (uint16_t)BadMessageCounter_RawTwoBytes[1];

	uint8_t Frequency_RawTwoBytes[2];
	memcpy((uint8_t*)&Frequency_RawTwoBytes, (uint8_t*)(g_TxStatsRawBuffer + 17), 2);
	JG_SubParse_TwoBytesTo10Q6((uint16_t*)&g_Frequency_kHz_int, (uint8_t*)&g_Frequency_kHz_decimal, Frequency_RawTwoBytes);

	uint8_t DutyCycle_RawTwoBytes[2];
	memcpy((uint8_t*)&DutyCycle_RawTwoBytes, (uint8_t*)(g_TxStatsRawBuffer + 19), 2);
	JG_SubParse_TwoBytesTo1Q15((uint8_t*)&g_DutyCycle_percent_int, (uint16_t*)&g_DutyCycle_percent_decimal, DutyCycle_RawTwoBytes);

	memcpy((uint8_t*)&g_LedModeByte, (uint8_t*)(g_TxStatsRawBuffer + 21),1);

	memcpy((uint8_t*)&g_LedStatusByte, (uint8_t*)(g_TxStatsRawBuffer + 22),1);

	uint8_t FODThreshold_RawFourBytes[4];
	memcpy((uint8_t*)&FODThreshold_RawFourBytes, (uint8_t*)(g_TxStatsRawBuffer + 23), 4);
	JG_SubParse_FourBytesTo19Q13((uint32_t*)&g_FODThreshold_mW_int, (uint16_t*)&g_FODThreshold_mW_decimal, FODThreshold_RawFourBytes);

	uint8_t ParasiticLossDetected_RawFourBytes[4];
	memcpy((uint8_t*)&ParasiticLossDetected_RawFourBytes, (uint8_t*)(g_TxStatsRawBuffer + 27), 4);
	JG_SubParse_FourBytesTo19Q13((uint32_t*)&g_ParasiticLossDetected_mW_int, (uint16_t*)&g_ParasiticLossDetected_mW_decimal, ParasiticLossDetected_RawFourBytes);

	memcpy((uint8_t*)&g_CS100Byte, (uint8_t*)(g_TxStatsRawBuffer + 31),1);
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

void JG_SubParse_TwoBytesTo9Q7(uint16_t* OutIntegerPart9Bits, uint8_t* OutDecimalPart7Bits, uint8_t* RawTwoBytesArrayMSBFirst){
	uint8_t Mask_1MSbValid = 0x80;
	uint8_t Mask_7LSbValid = 0x7F;

	uint16_t TmpOutIntegerPart9Bits = 0;
	uint8_t TmpOutDecimalPart7Bits = 0;
	uint8_t TmpRawTwoBytesMSBFirst[2] = {0};

	memcpy((uint8_t*)&TmpRawTwoBytesMSBFirst, RawTwoBytesArrayMSBFirst, 2);

	TmpOutIntegerPart9Bits = (TmpRawTwoBytesMSBFirst[0] << 1) + ((TmpRawTwoBytesMSBFirst[1] & Mask_1MSbValid) >> 7);
	TmpOutDecimalPart7Bits = (TmpRawTwoBytesMSBFirst[1] & Mask_7LSbValid);

	*OutIntegerPart9Bits = TmpOutIntegerPart9Bits;
	*OutDecimalPart7Bits = TmpOutDecimalPart7Bits;

}

void JG_SubParse_TwoBytesTo1Q15(uint8_t* OutIntegerPart1Bit, uint16_t* OutDecimalPart15Bits, uint8_t* RawTwoBytesArrayMSBFirst){
	uint8_t Mask_1MSbValid = 0x80;
	uint8_t Mask_7LSbValid = 0x7F;

	uint8_t TmpOutIntegerPart1Bit = 0;
	uint16_t TmpOutDecimalPart15Bits = 0;
	uint8_t TmpRawTwoBytesMSBFirst[2] = {0};

	memcpy((uint8_t*)&TmpRawTwoBytesMSBFirst, RawTwoBytesArrayMSBFirst, 2);

	TmpOutIntegerPart1Bit = ((TmpRawTwoBytesMSBFirst[0] & Mask_1MSbValid) >> 7);
	TmpOutDecimalPart15Bits = ((TmpRawTwoBytesMSBFirst[0] & Mask_7LSbValid) << 8) + TmpRawTwoBytesMSBFirst[1];

	*OutIntegerPart1Bit = TmpOutIntegerPart1Bit;
	*OutDecimalPart15Bits = TmpOutDecimalPart15Bits;

}

void JG_SubParse_Configuration(){
	uint8_t Mask_5LSbValid = 0x1F;
	uint8_t Mask_3MSbValid = 0xE0;
	uint8_t MaxPowerValue = (g_ConfigurationBuffer[0] & Mask_5LSbValid);
	uint8_t PowerClass = (g_ConfigurationBuffer[0] & Mask_3MSbValid);

	uint32_t MaxPower_W =  MaxPowerValue / 2;
	while(PowerClass){
		MaxPower_W = MaxPower_W * 10;
		--PowerClass;
	}
	g_ReceiverMaxPower_W = MaxPower_W;

	g_PowerTransferControlType = ((0x1 << 8) & g_ConfigurationBuffer[2]) >> 8;
	g_NumberOfAdditionalPackets = (0x7) & g_ConfigurationBuffer[2];

	uint8_t Mask_5MSbValid = 0xF8;
	uint8_t Mask_3LSbValid = 0x07;
	g_WindowSize_ms = ((Mask_5MSbValid & g_ConfigurationBuffer[3]) >> 3) * 4;
	g_WindowOffset_ms = (Mask_3LSbValid & g_ConfigurationBuffer[3]) * 4;
}

void JG_SubParse_Identification(){
	uint8_t Mask_4MSbValid = 0xF0;
	uint8_t Mask_4LSbValid = 0x0F;
	g_MajorQiVersion = (Mask_4MSbValid & g_IdentificationBffer[0]) >> 4;
	g_MinorQiVersion = (Mask_4LSbValid & g_IdentificationBffer[0]);

	g_ManufacturerCode = (g_IdentificationBffer[1] << 8) + g_IdentificationBffer[2];
	g_ExtendedMode = ((0x01 << 7) & g_IdentificationBffer[3]) >> 7;

	uint8_t Mask_7LSbValid = 0x7F;
	g_BasicDeviceIdentifier = ((Mask_7LSbValid & g_IdentificationBffer[3]) << 24) + (g_IdentificationBffer[4] << 16) + (g_IdentificationBffer[5] << 8) + (g_IdentificationBffer[6]);

}
