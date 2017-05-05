#ifndef BQ500511_I2C_H_
#define BQ500511_I2C_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"

/*
 * Makra s³u¿¹ce do ³atwiejszego korzystania z rejestrów chipu P9025AC
 */

#define BQ500511A_I2C_SLAVE_ADDR ((uint16_t)(0x14 << 1))

#define BQ500511A_I2C_DEVICE_ID_COMMAND_CODE		((uint16_t)0xFD)
#define BQ500511A_I2C_PLD_MONITOR_COMMAND_CODE		((uint16_t)0xD5)
#define BQ500511A_I2C_PLD_THRESHOLD_COMMAND_CODE	((uint16_t)0xD6)
#define BQ500511A_I2C_RX_PROP_COMMAND_CODE			((uint16_t)0xD3)
#define BQ500511A_I2C_RX_PROP_COUNT_COMMAND_CODE	((uint16_t)0xD4)
#define BQ500511A_I2C_RX_STATS_COMMAND_CODE			((uint16_t)0xD0)
#define BQ500511A_I2C_TX_STATS_COMMAND_CODE			((uint16_t)0xD1)

#define BQ500511A_I2C_DEVICE_ID_COMMAND_RESPONSE_LENGTH		((uint16_t)29)
#define BQ500511A_I2C_PLD_MONITOR_COMMAND_RESPONSE_LENGTH	((uint16_t)32)
#define BQ500511A_I2C_PLD_THRESHOLD_COMMAND_RESPONSE_LENGTH	((uint16_t)2)
#define BQ500511A_I2C_RX_PROP_COMMAND_RESPONSE_LENGTH		((uint16_t)22)
#define BQ500511A_I2C_RX_PROP_COUNT_COMMAND_RESPONSE_LENGTH	((uint16_t)2)
#define BQ500511A_I2C_RX_STATS_COMMAND_RESPONSE_LENGTH		((uint16_t)32)
#define BQ500511A_I2C_TX_STATS_COMMAND_RESPONSE_LENGTH		((uint16_t)32)

extern volatile uint8_t g_I2C_Receive_Buffer[100];
extern volatile uint8_t g_DeviceIDRawBuffer[BQ500511A_I2C_DEVICE_ID_COMMAND_RESPONSE_LENGTH];
extern volatile uint8_t g_PLDMonitorRawBuffer[BQ500511A_I2C_PLD_MONITOR_COMMAND_RESPONSE_LENGTH];
extern volatile uint8_t g_PLDThresholdRawBuffer[BQ500511A_I2C_PLD_THRESHOLD_COMMAND_RESPONSE_LENGTH];
extern volatile uint8_t g_RxPropRawBuffer[BQ500511A_I2C_RX_PROP_COMMAND_RESPONSE_LENGTH];
extern volatile uint8_t g_RxPropCountRawBuffer[BQ500511A_I2C_RX_PROP_COUNT_COMMAND_RESPONSE_LENGTH];
extern volatile uint8_t g_RxStatsRawBuffer[BQ500511A_I2C_RX_STATS_COMMAND_RESPONSE_LENGTH];
extern volatile uint8_t g_TxStatsRawBuffer[BQ500511A_I2C_TX_STATS_COMMAND_RESPONSE_LENGTH];

extern I2C_HandleTypeDef hi2c1; //Struktura potrzebna do korzystania z peryferium i2c

void JG_I2C_ReadDeviceId(); //Sprawdzone, ¿e odsy³a 29 bajtów
void JG_I2C_ReadPLDMonitor(); //Ma zawsze odsy³ac 32 bajty
void JG_I2C_ReadPLDTreshhold(); //Ma zawsze odsy³ac 2 bajty
void JG_I2C_ReadRxProp(); //Zawsze zwraca 22 bajty (dot. proprietary packets)
void JG_I2C_ReadRxPropCount(); //Zawsze zwraca 2 bajty
void JG_I2C_ReadRxStats(); //Zawsze zwraca 32 bajty
void JG_I2C_ReadTxStats(); //Zawsze zwraca 32 bajty

#endif /* BQ500511_I2C_H_ */
