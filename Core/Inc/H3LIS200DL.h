/*
 * H3LIS200DL.h
 *
 */

#ifndef INC_H3LIS200DL_H_
#define INC_H3LIS200DL_H_

#include "main.h"
#include "spi_driver.h"

#define H3LIS200DL_ID 0x32

typedef struct
{

} H3LIS200DL_Filter;

typedef struct {

	int8_t x;
	int8_t y;
	int8_t z;

} H3LIS200DL_data;

typedef struct
{
	uint8_t ID;
	H3LIS200DL_Filter filter_struct;
	H3LIS200DL_data data;
	SPI_CS *CS;

} H3LIS200DL;

uint8_t H3LIS200DL_Init(H3LIS200DL *mems);
uint8_t H3LIS200DL_Activate(H3LIS200DL *mems);
uint8_t H3LIS200DL_DeActivate(H3LIS200DL *mems);
uint8_t H3LIS200DL_AccelData(H3LIS200DL *mems);
static float H3LIS200DL_from_fs2_hr_to_mg(int16_t lsb);


#define WHO_AM_I 0x0F

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24

#define HP_FILTER_RESET 0x25

#define REFERENCE 0x26

#define STATUS_REG 0x27

#define OUT_X 0x29
#define OUT_Y 0x2B
#define OUT_Z 0x2D

#define INT1_CFG 0x30
#define INT1_SRC 0x31
#define INT1_THS 0x32
#define INT1_DURATION 0x33

#define INT2_CFG 0x34
#define INT2_SRC 0x35
#define INT2_THS 0x36
#define INT2_DURATION 0x37

#endif /* INC_H3LIS200DL_H_ */
