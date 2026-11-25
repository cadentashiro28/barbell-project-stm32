#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_def.h"

typedef struct {
    SPI_HandleTypeDef *hspi;    
    GPIO_TypeDef *cs_port;
    uint16_t cs_pin;
} spi_device_t;

HAL_StatusTypeDef spi_transfer(spi_device_t *dev, uint8_t *tx, uint8_t *rx, uint16_t len);

#endif
