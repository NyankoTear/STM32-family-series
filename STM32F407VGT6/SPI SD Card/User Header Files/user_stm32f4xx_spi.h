#include "stm32f4xx_ll_spi.h"

#ifndef __USER_STM32F4XX_SPI_H__
#define __USER_STM32F4XX_SPI_H__

void SPIInitialization(SPI_TypeDef* const SPIx);
uint8_t SPIMasterTransmit8BitData(SPI_TypeDef* const SPIx, uint8_t const TransmitData);

#endif  /*   __USER_STM32F4XX_SD_CARD_SPI_H__  */