#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <modem/nrf_modem_lib.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/input/input.h>

LOG_MODULE_REGISTER(main, CONFIG_LOG_DEFAULT_LEVEL);

static const struct device *const longpress_dev = DEVICE_DT_GET(DT_PATH(longpress));

static void longpress_cb(struct input_event *evt, void *user_data)
{
    if (evt->sync == 0) {
		LOG_INF("sync == 0");
        return;
    }
    int button_number = -1;
    if (0 != evt->value) {
        switch (evt->code) {
            case 18:
                button_number = 1;
                break;
            case 19:
                button_number = 2;
                break;
            default:
                return;
        }
        switch (evt->code) {
            case 18:
                LOG_INF("Short press: button %i\n", button_number);
                break;
            case 19:
                LOG_INF("Long press:  button %i\n", button_number);
                break;
            default:
                return;
        }
    }
}

int main(void)
{
	LOG_INF("start...");
    return 0;
}

INPUT_CALLBACK_DEFINE(longpress_dev, longpress_cb, NULL);
