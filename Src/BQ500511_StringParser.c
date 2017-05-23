#include "BQ500511_StringParser.h"

volatile uint8_t g_ParsedStringBuffer[PARSED_STRING_BUFFER_LENGTH];

size_t JG_StringParse_DeviceId(){

	return snprintf((char*)g_ParsedStringBuffer, PARSED_STRING_BUFFER_LENGTH, "%s\r\n", (char*)g_DeviceIdBuffer);

}


size_t JG_StringParse_PLDMonitor(){

	//ReportedReceivedPower
	uint32_t ReportedMaxPower_mW = (g_RawReportedMaxPower * 500);
	uint32_t ReportedPowerQuant_mW = ReportedMaxPower_mW / 128;
	uint16_t ReportedReceivedPower_mW = ReportedPowerQuant_mW * g_ReportedReceivedPower_128thOfMaxPower;
	char ReportedReceivedPower_mW_String[10] = {0};
	snprintf((char*)&ReportedReceivedPower_mW_String, 10, "%d", ReportedReceivedPower_mW);

	//ReportedMaxPower
	char ReportedMaxPowerString[10] = {0};
	snprintf((char*)&ReportedMaxPowerString, 10, "%d", ((uint16_t)g_RawReportedMaxPower * 500));

	//ThresholdSetFromResistor
	uint8_t ThresholdSetFromResistorString[15] = {0};
	JG_SubStringParse_19Q13(ThresholdSetFromResistorString, g_ThresholdSetFromResistor_mW_int, g_ThresholdSetFromResistor_mW_decimal);

	//CalculatedParasiticLoss
	uint8_t CalculatedParasiticLossString[15] = {0};
	JG_SubStringParse_19Q13(CalculatedParasiticLossString, g_CalculatedParasiticLoss_mW_int, g_CalculatedParasiticLoss_mW_decimal);

	//DCInputVoltage
	uint8_t DCInputVoltageString[15] = {0};
	JG_SubStringParse_6Q10(DCInputVoltageString, g_DCInputVoltage_V_int, g_DCInputVoltage_V_decimal);

	//DCInputCurrent
	uint8_t DCInputCurrentString[15] = {0};
	JG_SubStringParse_13Q3(DCInputCurrentString, g_DCInputCurrent_mA_int, g_DCInputCurrent_mA_decimal);

	//CalculatedInputPower
	uint8_t CalculatedInputPowerString[15] = {0};
	JG_SubStringParse_19Q13(CalculatedInputPowerString, g_CalculatedInputPower_mW_int, g_CalculatedInputPower_mW_decimal);

	//FODPeak
	char FODPeak_V_String[10] = {0};
	snprintf((char*)&FODPeak_V_String, 10, "%d", (uint16_t)g_FODPeak_V);

	//OutputFrequency
	uint8_t OutputFrequency_kHz_String[10] = {0};
	JG_SubStringParse_10Q6(OutputFrequency_kHz_String, g_OutputFrequency_kHz_int, g_OutputFrequency_kHz_decimal);

	return snprintf((char*)g_ParsedStringBuffer, PARSED_STRING_BUFFER_LENGTH, "%s %s %s %s %s %s %s %s %s\r\n", (char*)ReportedReceivedPower_mW_String,
																											(char*)ReportedMaxPowerString,
																											(char*)ThresholdSetFromResistorString,
																											(char*)CalculatedParasiticLossString,
																											(char*)DCInputVoltageString,
																											(char*)DCInputCurrentString,
																											(char*)CalculatedInputPowerString,
																											(char*)FODPeak_V_String,
																											(char*)OutputFrequency_kHz_String);

}

