/*
 * H3LIS200DL.c
 *
 */

#include "H3LIS200DL.h"


uint8_t H3LIS200DL_Init(H3LIS200DL *mems){
	uint8_t res;
	spi_read(WHO_AM_I, &res, 1, mems->CS);
	if (res == H3LIS200DL_ID){
		mems->ID = res;
		return 0;
	}
	return -1;
}

uint8_t H3LIS200DL_Activate(H3LIS200DL *mems){
	uint8_t res = 0x3F;
	uint8_t ctrl_res = 0;
	spi_write(CTRL_REG1, &res, 1, mems->CS);
	return 0;
}

uint8_t H3LIS200DL_DeActivate(H3LIS200DL *mems){
	uint8_t res = 0;
	uint8_t ctrl_res = 0;
	spi_read(CTRL_REG1, &res, 1, mems->CS);
	res &= 0x1F;
	spi_write(CTRL_REG1, &res, 1, mems->CS);
	spi_read(CTRL_REG1, &ctrl_res, 1, mems->CS);
	if (ctrl_res == res){
		return 0;
	}
	return -1;
}

uint8_t H3LIS200DL_AccelData(H3LIS200DL *mems){
	uint8_t res;
	H3LIS200DL_data new_data;

	spi_read(OUT_X, &res, 1, mems->CS);
	new_data.x = res;
	spi_read(OUT_Y, &res, 1, mems->CS);
	new_data.y = res;
	spi_read(OUT_Z, &res, 1, mems->CS);
	new_data.z = res;

	mems->data = new_data;
	return 0;
}


float H3LIS200DL_from_fs200_to_mg(int16_t lsb)
{
  return ((float)lsb / 8.0f) * 1.0f;
}
