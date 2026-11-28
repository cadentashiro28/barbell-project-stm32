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

static HAL_StatusTypeDef spi_transfer(spi_device_t *dev, uint8_t *tx, uint8_t *rx, uint16_t len) {
    cs_assert(dev);
    HAL_StatusTypeDef err = HAL_SPI_TransmitReceive(dev->hspi, tx, rx,len, SPI_TIMEOUT_DEFAULT);
    cs_deassert(dev);
    return err;
}

HAL_StatusTypeDef spi_read_reg(spi_device_t *dev, uint8_t address, uint8_t *rx_data) {
    uint8_t tx[2] = {address | (1 << 7), 0};
    uint8_t rx[2] = {0};
    HAL_StatusTypeDef err = spi_transfer(dev, tx, rx, sizeof(tx));
    rx_data = &rx[1];
    return err;
}

HAL_StatusTypeDef spi_write_reg(spi_device_t *dev, uint8_t address, uint8_t val) {
    uint8_t tx[2] = {address | (1 << 7), val};
    uint8_t rx[2] = {0};
    HAL_StatusTypeDef err = spi_transfer(dev, tx, rx, sizeof(tx));
    return err;
}


