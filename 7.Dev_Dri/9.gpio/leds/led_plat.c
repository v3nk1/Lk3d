#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/platform_device.h>
#include <linux/platform_data/leds-s3c24xx.h>
#include <mach/gpio-samsung.h>

static int led_probe(struct platform_device *pd)
{

	printk("led-%d %s: Invoked\n", pd->id, __func__);
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

	pr_info("%s Invoked\n", __func__);
	return platform_driver_register(&ledplat);
}

module_init(led_plat_init);

static void __exit led_plat_exit(void)
{

	platform_driver_unregister(&ledplat);
	pr_info("%s Invoked\n", __func__);

}

module_exit(led_plat_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Veda Solutions");