size_t JG_StringParse_RxStats(){

	//Signal Strength
	char SignalStrengthString[4];
	snprintf((char*)&SignalStrengthString, 4, "%u", (uint16_t)g_SignalStrengthByte);

	//EndPowerTransfer
	char EndPowerTransferString[4];
	snprintf((char*)&EndPowerTransferString, 4, "%u", (uint16_t)g_EndPowerTransferByte);

	//ControlError
	char ControlErrorString[4];
	snprintf((char*)&ControlErrorString, 4, "%u", (uint16_t)g_ControlErrorByte);

	//ReceivedPower
	char ReceivedPowerString[4];
	snprintf((char*)&ReceivedPowerString, 4, "%u", (uint16_t)g_ReceivedPowerByte);

	//ChargeStatus
	char ChargeStatusString[4];
	snprintf((char*)&ChargeStatusString, 4, "%u", (uint16_t)g_ChargeStatusByte);

	//Holdoff
	char HoldoffString[4];
	snprintf((char*)&HoldoffString, 4, "%u", (uint16_t)g_HoldoffByte);

	//Configuration
	//MaxPower
	char MaxPower_WString[10];
	snprintf((char*)&MaxPower_WString, 10, "%u", (uint16_t)g_ReceiverMaxPower_W);

	//PowerTransferControlType
	char PowerTransferControlTypeString[3];
	snprintf((char*)&PowerTransferControlTypeString, 3, "%d", (uint16_t)g_PowerTransferControlType);

	//NumberOfAdditionalPackets
	char NumberOfAdditionalPacketsString[10];
	snprintf((char*)&NumberOfAdditionalPacketsString, 10, "%d", (uint16_t)g_NumberOfAdditionalPackets);

	//WindowSize_ms
	char WindowSize_msString[10];
	snprintf((char*)&WindowSize_msString, 10, "%d", (uint16_t)g_WindowSize_ms);

	//WindowOffset_ms
	char WindowOffset_msString[10];
	snprintf((char*)&WindowOffset_msString, 10, "%d", (uint16_t)g_WindowOffset_ms);

	//Identification
	//QiVersion
	char QiVersionString[5];
	snprintf((char*)&QiVersionString, 5, "%d.%d", (uint16_t)g_MajorQiVersion, (uint16_t)g_MinorQiVersion);

	//ManufacturerCode
	char ManufacturerCodeString[10];
	snprintf((char*)&ManufacturerCodeString, 10, "%d", (uint16_t)g_ManufacturerCode);

	//ExtendedMode
	char ExtendedModeString[3];
	snprintf((char*)&ExtendedModeString, 3, "%d", (uint16_t)g_ExtendedMode);

	//BasicDeviceIdentifier
	char BasicDeviceIdentifierString[15];
	snprintf((char*)&BasicDeviceIdentifierString, 15, "%x%x", (uint16_t)(g_BasicDeviceIdentifier >> 16), (uint16_t)g_BasicDeviceIdentifier);

	return snprintf((char*)g_ParsedStringBuffer, PARSED_STRING_BUFFER_LENGTH, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s\r\n",
																												(char*)SignalStrengthString,
																												(char*)EndPowerTransferString,
																												(char*)ControlErrorString,
																												(char*)ReceivedPowerString,
																												(char*)ChargeStatusString,
																												(char*)HoldoffString,
																												(char*)MaxPower_WString,
																												(char*)PowerTransferControlTypeString,
																												(char*)NumberOfAdditionalPacketsString,
																												(char*)WindowSize_msString,
																												(char*)WindowOffset_msString,
																												(char*)QiVersionString,
																												(char*)ManufacturerCodeString,
																												(char*)ExtendedModeString,
																												(char*)BasicDeviceIdentifierString);

}

size_t JG_StringParse_TxStats(){

	//VoltageIn
	uint8_t VoltageIn_VString[15] = {0};
	JG_SubStringParse_6Q10(VoltageIn_VString, g_VoltageIn_V_int, g_VoltageIn_V_decimal);

	//CurrentOut
	uint8_t CurrentOut_mAString[15] = {0};
	JG_SubStringParse_13Q3(CurrentOut_mAString, g_CurrentOut_mA_int, g_CurrentOut_mA_decimal);

	//InternalTemperature
	uint8_t InternalTemperature_degCString[15] = {0};
	JG_SubStringParse_9Q7(InternalTemperature_degCString, g_InternalTemperature_degC_int, g_InternalTemperature_degC_decimal);

	//GoodMessageCounter
	uint8_t GoodMessageCounterString[15] = {0};
	snprintf((char*)&GoodMessageCounterString, 15, "%u", (uint16_t)g_GoodMessageCounter);

	//BadMessageCounter
	uint8_t BadMessageCounterString[15] = {0};
	snprintf((char*)&BadMessageCounterString, 15, "%u", (uint16_t)g_BadMessageCounter);

	//Frequency_kHz
	uint8_t Frequency_kHzString[15] = {0};
	JG_SubStringParse_10Q6(Frequency_kHzString,g_Frequency_kHz_int, g_Frequency_kHz_decimal);

	//DutyCycle_percent
	uint8_t DutyCycle_percentString[15] = {0};
	JG_SubStringParse_1Q15(DutyCycle_percentString,g_DutyCycle_percent_int, g_DutyCycle_percent_decimal);

	//LedMode
	uint8_t LedModeString_decimal[15] = {0};
	snprintf((char*)&LedModeString_decimal, 15, "%u", (uint16_t)g_LedModeByte);

	//LedStatus
	uint8_t LedStatusString_hex[15] = {0};
	snprintf((char*)&LedStatusString_hex, 15, "%x", (uint16_t)g_LedStatusByte);

	//FODThreshold_mW
	uint8_t FODThreshold_mWString[15] = {0};
	JG_SubStringParse_19Q13(FODThreshold_mWString, g_FODThreshold_mW_int, g_FODThreshold_mW_decimal);

	//ParasiticLossDetected_mW
	uint8_t ParasiticLossDetected_mWString[15] = {0};
	JG_SubStringParse_19Q13(ParasiticLossDetected_mWString, g_ParasiticLossDetected_mW_int, g_ParasiticLossDetected_mW_decimal);

	//CS100
	uint8_t CS100_hexString[15] = {0};
	snprintf((char*)&CS100_hexString, 15, "%x", (uint16_t)g_CS100Byte);

	return snprintf((char*)g_ParsedStringBuffer, PARSED_STRING_BUFFER_LENGTH, "%s %s %s %s %s %s %s %s %s %s %s %s\r\n",
																												(char*)VoltageIn_VString,
																												(char*)CurrentOut_mAString,
																												(char*)InternalTemperature_degCString,
																												(char*)GoodMessageCounterString,
																												(char*)BadMessageCounterString,
																												(char*)Frequency_kHzString,
																												(char*)DutyCycle_percentString,
																												(char*)LedModeString_decimal,
																												(char*)LedStatusString_hex,
																												(char*)FODThreshold_mWString,
																												(char*)ParasiticLossDetected_mWString,
																												(char*)CS100_hexString);

}

