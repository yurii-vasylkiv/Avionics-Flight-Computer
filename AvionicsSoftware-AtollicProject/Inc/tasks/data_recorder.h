#ifndef DATA_LOGGING_H
#define DATA_LOGGING_H
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// UMSATS 2018-2020
//
// Repository:
//  UMSATS/Avionics-2019
//
// File Description:
//  Header file for the data logging module. This uses the flash memory interface to log data to memory.
//
// History
// 2019-04-09 by Joseph Howarth
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <string.h> 				// For memcpy
#include <math.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "forward_declarations.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#define DATA_BUFFER_SIZE	FLASH_PAGE_SIZE			//Matches flash memory page size.
#define ACC_TYPE 			0x800000
#define GYRO_TYPE			0x400000
#define PRES_TYPE			0x200000
#define	TEMP_TYPE			0x100000

#define DROGUE_DETECT		0x080000
#define DROGUE_DEPLOY		0x040000

#define MAIN_DETECT			0x020000
#define MAIN_DEPLOY			0x010000

#define LAUNCH_DETECT		0x008000
#define LAND_DETECT			0x004000

#define POWER_FAIL			0x002000
#define	OVERCURRENT_EVENT	0x001000

#define	ACC_LENGTH	6		//Length of a accelerometer measurement in bytes.
#define	GYRO_LENGTH	6		//Length of a gyroscope measurement in bytes.
#define	PRES_LENGTH	3		//Length of a pressure measurement in bytes.
#define	TEMP_LENGTH	3		//Length of a temperature measurement in bytes.
#define ALT_LENGTH  4
#define HEADER_SIZE 3


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// ENUMS AND ENUM TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef enum{

	BUFFER_A = 0,
	BUFFER_B = 1

} BufferSelection_t;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// STRUCTS AND STRUCT TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct{

	Flash * flash_ptr;
	UART_HandleTypeDef * uart;
	configData_t *flightCompConfig;

	//Queues
	QueueHandle_t IMU_data_queue;	//For holding accelerometer and gyroscope readings.
	QueueHandle_t PRES_data_queue;	//For holding pressure and temp. readings.

	TaskHandle_t *timerTask_h;

}thread_data_recorder_parameters;


typedef struct{

			uint8_t  data[HEADER_SIZE+ACC_LENGTH+GYRO_LENGTH+PRES_LENGTH+TEMP_LENGTH+ALT_LENGTH];

}Measurement_t;
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// CONSTANTS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This task logs data measurements to the flash memory.
//
//	Should be passed a populated LoggingStruct as the parameter.
//	The flash should be initialized before this task is started.
//
// Returns:
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void thread_data_recorder_start(void * params);

#endif // DATA_LOGGING_H
