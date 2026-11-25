#include "spi_driver.h"
#include "spi_imu.h"
#include <stdio.h>

#define WHO_AM_I_REG 0x0F
#define WHO_AM_I_EXPECTED 0x69


void spi_imu_who_am_i_test(spi_device_t *dev) {
    uint8_t tx[2] = {WHO_AM_I_REG | (1 << 7), 0};
    uint8_t rx[2] = {0};
    HAL_StatusTypeDef err = spi_transfer(dev, tx, rx, sizeof(tx));
    if (err == HAL_OK) {
        printf("%s\r\n", (rx[1] == WHO_AM_I_EXPECTED) ? "who am i pass" : "who am i fail");
    }
}
