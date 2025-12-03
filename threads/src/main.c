#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

/* size of stack area used by each thread */
#define STACKSIZE 1024
/* scheduling priority used by each thread */
#define PRIORITY 7
#define PIN_LED_0 23
#define PIN_LED_1 24
#define PIN_LED_2 25

LOG_MODULE_REGISTER(main, CONFIG_LOG_DEFAULT_LEVEL);

static const struct device *leds = DEVICE_DT_GET(DT_NODELABEL(gpio0));

static void blink(int pin, uint32_t sleep_ms)
{
    if(!device_is_ready(leds)) return;

    int err;
    err = gpio_pin_configure(leds, pin, GPIO_OUTPUT_HIGH);
    if(err < 0) {
        LOG_ERR("Failed to config gpio %d pin %d", pin, err);
        return;
    }
    while(true) {
        err = gpio_pin_set_raw(leds, pin, 0); /* turn on */
        if(err < 0) {
            LOG_ERR("Failed to set gpio %d pin %d", pin, err);
            break;
        }
        LOG_INF("turn on (PIN: %d)", pin);
        k_msleep(sleep_ms);
        err = gpio_pin_set_raw(leds, pin, 1); /* turn off */
        if(err < 0) {
            LOG_ERR("Failed to set gpio %d pin %d", pin, err);
            break;
        }
        LOG_INF("turn off (PIN: %d)", pin);
        k_msleep(sleep_ms);
    }
}

static void blink0(void)
{
    blink(PIN_LED_0, 100);
}

static void blink1(void)
{
    blink(PIN_LED_1, 1000);
}

static void blink2(void)
{
    blink(PIN_LED_2, 2000);
}


K_THREAD_DEFINE(blink0_id, STACKSIZE, blink0, NULL, NULL, NULL, PRIORITY, 0, 0);
K_THREAD_DEFINE(blink1_id, STACKSIZE, blink1, NULL, NULL, NULL, PRIORITY, 0, 0);
K_THREAD_DEFINE(blink2_id, STACKSIZE, blink2, NULL, NULL, NULL, PRIORITY, 0, 0);