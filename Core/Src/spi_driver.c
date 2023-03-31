/*
 *
 */

#include "spi_driver.h"

/**
 * @brief  Write data to spi
 * @param  address
 * @param  buff
 * @param  size
 * @retval res
 */
uint8_t spi_write(uint8_t address, uint8_t *buffer, uint8_t size, SPI_CS *CS){
	uint8_t res;
	uint8_t rx_byte;
	uint8_t tx_byte;

	if(size < 1){
		res = 0;
		return res;
	} else if(size > 1){
		address |= 0x40;
	}
	HAL_GPIO_WritePin(CS->GPIOx, CS->GPIO_Pin, GPIO_PIN_RESET);

	HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)&address, (uint8_t*)&rx_byte, 1, 0x1000);
	for (uint8_t buff_index = 0; buff_index < size; buff_index++){
		tx_byte = buffer[buff_index];
		HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)&tx_byte, (uint8_t*)&rx_byte, 1, 0x1000);
	}

	HAL_GPIO_WritePin(CS->GPIOx, CS->GPIO_Pin, GPIO_PIN_SET);

	res = 1;
	return res;
}


/**
 * @brief  Read data from spi
 * @param  address
 * @param  buffer
 * @param  size
 * @retval res
 */
uint8_t spi_read(uint8_t address, uint8_t *buffer, uint8_t size, SPI_CS *CS){
	uint8_t res;
	uint8_t rx_byte;
	uint8_t spacer_byte= 0x00;

	if(size < 1){
		res = 0;
		return res;
	} else if(size > 1){
		address |= 0x40;
	}

	HAL_GPIO_WritePin(CS->GPIOx, CS->GPIO_Pin, GPIO_PIN_RESET);

	address |= 0x80;
	HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)&address, (uint8_t*)&rx_byte, 1, 0x1000);
	for (uint8_t buff_index = 0; buff_index < size; buff_index++){
		HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)&spacer_byte, (uint8_t*)&rx_byte, 1, 0x1000);
		buffer[buff_index] = rx_byte;
	}

	HAL_GPIO_WritePin(CS->GPIOx, CS->GPIO_Pin, GPIO_PIN_SET);

	res = 1;
	return res;
}