size_t JG_StringParse_MATLABDiagnostics(){

	//DeviceId
	uint8_t DeviceIdString[30];
	snprintf((char*)DeviceIdString, 30, "%s", (char*)g_DeviceIdBuffer);

	//DCInputVoltage
	uint8_t DCInputVoltageString[15] = {0};
	JG_SubStringParse_6Q10(DCInputVoltageString, g_DCInputVoltage_V_int, g_DCInputVoltage_V_decimal);

	//DCInputCurrent
	uint8_t DCInputCurrentString[15] = {0};
	JG_SubStringParse_13Q3(DCInputCurrentString, g_DCInputCurrent_mA_int, g_DCInputCurrent_mA_decimal);

	//CurrentOut
	uint8_t CurrentOut_mAString[15] = {0};
	JG_SubStringParse_13Q3(CurrentOut_mAString, g_CurrentOut_mA_int, g_CurrentOut_mA_decimal);

	//CalculatedInputPower
	uint8_t CalculatedInputPowerString[15] = {0};
	JG_SubStringParse_19Q13(CalculatedInputPowerString, g_CalculatedInputPower_mW_int, g_CalculatedInputPower_mW_decimal);

	//OutputFrequency
	uint8_t OutputFrequency_kHz_String[10] = {0};
	JG_SubStringParse_10Q6(OutputFrequency_kHz_String, g_OutputFrequency_kHz_int, g_OutputFrequency_kHz_decimal);

	//DutyCycle_percent
	uint8_t DutyCycle_percentString[15] = {0};
	JG_SubStringParse_1Q15(DutyCycle_percentString,g_DutyCycle_percent_int, g_DutyCycle_percent_decimal);

	//ReportedReceivedPower
	uint32_t ReportedMaxPower_mW = (g_RawReportedMaxPower * 500);
	uint32_t ReportedPowerQuant_mW = ReportedMaxPower_mW / 128;
	uint16_t ReportedReceivedPower_mW = ReportedPowerQuant_mW * g_ReportedReceivedPower_128thOfMaxPower;
	char ReportedReceivedPower_mW_String[10] = {0};
	snprintf((char*)&ReportedReceivedPower_mW_String, 10, "%d", ReportedReceivedPower_mW);

	//ReportedMaxPower
	char ReportedMaxPowerString[10] = {0};
	snprintf((char*)&ReportedMaxPowerString, 10, "%d", ((uint16_t)g_RawReportedMaxPower * 500));

	//CalculatedParasiticLoss
	uint8_t CalculatedParasiticLossString[15] = {0};
	JG_SubStringParse_19Q13(CalculatedParasiticLossString, g_CalculatedParasiticLoss_mW_int, g_CalculatedParasiticLoss_mW_decimal);

	//ThresholdSetFromResistor
	uint8_t ThresholdSetFromResistorString[15] = {0};
	JG_SubStringParse_19Q13(ThresholdSetFromResistorString, g_ThresholdSetFromResistor_mW_int, g_ThresholdSetFromResistor_mW_decimal);

	//GoodMessageCounter
	uint8_t GoodMessageCounterString[15] = {0};
	snprintf((char*)&GoodMessageCounterString, 15, "%u", (uint16_t)g_GoodMessageCounter);

	//BadMessageCounter
	uint8_t BadMessageCounterString[15] = {0};
	snprintf((char*)&BadMessageCounterString, 15, "%u", (uint16_t)g_BadMessageCounter);

	//Signal Strength
	char SignalStrengthString[4];
	snprintf((char*)&SignalStrengthString, 4, "%u", (uint16_t)g_SignalStrengthByte);

	//EndPowerTransfer
	char EndPowerTransferString[4];
	snprintf((char*)&EndPowerTransferString, 4, "%u", (uint16_t)g_EndPowerTransferByte);

	//ControlError
	char ControlErrorString[4];
	snprintf((char*)&ControlErrorString, 4, "%u", (uint16_t)g_ControlErrorByte);

	//ReceivedPower
	char ReceivedPowerString[4];
	snprintf((char*)&ReceivedPowerString, 4, "%u", (uint16_t)g_ReceivedPowerByte);

	//ChargeStatus
	char ChargeStatusString[4];
	snprintf((char*)&ChargeStatusString, 4, "%u", (uint16_t)g_ChargeStatusByte);

	//Holdoff
	char HoldoffString[4];
	snprintf((char*)&HoldoffString, 4, "%u", (uint16_t)g_HoldoffByte);

	//Configuration
	//MaxPower
	char MaxPower_WString[10];
	snprintf((char*)&MaxPower_WString, 10, "%u", (uint16_t)g_ReceiverMaxPower_W);

	//PowerTransferControlType
	char PowerTransferControlTypeString[3];
	snprintf((char*)&PowerTransferControlTypeString, 3, "%d", (uint16_t)g_PowerTransferControlType);

	//NumberOfAdditionalPackets
	char NumberOfAdditionalPacketsString[10];
	snprintf((char*)&NumberOfAdditionalPacketsString, 10, "%d", (uint16_t)g_NumberOfAdditionalPackets);

	//WindowSize_ms
	char WindowSize_msString[10];
	snprintf((char*)&WindowSize_msString, 10, "%d", (uint16_t)g_WindowSize_ms);

	//WindowOffset_ms
	char WindowOffset_msString[10];
	snprintf((char*)&WindowOffset_msString, 10, "%d", (uint16_t)g_WindowOffset_ms);

	//Identification
	//QiVersion
	char QiVersionString[5];
	snprintf((char*)&QiVersionString, 5, "%d.%d", (uint16_t)g_MajorQiVersion, (uint16_t)g_MinorQiVersion);

	//ManufacturerCode
	char ManufacturerCodeString[10];
	snprintf((char*)&ManufacturerCodeString, 10, "%d", (uint16_t)g_ManufacturerCode);

	//ExtendedMode
	char ExtendedModeString[3];
	snprintf((char*)&ExtendedModeString, 3, "%d", (uint16_t)g_ExtendedMode);

	//BasicDeviceIdentifier
	char BasicDeviceIdentifierString[15];
	snprintf((char*)&BasicDeviceIdentifierString, 15, "%x%x", (uint16_t)(g_BasicDeviceIdentifier >> 16), (uint16_t)g_BasicDeviceIdentifier);

	return snprintf((char*)g_ParsedStringBuffer, PARSED_STRING_BUFFER_LENGTH, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s\r\n",
																													(char*)DeviceIdString,
																													(char*)DCInputVoltageString,
																													(char*)DCInputCurrentString,
																													(char*)CurrentOut_mAString,
																													(char*)CalculatedInputPowerString,
																													(char*)OutputFrequency_kHz_String,
																													(char*)DutyCycle_percentString,
																													(char*)ReportedReceivedPower_mW_String,
																													(char*)ReportedMaxPowerString,
																													(char*)CalculatedParasiticLossString,
																													(char*)ThresholdSetFromResistorString,
																													(char*)GoodMessageCounterString,
																													(char*)BadMessageCounterString,
																													(char*)SignalStrengthString,
																													(char*)EndPowerTransferString,
																													(char*)ControlErrorString,
																													(char*)ReceivedPowerString,
																													(char*)ChargeStatusString,
																													(char*)HoldoffString,
																													(char*)MaxPower_WString,
																													(char*)PowerTransferControlTypeString,
																													(char*)NumberOfAdditionalPacketsString,
																													(char*)WindowSize_msString,
																													(char*)WindowOffset_msString,
																													(char*)QiVersionString,
																													(char*)ManufacturerCodeString,
																													(char*)ExtendedModeString,
																													(char*)BasicDeviceIdentifierString);


}

