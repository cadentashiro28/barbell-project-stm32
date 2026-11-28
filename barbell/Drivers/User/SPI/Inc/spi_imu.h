#ifndef SPI_IMU_H
#define SPI_IMU_H

#include "spi_driver.h"
#include <stdbool.h>

HAL_StatusTypeDef imu_who_am_i_test(spi_device_t *dev);
HAL_StatusTypeDef imu_set_CTRL1(spi_device_t *dev, uint8_t fifo_th_l);
HAL_StatusTypeDef imu_set_CTRL3(spi_device_t *dev, bool bdu);


#endif