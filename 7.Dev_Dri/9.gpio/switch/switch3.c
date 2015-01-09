/* eeprom.c - A small char driver to work with mini2440 eeprom
 *
 * Author: Veda Solutions (www.techveda.org)
 *
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/gpio_keys.h>
#include <linux/interrupt.h>
#include <linux/input.h>
#include <asm/gpio.h>
#include <linux/slab.h>
#include <linux/uio_driver.h>

#define SW1_IRQ 56

int irq=SW1_IRQ ;
static struct uio_info *info;


//static irqreturn_t button_handler(int irq,void *arg)
static irqreturn_t button_handler(int irq,struct uio_info *info)
{
	return IRQ_HANDLED;
}




static int button_probe(struct platform_device *pdev)
{

	
	pr_info("%s called\n",__func__);

/******************** UIO ***************************/	

	info = kzalloc(sizeof(struct uio_info), GFP_KERNEL);
        info->name = "uio_device";
        info->version = "0.0.1";
        info->irq =irq ;
	info->irq_flags = IRQF_SHARED|IRQF_TRIGGER_FALLING;
	info->handler = button_handler;
	if (uio_register_device(&pdev->dev, info) < 0) 
	{
		pr_info("Failing to register uio device\n");
		return -1;
	}

	pr_info("Registered UIO handler for IRQ=%d\n", irq);

	return 0;	
}

/*Will be called from the i2c-core when our eeprom disappears*/
static int button_remove(struct platform_device *pdev)
{
	pr_info("%s\n",__func__);
	uio_unregister_device(info);
	kfree(info);
	return 0;
}




static struct platform_driver button_driver = {
	.driver = {
		.name = "gpio-keys",
		.owner = THIS_MODULE,
	},
	.probe = button_probe,
	.remove = button_remove,
};

/*module initialization routine*/
static int __init button_init(void)
{
	platform_driver_register(&button_driver);
	return 0;
}
module_init(button_init);

static void __exit button_exit(void)
{
	platform_driver_unregister(&button_driver);
	

}
module_exit(button_exit);

MODULE_DESCRIPTION("Driver for BUTTON");
MODULE_AUTHOR("Veda Solutions");
MODULE_LICENSE("GPL");
