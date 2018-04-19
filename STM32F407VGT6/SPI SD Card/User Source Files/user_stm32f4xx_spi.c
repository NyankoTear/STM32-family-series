#include "user_stm32f4xx_spi.h"

void SPIInitialization(SPI_TypeDef* const SPIx)
{
  LL_SPI_SetBaudRatePrescaler(SPIx, LL_SPI_BAUDRATEPRESCALER_DIV16);
  LL_SPI_SetClockPolarity(SPIx, LL_SPI_POLARITY_LOW);
  LL_SPI_SetClockPhase(SPIx, LL_SPI_PHASE_1EDGE);
  LL_SPI_SetDataWidth(SPIx, LL_SPI_DATAWIDTH_8BIT);
  LL_SPI_SetTransferBitOrder(SPIx, LL_SPI_MSB_FIRST);
  LL_SPI_SetNSSMode(SPIx, LL_SPI_NSS_SOFT);
  LL_SPI_SetStandard(SPIx, LL_SPI_PROTOCOL_MOTOROLA);
  LL_SPI_SetMode(SPIx, LL_SPI_MODE_MASTER);
  LL_SPI_SetTransferDirection(SPIx, LL_SPI_FULL_DUPLEX);
  LL_SPI_Enable(SPIx);
}

uint8_t SPIMasterTransmit8BitData(SPI_TypeDef* const SPIx, uint8_t const TransmitData)
{
  uint8_t ReceiveData = 0x00U;               //  Create unsigned integer value which receive the value.
  
  LL_SPI_TransmitData8(SPIx, TransmitData);  //  Write "TransmitData" 8-bit value to be transmitted into the SPI_DR register.
  while(!LL_SPI_IsActiveFlag_TXE(SPIx));     //  Wait until TXE = 1.
  while(!LL_SPI_IsActiveFlag_RXNE(SPIx));    //  Wait until RNXE = 1(This clears the RXNE bit).
  ReceiveData = LL_SPI_ReceiveData8(SPIx);   //  Read the last received data.

  return ReceiveData;                        //  Return "ReceiveData" 8-bit value.
}