#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/usb.h>

/*
 * usb_kbd_probe: Called by core when the usb keyboard is plugged in.
 * Inputs:      iface   - usb interface object we are interested in.
 *              id      - Table of devices that match our request.
 *
 */
static int usb_kbd_probe(struct usb_interface *iface,
			 const struct usb_device_id *id)
{
	/*
	 * Get usb_device object where this interface is on.
	 */
	struct usb_device *dev = interface_to_usbdev(iface);
	pr_info("%s: Invoked\n", __func__);

	pr_info("%s: Device information: \n", __func__);
	pr_info("%s: Device manufacturer: %s\n", __func__, dev->manufacturer);
	pr_info("%s: Product: %s\n", __func__, dev->product);
	pr_info("%s: VendorId: %4x, ProductId: %4x\n", __func__,
		dev->descriptor.idVendor, dev->descriptor.idProduct);
	pr_info("%s: usb-%s-%s/input0\n", __func__, dev->bus->bus_name,
		dev->devpath);

	return 0;
}

/*
 * usb_kbd_disconnect: Called by USB Core when our keyboard is unplugged or
 * our module is removed.
 */
static void usb_kbd_disconnect(struct usb_interface *intf)
{
	pr_info("%s: Invoked\n", __func__);

}

/*
 * udb_kbd_id_table: Table that specify what device we are dealing with. We
 * are interrested in Human Interface device(HID). We match our device against 
 * interface descriptor, So we tell usb to search for a device which has class
 * as 3(HID), subclass as 1(boot interface) and protocol as 1(keyboard).
 * refer  4.1, 4.2 and 4.3 sections of USB HID Specification 1.1.
 */
static struct usb_device_id usb_kbd_id_table[] = {
	{USB_INTERFACE_INFO(3, 1, 1)},
	{},			/* Terminating entry */
};

MODULE_DEVICE_TABLE(usb, usb_kbd_id_table);

static struct usb_driver usb_kbd_driver = {
	.name = "usbkbd",	// our device name
	.probe = usb_kbd_probe,	// called when our keyboard is found
	.disconnect = usb_kbd_disconnect,	// called when keyboard is removed
	.id_table = usb_kbd_id_table,
};

/*
 * usb_kbd_init, module initialization routine, register with the USB Core.
 */
static int __init usb_kbd_init(void)
{
	int ret;
	pr_info("%s: Invoked\n", __func__);

	ret = usb_register(&usb_kbd_driver);
	if (ret == 0)
		pr_info("usbkbd: Registered with USB Core");
	return ret;
}

static void __exit usb_kbd_exit(void)
{
	pr_info("%s: Invoked\n", __func__);
	usb_deregister(&usb_kbd_driver);
}

module_init(usb_kbd_init);
module_exit(usb_kbd_exit);

MODULE_AUTHOR("techveda.org");
MODULE_DESCRIPTION("USB Keyboard Driver");
MODULE_LICENSE("GPL");