size_t JG_SubStringParse_19Q13(uint8_t* OutStringBuffer, uint32_t IntegerPart19Bits, uint16_t DecimalPart13Bits){
	//This function discards 3 msbits from integer part (leaving 16 bits) -> not a problem as the valid int range is to 5000 only (less than 65 535)


	uint32_t DecimalPart13BitsQuant_x100000 = 12; // (1 / (0x1 << 13))*100000=12
	uint32_t DecimalPart13Bits_x10000 = ((uint32_t)DecimalPart13Bits * DecimalPart13BitsQuant_x100000)/10; //Has to be divided by 10 to fit in 65 535 range
	if(IntegerPart19Bits <=5000)
		return snprintf((char*)OutStringBuffer, 11, "%d.%04d", (uint16_t)IntegerPart19Bits,((uint16_t)DecimalPart13Bits_x10000));
	else{
		uint16_t NegativeValueInt = 0xFFFF - (uint16_t)IntegerPart19Bits;
		uint16_t NegativeValueDecimal = (DecimalPart13BitsQuant_x100000*(0x1FFF))/10 - DecimalPart13Bits_x10000;
		return snprintf((char*)OutStringBuffer, 11, "-%d.%d", NegativeValueInt, NegativeValueDecimal);
	}

}

size_t JG_SubStringParse_6Q10(uint8_t* OutStringBuffer, uint8_t IntegerPart6Bits, uint16_t DecimalPart10Bits){

	uint32_t DecimalPart10BitsQuant_x100000 = 97; // (1 / (0x1 << 10))*100000=97
	uint32_t DecimalPart10Bits_x10000 = ((uint32_t)DecimalPart10Bits * DecimalPart10BitsQuant_x100000)/10; //Has to be divided by 10 to fit in 65 535 range

	return snprintf((char*)OutStringBuffer, 11, "%d.%04d", (uint16_t)IntegerPart6Bits,((uint16_t)DecimalPart10Bits_x10000));

}

