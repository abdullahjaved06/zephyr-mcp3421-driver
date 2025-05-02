

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/device.h>

static const struct i2c_dt_spec mcp3421_dev = I2C_DT_SPEC_GET(DT_NODELABEL(mcp3421));


int main(void)
{
	int ret;
	

}
