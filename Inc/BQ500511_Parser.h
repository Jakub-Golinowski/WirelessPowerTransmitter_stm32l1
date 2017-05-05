#ifndef BQ500511_PARSER_H_
#define BQ500511_PARSER_H_

#include "mini-printf.h"
#include "BQ500511_I2C.h"

#define BQ500511A_DEVICE_ID_BUFFER_LENGTH				(BQ500511A_I2C_DEVICE_ID_COMMAND_RESPONSE_LENGTH - 1)
#define BQ500511A_RX_PROP_BUFFER_LENGTH					(BQ500511A_I2C_RX_PROP_COMMAND_RESPONSE_LENGTH - 1)
#define	BQ500511A_CONFIGURATION_BUFFER_LENGTH			(5)
#define	BQ500511A_IDENTIFICATION_BUFFER_LENGTH			(7)
#define	BQ500511A_EXTENDED_IDENTIFICATION_BUFFER_LENGTH	(8)

extern volatile uint8_t g_DeviceIdBuffer[BQ500511A_DEVICE_ID_BUFFER_LENGTH];

extern volatile uint8_t g_ReportedReceivedPower_128thOfMaxPower;
extern volatile uint8_t g_RawReportedMaxPower_mW;
extern volatile uint32_t g_ThresholdSetFromResistor_mW_int;
extern volatile uint16_t g_ThresholdSetFromResistor_mW_decimal;
extern volatile uint32_t g_CalculatedParasiticLoss_mW_int;
extern volatile uint32_t g_CalculatedParasiticLoss_mW_decimal;
extern volatile uint8_t g_DCInputVoltage_V_int;
extern volatile uint16_t g_DCInputVoltage_V_decimal;
extern volatile uint16_t g_DCInputCurrent_mA_int;
extern volatile uint8_t g_DCInputCurrent_mA_decimal;
extern volatile uint32_t g_CalculatedInputPower_mW_int;
extern volatile uint16_t g_CalculatedInputPower_mW_decimal;
extern volatile uint16_t g_FODPeak_V;
extern volatile uint16_t g_OutputFrequency_kHz_int;
extern volatile uint16_t g_OutputFrequency_kHz_decimal;

extern volatile uint16_t g_PLD_Threshold;

extern volatile uint8_t g_RxPropBuffer[BQ500511A_RX_PROP_BUFFER_LENGTH];

extern volatile uint16_t g_RxPropCount;

extern volatile uint8_t g_SignalStrengthByte;
extern volatile uint8_t g_EndPowerTransferByte;
extern volatile uint8_t g_ControlErrorByte;
extern volatile uint8_t g_ReceivedPowerByte;
extern volatile uint8_t g_ChargeStatusByte;
extern volatile uint8_t g_HoldoffByte;
extern volatile uint8_t g_ConfigurationBuffer[BQ500511A_CONFIGURATION_BUFFER_LENGTH];
extern volatile uint8_t g_IdentificationBffer[BQ500511A_IDENTIFICATION_BUFFER_LENGTH];
extern volatile uint8_t g_ExtendedIdentificationBuffer[BQ500511A_EXTENDED_IDENTIFICATION_BUFFER_LENGTH];

extern volatile uint8_t g_VoltageIn_V_int;
extern volatile uint16_t g_VoltageIn_V_decimal;
extern volatile uint16_t g_CurrentOut_mA_int;
extern volatile uint16_t g_CurrentOut_mA_decimal;
extern volatile uint16_t g_InternalTemperature_degC_int;
extern volatile uint8_t g_InternalTemperature_degC_decimal;
extern volatile uint16_t g_GoodMessageCounter;
extern volatile uint16_t g_BadMessageCounter;
extern volatile uint16_t g_Frequency_kHz_int;
extern volatile uint16_t g_Frequency_kHz_decimal;
extern volatile uint8_t g_DutyCycle_percent_int;
extern volatile uint16_t g_DutyCycle_percent_decimal;
extern volatile uint8_t g_LedModeByte;
extern volatile uint16_t g_LedStatusByte;
extern volatile uint32_t g_FODThreshold_mW_int;
extern volatile uint16_t g_FODThreshold_mW_decimal;
extern volatile uint32_t g_ParasiticLossDetected_mW_int;
extern volatile uint16_t g_ParasiticLossDetected_mW_decimal;
extern volatile uint8_t g_CS100Byte;

void JG_Parse_DeviceBuffer();
void JG_Parse_PLDMonitor();
void JG_Parse_PLDThreshold();
void JG_Parse_RxProp();
void JG_Parse_RxPropCount();
void JG_Parse_RxStats();
void JG_Parse_TxStats();

void JG_SubParse_ThresholdSetFromResistor();
void JG_SubParse_FourBytesTo19Q13(uint32_t* OutIntegerPart19Bits, uint16_t* OutDecimalPart13Bits, uint8_t* RawFourBytesArrayMSBFirst);
void JG_SubParse_TwoBytesTo6Q10(uint8_t* OutIntegerPart6Bits, uint16_t* OutDecimalPart10Bits, uint8_t* RawTwoBytesArrayMSBFirst);
void JG_SubParse_TwoBytesTo13Q3(uint16_t* OutIntegerPart13Bits, uint8_t* OutDecimalPart3Bits, uint8_t* RawTwoBytesArrayMSBFirst);
void JG_SubParse_TwoBytesTo10Q6(uint16_t* OutIntegerPart10Bits, uint8_t* OutDecimalPart6Bits, uint8_t* RawTwoBytesArrayMSBFIrst);
void JG_SubParse_TwoBytesTo9Q7(uint16_t* OutIntegerPart9Bits, uint8_t* OutDecimalPart7Bits, uint8_t* RawTwoBytesArrayMSBFirst);
void JG_SubParse_TwoBytesTo1Q15(uint8_t* OutIntegerPart1Bit, uint16_t* OutDecimalPart15Bits, uint8_t* RawTwoBytesArrayMSBFirst);
#endif /* BQ500511_PARSER_H_ */
