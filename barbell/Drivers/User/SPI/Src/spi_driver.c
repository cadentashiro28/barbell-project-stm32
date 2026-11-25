#include "spi_driver.h"
#include "stm32h7xx_hal_gpio.h"
#include "stm32h7xx_hal_spi.h"

#define SPI_TIMEOUT_DEFAULT 100

// HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size, uint32_t Timeout);
// HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);
// HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, const uint8_t *pTxData, uint8_t *pRxData,
//                                           uint16_t Size, uint32_t Timeout);
// HAL_StatusTypeDef HAL_SPI_Transmit_IT(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size);
// HAL_StatusTypeDef HAL_SPI_Receive_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);
// HAL_StatusTypeDef HAL_SPI_TransmitReceive_IT(SPI_HandleTypeDef *hspi, const uint8_t *pTxData, uint8_t *pRxData,
//                                              uint16_t Size);

// HAL_StatusTypeDef HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size);
// HAL_StatusTypeDef HAL_SPI_Receive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);
// HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, const uint8_t *pTxData, uint8_t *pRxData,
//                                               uint16_t Size);

static void cs_assert(spi_device_t *dev) {
    HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_RESET);

}

static void cs_deassert(spi_device_t *dev) {
    HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);
}

HAL_StatusTypeDef spi_transfer(spi_device_t *dev, uint8_t *tx, uint8_t *rx, uint16_t len) {
    cs_assert(dev);
    HAL_StatusTypeDef err = HAL_SPI_TransmitReceive(dev->hspi, tx, rx,len, SPI_TIMEOUT_DEFAULT);
    cs_deassert(dev);
    return err;
}

