#include "JG_PowerSourceDetection.h"

//Tablica zawieraj¹ca pomiar napiêcia na dzielniku oporowym. Pierwsze pole tablicy to J1 a drugie to J2.
volatile uint16_t g_ADCMeasurements[2];


const uint32_t J1USB_VoltageDividerCoefficientx10000_V = 15575;
const uint32_t J2DCJack_VoltageDividerCoefficientx10000_V = 15566;

void JG_ParseAndSendADCMeasurementsToUART(){

	uint32_t J1USB_VoltageDividerVoltagex1000V = 33*100 * g_ADCMeasurements[0] / 4095;
	uint32_t J2DCJack_VoltageDividerVoltagex1000V = 33*100 * g_ADCMeasurements[1] / 4095;

	uint32_t J1USB_Volatagex1000_V = (J1USB_VoltageDividerVoltagex1000V * J1USB_VoltageDividerCoefficientx10000_V) / 10000;
	uint32_t J2DCJack_Voltagex1000_V = (J2DCJack_VoltageDividerVoltagex1000V * J2DCJack_VoltageDividerCoefficientx10000_V) / 10000;

	uint16_t J1USB_VoltageIntegerPart_V = J1USB_Volatagex1000_V / 1000;
	uint16_t J1USB_VoltageDecimalPart_V = J1USB_Volatagex1000_V - (J1USB_VoltageIntegerPart_V*1000);

	uint16_t J2DCJack_VoltageIntegerPart_V = J2DCJack_Voltagex1000_V / 1000;
	uint16_t J2DCJack_VoltageDecimalPart_V = J2DCJack_Voltagex1000_V - (J2DCJack_VoltageIntegerPart_V*1000);

	uint8_t StringBuffer[40];
	size_t size = snprintf((char*)StringBuffer, 40, "J1USB = %d.%03d V | J2DCJack = %d.%03d V\r\n", J1USB_VoltageIntegerPart_V, J1USB_VoltageDecimalPart_V, J2DCJack_VoltageIntegerPart_V, J2DCJack_VoltageDecimalPart_V);

	HAL_UART_Transmit(&huart3,StringBuffer,size, 100);

}
