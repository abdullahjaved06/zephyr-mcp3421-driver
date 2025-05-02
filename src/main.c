#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(mcp3421, LOG_LEVEL_INF);

// I2C configuration based on devicetree label
static const struct i2c_dt_spec mcp3421 = I2C_DT_SPEC_GET(DT_NODELABEL(mcp3421));

// MCP3421 config: Continuous conversion, 18-bit, Gain = 1
#define MCP3421_CONFIG_BYTE 0x9C

void main(void)
{
    if (!device_is_ready(mcp3421.bus)) {
        LOG_ERR("I2C bus for MCP3421 is not ready");
        return;
    }

    LOG_INF("MCP3421 initialized. Reading raw ADC values...");

    while (1) {
        int ret;
        uint8_t config = MCP3421_CONFIG_BYTE;
        uint8_t buffer[4];  // 3 bytes for ADC + 1 config byte
        int32_t raw_adc = 0;

        // Step 1: Send config byte to start (or refresh) continuous conversion
        ret = i2c_write_dt(&mcp3421, &config, 1);
        if (ret < 0) {
            LOG_ERR("Failed to write config byte: %d", ret);
            k_sleep(K_SECONDS(1));
            continue;
        }

        // Step 2: Wait for conversion to complete (~266ms for 18-bit)
        k_sleep(K_MSEC(300));

        // Step 3: Read 3 data bytes + 1 config byte
        ret = i2c_read_dt(&mcp3421, buffer, 4);
        if (ret < 0) {
            LOG_ERR("Failed to read ADC value: %d", ret);
            k_sleep(K_SECONDS(1));
            continue;
        }

        // Step 4: Extract 18-bit signed result
        raw_adc = ((buffer[0] & 0x03) << 16) | (buffer[1] << 8) | buffer[2];

        // Step 5: Sign-extend if the value is negative
        if (buffer[0] & 0x80) {
            raw_adc |= 0xFFFC0000;  // Extend sign bit for 18-bit signed value
        }

        // Step 6: Print raw ADC value
        LOG_INF("Raw ADC: %d", raw_adc);

        k_sleep(K_SECONDS(2));
    }
}
