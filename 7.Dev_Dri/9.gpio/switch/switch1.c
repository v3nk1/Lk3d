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
#define SW1_IRQ 56




static int button_probe(struct platform_device *pdev)
{
	int i=0;
	struct gpio_keys_platform_data *pdata=dev_get_platdata(&pdev->dev);
	pr_info("%s called\n",__func__);
        pr_info("Name: %s\n",pdev->name);
	pr_info("Number of buttons found: %d\n",pdata->nbuttons);
	pr_info("Buttons names\n");
	pr_info("=============\n");
	for(i=0;i < pdata->nbuttons;i++)
		pr_info("\t%s\n",pdata->buttons[i].desc);

	return 0;	
}

/*Will be called from the i2c-core when our eeprom disappears*/
static int button_remove(struct platform_device *pdev)
{
	pr_info("%s\n",__func__);
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
