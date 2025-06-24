/*
 * stm32f4xx_spi_driver.h
 *
 *  Created on: Apr 2, 2025
 *      Author: 35596
 */

#ifndef INC_STM32F4XX_SPI_DRIVER_H_
#define INC_STM32F4XX_SPI_DRIVER_H_

#include "stm32f4xx.h"

/*
 * @SPI_DeviceMode
 */
#define SPI_MODE_MASTER 1
#define SPI_MODE_SLAVE  0

typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;

}SPI_Confg_t;

typedef struct
{
	SPI_RegDef_t *pSPIx;
	SPI_Confg_t SPIConfig;
}SPI_Handle_t;

void SPI_PeriClkCtrl(SPI_RegDef_t *pvSPIx,uint8_t EnDis);
void SPI_Init(SPI_Handle_t *pvSPI_handle);
void SPI_DeInit(SPI_RegDef_t *pvSPIx);

#endif /* INC_STM32F4XX_SPI_DRIVER_H_ */