size_t JG_SubStringParse_13Q3(uint8_t* OutStringBuffer, uint16_t IntegerPart13Bits, uint8_t DecimalPart3Bits){

	uint32_t DecimalPart3BitsQuant_x1000 = 125; // (1 / (0x1 << 3))*10000 = 625
	uint32_t DecimalPart3Bits_x1000 = ((uint32_t)DecimalPart3Bits * DecimalPart3BitsQuant_x1000);

	return snprintf((char*)OutStringBuffer, 11, "%d.%03d", (uint16_t)IntegerPart13Bits,((uint16_t)DecimalPart3Bits_x1000));

}

size_t JG_SubStringParse_10Q6(uint8_t* OutStringBuffer, uint16_t IntegerPart10Bits, uint8_t DecimalPart6Bits){

	uint32_t DecimalPart6BitsQuant_x1000000 = 15625; // (1 / (0x1 << 6))*1000000 = 15625
	uint32_t DecimalPart6Bits_x10000 = ((uint32_t)DecimalPart6Bits * DecimalPart6BitsQuant_x1000000)/100;//Divided by 100 to be inside uint16_t range

	return snprintf((char*)OutStringBuffer, 11, "%d.%04d", (uint16_t)IntegerPart10Bits,((uint16_t)DecimalPart6Bits_x10000));

}

size_t JG_SubStringParse_9Q7(uint8_t* OutStringBuffer, uint16_t IntegerPart9Bits, uint8_t DecimalPart7Bits){

	uint32_t DecimalPart7BitsQuant_x1000000 = 7812; // (1 / (0x1 << 7))*1000000 = 7812
	uint32_t DecimalPart7Bits_x10000 = ((uint32_t)DecimalPart7Bits * DecimalPart7BitsQuant_x1000000)/100;//Divided by 100 to be inside uint16_t range

	return snprintf((char*)OutStringBuffer, 11, "%d.%04d", (uint16_t)IntegerPart9Bits,((uint16_t)DecimalPart7Bits_x10000));


}

size_t JG_SubStringParse_1Q15(uint8_t* OutStringBuffer, uint8_t IntegerPart1Bit, uint16_t DecimalPart15Bits){

	uint32_t DecimalPart15BitsQuant_x1000000 = 30; // (1 / (0x1 << 15))*1000000 = 30
	uint32_t DecimalPart15Bits_x10000 = ((uint32_t)DecimalPart15Bits * DecimalPart15BitsQuant_x1000000)/100;//Divided by 100 to be inside uint16_t range

	return snprintf((char*)OutStringBuffer, 11, "%d.%04d", (uint16_t)IntegerPart1Bit,((uint16_t)DecimalPart15Bits_x10000));

}

