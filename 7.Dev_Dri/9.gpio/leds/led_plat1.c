#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/platform_device.h>
#include <linux/platform_data/leds-s3c24xx.h>
#include <mach/gpio-samsung.h>
#include "led_hdr.h"
#include <linux/delay.h>

static void *base, *config_reg, *data_reg, *up_reg;

static int led_probe(struct platform_device *pd)
{

	printk("led-%d %s: Invoked\n", pd->id, __func__);
	if(pd->id != 4)
		return 0;
	printk("led-4: On\n");
	WRITE_REG(PULUP_EN, up_reg);
	WRITE_REG(CON_OUT, config_reg);
	WRITE_REG(LED_ON, data_reg);
	mdelay(2000);
	printk("led-4: Off\n");
	WRITE_REG(LED_OFF, data_reg);
	WRITE_REG(PULUP_DIS, up_reg);
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
	base = ioremap(GPBCON, sizeof(int) * 3);
	config_reg = base;
	data_reg = base + 4;
	up_reg = base + 8;

	platform_driver_register(&ledplat);

	return 0;
}

module_init(led_plat_init);

static void __exit led_plat_exit(void)
{

	platform_driver_unregister(&ledplat);
	pr_info("%s: Invoked\n", __func__);
	iounmap(base);

}

module_exit(led_plat_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Veda Solutions");
