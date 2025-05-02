#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(MCP3421, LOG_LEVEL_INF);

static const struct i2c_dt_spec mcp3421 = I2C_DT_SPEC_GET(DT_NODELABEL(mcp3421));

//MCP3421 config: continuous conversion, 18-bit, Gain =1
#define MCP3421_CONFIG_BYTE 0x9C


int main(void)
{
    if (!device_is_ready(mcp3421.bus)) {
        LOG_ERR("I2C bus for MCP3421 is not ready");
        return -ENODEV;
    }

    LOG_INF("MCP3421 device is ready");

    while (1)
    {
        int ret;
        uint8_t config = MCP3421_CONFIG_BYTE;
        ret = i2c_write_dt(&mcp3421,config,1);
        if(ret<0) {
            LOG_ERR("Failed to write config byte: %d",ret);
            k_sleep(K_SECONDS(1));
            continue;
        }
        
    }
    
   
}
