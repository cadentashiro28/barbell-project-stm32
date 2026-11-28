#include "spi_driver.h"
#include "stm32h7xx_hal_def.h"
#include <stdio.h>
#include "spi_imu.h"
#include <stdint.h>

// LSM6DS3 (IMU)
// https://content.arduino.cc/assets/st_imu_lsm6ds3_datasheet.pdf#%5B%7B%22num%22%3A100%2C%22gen%22%3A0%7D%2C%7B%22name%22%3A%22XYZ%22%7D%2C118%2C751%2Cnull%5D
#define WHO_AM_I_REG 0x0F
#define WHO_AM_I_EXPECTED 0x69

#define REG_CTRL3_C 0x12
#define BDU_SHIFT 6

#define REG_FIFO_CTRL1 0x06
#define FIFO_TH_L 0x00

#define REG_FIFO_CTRL2 0x07

#define FIFO_TH_H_MASK 0b1111
#define FIFO_TH_H 0x00

#define REG_FIFO_CTRL3 0x08

#define DEC_FIFO_GYRO_SHIFT 3
#define DEC_FIFO_GYRO_MASK (0b111 << DEC_FIFO_GYRO_SHIFT)
#define DEC_FIFO_GYRO 0x00

#define DEC_FIFO_XL_MASK 0b111
#define DEC_FIFO_XL 0x00

#define REG_FIFO_CTRL5 0x0A

#define ODR_FIFO_GYRO_SHIFT 3
#define ODR_FIFO_GYRO_MASK (0b1111 << ODR_FIFO_GYRO_SHIFT)
#define ODR_FIFO_GYRO 0x00

#define FIFO_MODE_MASK 0b111
#define FIFO_MODE 0x00

#define REG_FIFO_STATUS1 0x3A
#define DIF_FIFO_H_MASK 0b11111111

#define REG_FIFO_STATUS2 0x3B
#define FTH_SHIFT 7
#define FIFO_OVER_RUN_SHIFT 6
#define FIFO_FULL_SHIFT 5
#define FIFO_EMPTY_SHIFT 4
#define DIF_FIFO_L_MASK 0b1111

#define REG_FIFO_STATUS3 0x3C

#define REG_FIFO_STATUS4 0x3D
#define FIFO_PATTERN_H_MASK 0b11

#define REG_FIFO_DATA_OUT_L 0x3E
#define REG_FIFO_DATA_OUT_H 0x3F

#define REG_INT1_CTRL 0x0D
#define INT1_FTH_SHIFT 3

#define REG_CTRL1_XL 0x10
#define ODR_XL_SHIFT 4
#define ODR_XL_MASK (0b1111 << ODR_XL_SHIFT)
#define ODR_XL 0x00

#define FS_XL_SHIFT 2
#define FS_XL_MASK (0b11 << FS_XL_SHIFT)
#define FS_XL 0x00

#define BW_XL_MASK 0b11
#define BW_XL 0x00


#define REG_CTRL2_G 0x11

HAL_StatusTypeDef imu_who_am_i_test(spi_device_t *dev) {
    uint8_t rx = 0;
    HAL_StatusTypeDef err = spi_read_reg(dev, WHO_AM_I_REG, &rx);
    if (rx == WHO_AM_I_EXPECTED) {
        printf("Passed WHO_AM_I\r\n");
    } else {
        printf("FAILED WHO_AM_I\r\n");
    }
    return err;
}

HAL_StatusTypeDef imu_set_CTRL1(spi_device_t *dev, uint8_t fifo_th_l) {
    HAL_StatusTypeDef err = spi_write_reg(dev, REG_CTRL3_C, fifo_th_l);
}

HAL_StatusTypeDef imu_set_CTRL3(spi_device_t *dev, bool bdu) {
    uint8_t curr = 0;
    spi_read_reg(dev, REG_CTRL3_C, &curr);
    curr |= bdu << BDU_SHIFT;
    uint8_t rx[2] = {0};
    return spi_write_reg(dev, REG_CTRL3_C, curr);
}






