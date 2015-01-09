#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/platform_device.h>
#include <linux/platform_data/leds-s3c24xx.h>
#include <mach/gpio-samsung.h>
#include "led_hdr.h"
#include <linux/delay.h>
#include <plat/gpio-cfg.h>
#include <mach/regs-gpio.h>
#include <asm/gpio.h>

#define START_LED_PIN_NUM 4

static int led_probe(struct platform_device *pd)
{

	printk("led-%d %s: Invoked\n", pd->id, __func__);
	if(pd->id != 4)
		return 0;
	printk("led-%d: On\n", pd->id);
	/*selecting o/p functionality for the pin */
	s3c_gpio_cfgpin(S3C2410_GPB(START_LED_PIN_NUM + pd->id),
			S3C2410_GPIO_OUTPUT);
	/*activating pin */
	s3c_gpio_setpull(S3C2410_GPB(START_LED_PIN_NUM + pd->id),
			 S3C_GPIO_PULL_UP);
	gpio_set_value(S3C2410_GPB(START_LED_PIN_NUM + pd->id), 0);

	mdelay(2000);

	printk("led-%d: Off\n", pd->id);
	gpio_set_value(S3C2410_GPB(START_LED_PIN_NUM + pd->id), 1);
	/*selecting i/p functionality for the pin */
	s3c_gpio_cfgpin(S3C2410_GPB(START_LED_PIN_NUM + pd->id),
			S3C2410_GPIO_INPUT);
	/*de-activating pin */
	s3c_gpio_setpull(S3C2410_GPB(START_LED_PIN_NUM + pd->id),
			 S3C_GPIO_PULL_NONE);
	return 0;

}

static int led_remove(struct platform_device *pd)
{

	printk("led-%d %s: Invoked\n", pd->id, __func__);
	return 0;

}

static struct platform_driver ledplat = {
	.driver = {
		   .name = "s3c24xx_led",
		   .owner = THIS_MODULE,
		   },
	.probe = led_probe,
	.remove = led_remove,
};

static int __init led_plat_init(void)
{

	pr_info("%s: Invoked\n", __func__);
	return platform_driver_register(&ledplat);
}

module_init(led_plat_init);

static __exit void led_plat_exit(void)
{

	platform_driver_unregister(&ledplat);
	pr_info("%s: Invoked\n", __func__);

}

module_exit(led_plat_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Veda Solutions");
