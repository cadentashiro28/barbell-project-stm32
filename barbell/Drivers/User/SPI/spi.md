11/24/26
Goal #1, get SPI online and readback IMU
- Need to assess SPI initialization parameters, CPOL/CPHA, SPI mode
- Then build a basic wrapper for HAL calls + CS handling

Notes:
CPOL: 1, high resting clock (see fig 3)
CPHA: 1, clock falling edge (leading) launches, and clock rising edge (trailing) samples the MSB

Wrapping device parameters and handing off handle
typedef struct {
    SPI_HandleTypeDef *hspi;    
    GPIO_TypeDef *cs_port;
    uint16_t cs_pin;
} spi_device_t;
Externs are hard wired to a name
Function parameters would get too large (data ptr, size, timeout, cs port + pin, handle,)
struct is a nice way to keep related data together
HAL_SPI calls have enough overhead to not manually delay between CS assert and read.
In other words we won't violate t_setup = 5ns

Bug that caught me
Was shifting write enable bit (bit 0) too far, used (1 << 8), actually (1 << 7).
Remember that you write on cycle 1, response 1 is garbage, collect response on next sample cycle.
tx[0] = write command, tx[1] nothing, rx[0] dismiss, rx[1] = response
