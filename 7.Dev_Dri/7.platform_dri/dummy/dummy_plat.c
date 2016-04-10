/*
 * Platform bus is a virtual bus.
 * This is demonistration how can a new platform device
 * be supported, 1. Showing up a plat device
 *               2. Registering a dummy driver for dummy device.
 *               When i say dummy, device doesn't exists.
 * Info: http://lwn.net/Articles/448499/
 *       https://lwn.net/Articles/448502/
 * DTB : http://devicetree.org/Device_Tree_Usage
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>

/* Probe and Remove routines*/
int dummy_probe (struct platform_device *pdev)
{

    printk("%s: Invoked\n",__func__);
    return 0;

}

int dummy_remove (struct platform_device *pdev)
{

    printk("%s: Invoked\n",__func__);
    return 0;

}

/*Registering a dummy device*/
struct platform_device dummy_dev = {
    .name = "dummy-dev",
};

struct platform_driver dummy_driver = {
    .driver = {
        .name = "dummy-dev",
        .owner = THIS_MODULE,
    },
    .probe = dummy_probe,
    .remove = dummy_remove
};

int init_module(void){

    platform_device_register(&dummy_dev);
    printk("%s: Registered dummy platform device\n",__func__);

    return platform_driver_register(&dummy_driver);
}

/*
 * Technically platform drivers should not be removed
 * dynamically/run-time, If is done find respective crash dump
 * in "dmesg" log.
 */
void cleanup_module(void){

    platform_device_unregister(&dummy_dev);
    printk("%s: un-registered dummy platform device\n",__func__);
    platform_driver_unregister(&dummy_driver);

}

MODULE_LICENSE("GPL");
