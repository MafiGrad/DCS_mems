/*
 * LIS2DH12.c
 *
 */

#include "LIS2DH12.h"


uint8_t LIS2DH12_Init(LIS2DH12 *mems){
	uint8_t res;
	spi_read(WHO_AM_I, &res, 1, mems->CS);
	if (res == LIS2DH12_ID){
		mems->ID = res;
		return 0;
	}
	return -1;
}

uint8_t LIS2DH12_Activate(LIS2DH12 *mems){
	uint8_t res = 0x97;
	uint8_t ctrl_res = 0;
	spi_write(CTRL_REG1, &res, 1, mems->CS);
	res = 0x88;
	spi_write(CTRL_REG4, &res, 1, mems->CS);
	spi_read(REFERENCE, &ctrl_res, 1, mems->CS);
	return 0;
}

uint8_t LIS2DH12_DeActivate(LIS2DH12 *mems){
	uint8_t res = 0;
	uint8_t ctrl_res = 0;
	spi_read(CTRL_REG1, &res, 1, mems->CS);
	res &= 0x0F;
	spi_write(CTRL_REG1, &res, 1, mems->CS);
	spi_read(CTRL_REG1, &ctrl_res, 1, mems->CS);
	if (ctrl_res == res){
		return 0;
	}
	return -1;
}

uint8_t LIS2DH12_AccelData(LIS2DH12 *mems){
	uint8_t res[7];
	LIS2DH12_data new_data;
	spi_read(STATUS_REG, &res, 7, mems->CS);

	new_data.x = LIS2DH12_from_fs2_hr_to_mg(res[1] + res[2] * 0xFF);
	new_data.y = LIS2DH12_from_fs2_hr_to_mg(res[3] + res[4] * 0xFF);
	new_data.z = LIS2DH12_from_fs2_hr_to_mg(res[5] + res[6] * 0xFF);

	mems->data = new_data;
	return 0;
}


static float LIS2DH12_from_fs2_hr_to_mg(int16_t lsb)
{
  return ((float)lsb / 16.0f) * 1.0f;
}

