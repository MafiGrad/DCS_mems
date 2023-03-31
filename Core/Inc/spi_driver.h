/*
 *
 */

#ifndef INC_SPI_DRIVER_H_
#define INC_SPI_DRIVER_H_


#include "main.h"
#include "spi.h"

typedef struct
{
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;

} SPI_CS;

uint8_t spi_read(uint8_t address, uint8_t *buffer, uint8_t size, SPI_CS *CS);
uint8_t spi_write(uint8_t address, uint8_t *buffer, uint8_t size, SPI_CS *CS);



#endif /* INC_SPI_DRIVER_H_ */
