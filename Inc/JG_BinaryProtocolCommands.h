#ifndef JG_BINARYPROTOCOLCOMMANDS_H_
#define JG_BINARYPROTOCOLCOMMANDS_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"
#include "BQ500511_StringParser.h"
#include "JG_PowerSourceDetection.h"
/* Defines ------------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

//Cykliczny bufor kommend.
#define COMMAND_BUFFER_SIZE 32 // Command buffer, should be a power of 2 (f.e. 2^5 = 32)
#define COMMAND_BUFFER_MASK (COMMAND_BUFFER_SIZE-1) //USART receiving buffer mask, to control buffer head and tail indexes

#define FOD_THRESHOLD_NEW_VALUE_BUFFER_SIZE 10

#define BINARY_PROTOCOL_RESPONSE_BUFFER_LENGTH 200

#define JG_Command_IdentificationCommandCode (0x69)		// 0x69 oznacza 'i' w kodzie ASCII
#define JG_Command_IdentificationCommandRespone ("Wireless Power Transmitter WPC v1.2 A11 Low Power\r\nJakub Golinowski ZMiSP ISE 03/2017.\r\nCompilation time: " __DATE__ " " __TIME__ "\r\n")
#define JG_Command_IdentificationCommandResponseLength (sizeof(JG_Command_IdentificationCommandRespone)-1)

#define JG_Command_RepeatModeEnableCommandCode (0x72)		// 0x72 oznacza 'r' w kodzie ASCII
#define JG_Command_RepeatModeEnableCommandResponseBeginning ("\n\r========= ==================== =========\n\r          Entering Repeat Mode          \n\r========= ==================== =========\n\r")
#define JG_Command_RepeatModeEnableCommandResponseBeginningLength (sizeof(JG_Command_RepeatModeEnableCommandResponseBeginning)-1)

#define JG_Command_SingleDiagCommandCode (0x73)		// 0x73 oznacza 's' w kodzie ASCII

#define JG_Command_FODThresholdSetCommandCode (0x74)		// 0x74 oznacza 't' w kodzie ASCII
#define JG_Command_FODThresholdSetCommandResponse ("Send new FOD Threshold value in mW (range 0 - 2000)\r\n")
#define JG_Command_FODThresholdSetCommandResponeLength (sizeof(JG_Command_FODThresholdSetCommandResponse)-1)
#define FOD_THRESHOLD_VALUE_DELIMITER ((uint8_t)'\n')

#define JG_Command_SetUSBJ1AsPowerSourceCommandCode (0x31)	// 0x31 oznacza '1' w kodzie ASCII
#define JG_Command_SetUSBJ1AsPowerSourceResponse ("USB (J1) is now set as Power Source for Wireless Power Transfer Module\r\n")
#define JG_Command_SetUSBJ1AsPowerSourceResponeLength (sizeof(JG_Command_SetUSBJ1AsPowerSourceResponse)-1)

#define JG_Command_SetDCJackJ2AsPowerSourceCommandCode (0x32)	//0x32 oznacza '2' w kodzie ASCII
#define JG_Command_SetDCJackJ2AsPowerSourceResponse ("DC Jack (J2) is now set as Power Source for Wireless Power Transfer Module\r\n")
#define JG_Command_SetDCJackJ2AsPowerSourceResponeLength (sizeof(JG_Command_SetDCJackJ2AsPowerSourceResponse)-1)

#define JG_Command_ADCResultsQueryCommandCode (0x61)	//0x61 oznacza 'a' w kodzie ASCII
#define JG_Command_ADCResultsQueryResponseBeginning ("ADC results (1st J1, 2nd J2)\r\n")
#define JG_Command_ADCResultsQueryResponeBeginningLength (sizeof(JG_Command_ADCResultsQueryResponseBeginning)-1)

#define JG_Command_UnknownCommandRespone ("Unknown Command.\r\n")
#define JG_Command_UnknownCommandResponseLength (sizeof(JG_Command_UnknownCommandRespone)-1)

/* Global Variables ------------------------------------------------------------------*/
extern volatile uint8_t g_CommandReceivedCounter;
extern volatile uint8_t g_CommandBufferFullFlag;
extern volatile uint8_t g_RepeatModeFlag;
extern volatile uint8_t g_ExtendedRepeatModeFlag;

extern volatile uint8_t aTxBuffer_GV[BINARY_PROTOCOL_RESPONSE_BUFFER_LENGTH];

extern volatile uint8_t command_buffer_tail_index_GV;
extern volatile uint8_t command_buffer_head_index_GV;
extern volatile uint8_t command_buffer_GV[COMMAND_BUFFER_SIZE];

extern volatile uint8_t g_FODThresholdReadModeFlag;
extern volatile uint8_t g_FODThresholdNewValueBuffer[FOD_THRESHOLD_NEW_VALUE_BUFFER_SIZE];
extern volatile uint8_t g_FODThresholdNewValueBuffer_Index;
extern volatile uint8_t g_FODThresholdSingleByte;

extern volatile uint8_t ReceivedCommandByte;

extern volatile uint16_t g_ADCMeasurements[2];

//TODO zmienic tak ¿eby w tym pliku nie by³ widoczny provider po³¹czenia:
extern UART_HandleTypeDef huart3;
/* Function Declarations ------------------------------------------------------------------*/
int8_t JG_CommandBuffer_GetCommand(uint8_t * receivedData);
void JG_ProcessCurrentCommand(uint8_t Command);



#endif /* JG_BINARYPROTOCOLCOMMANDS_H_ */
