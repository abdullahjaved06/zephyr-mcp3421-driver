#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(MCP3421, LOG_LEVEL_INF);

static const struct i2c_dt_spec mcp3421_dev = I2C_DT_SPEC_GET(DT_NODELABEL(mcp3421));

int main(void)
{
    if (!device_is_ready(mcp3421_dev.bus)) {
        LOG_ERR("I2C bus for MCP3421 is not ready");
        return -ENODEV;
    }

    LOG_INF("MCP3421 device is ready");

    // You can add ADC read logic here

    return 0;
}
