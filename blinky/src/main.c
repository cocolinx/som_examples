#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <modem/nrf_modem_lib.h>
#include <zephyr/drivers/gpio.h>

#define PIN_LED_0       23
#define PIN_LED_1       24
#define PIN_LED_2       25
#define SLEEP_TIME_MS   1000

LOG_MODULE_REGISTER(main_blinky, CONFIG_LOG_DEFAULT_LEVEL);

static const struct device *leds = DEVICE_DT_GET(DT_NODELABEL(gpio0));

int main(void)
{
    int err;
    err = nrf_modem_lib_init();
    if(err < 0)
        LOG_ERR("Unable to initialize modem lib. (err: %d)", err);
    
    LOG_INF("=====BLINKY EXAMPLE=====");

    if(!device_is_ready(leds)) return 0;

    // low(on), high(off)
    err = gpio_pin_configure(leds, PIN_LED_0, GPIO_OUTPUT_HIGH);
    if(err < 0) {
        LOG_ERR("Failed to config gpio 23 pin %d", err);
        return 0;
    }

    err = gpio_pin_configure(leds, PIN_LED_1, GPIO_OUTPUT_HIGH);
    if(err < 0) {
        LOG_ERR("Failed to config gpio 24 pin %d", err);
        return 0;
    }

    err = gpio_pin_configure(leds, PIN_LED_2, GPIO_OUTPUT_HIGH);
    if(err < 0) {
        LOG_ERR("Failed to config gpio 25 pin %d", err);
        return 0;
    }

    while(true){
        /* PIN_LED_0 */
        err = gpio_pin_set_raw(leds, PIN_LED_0, 0); /* turn on */
        if(err < 0) {
            LOG_ERR("Failed to set gpio 23 pin %d", err);
            break;
        }
        LOG_INF("turn on (PIN: %d)", PIN_LED_0);
        k_msleep(SLEEP_TIME_MS);
        err = gpio_pin_set_raw(leds, PIN_LED_0, 1); /* turn off */
        if(err < 0) {
            LOG_ERR("Failed to set gpio 23 pin %d", err);
            break;
        }
        LOG_INF("turn off (PIN: %d)", PIN_LED_0);
        k_msleep(SLEEP_TIME_MS);
        
        /* PIN_LED_1 */
        err = gpio_pin_set_raw(leds, PIN_LED_1, 0); /* turn on */
        if(err < 0) {
            LOG_ERR("Failed to set gpio 24 pin %d", err);
            break;
        }
        LOG_INF("turn on (PIN: %d)", PIN_LED_1);
        k_msleep(SLEEP_TIME_MS);
        err = gpio_pin_set_raw(leds, PIN_LED_1, 1); /* turn off */
        if(err < 0) {
            LOG_ERR("Failed to set gpio 24 pin %d", err);
            break;
        }
        LOG_INF("turn off (PIN: %d)", PIN_LED_1);
        k_msleep(SLEEP_TIME_MS);

        /* PIN_LED_2 */
        err = gpio_pin_set_raw(leds, PIN_LED_2, 0); /* turn on */
        if(err < 0) {
            LOG_ERR("Failed to set gpio 25 pin %d", err);
            break;
        }
        LOG_INF("turn on (PIN: %d)", PIN_LED_2);
        k_msleep(SLEEP_TIME_MS);
        err = gpio_pin_set_raw(leds, PIN_LED_2, 1); /* turn off */
        if(err < 0) {
            LOG_ERR("Failed to set gpio 25 pin %d", err);
            break;
        }
        LOG_INF("turn off (PIN: %d)", PIN_LED_2);
        k_msleep(SLEEP_TIME_MS);
    }

    return 0;
}
