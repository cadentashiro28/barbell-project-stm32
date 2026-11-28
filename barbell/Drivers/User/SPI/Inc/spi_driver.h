#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_def.h"

typedef struct {
    SPI_HandleTypeDef *hspi;    
    GPIO_TypeDef *cs_port;
    uint16_t cs_pin;
} spi_device_t;

HAL_StatusTypeDef spi_read_reg(spi_device_t *dev, uint8_t address, uint8_t *rx_data);
HAL_StatusTypeDef spi_write_reg(spi_device_t *dev, uint8_t address, uint8_t val );

#endif
