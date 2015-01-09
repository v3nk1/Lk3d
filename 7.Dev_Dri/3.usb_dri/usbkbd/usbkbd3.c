#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/usb/input.h>
#include <linux/usb.h>
#include <linux/sched.h>
#include <linux/workqueue.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include<linux/device.h>
#include<linux/miscdevice.h>

/* Get a minor range for your devices from the usb maintainer */
#define USB_SKEL_MINOR_BASE     192

#define CDEV_NAME     "mykbddrv"
#define SUCCESS 0

/*
 * key:		esc bspc tab ent spc caps f1->f12
 * scancode:	 1   14   15  28  57  58  59 to 88

 * key:		1 to =  q to ]  a to '  ~   z to / 
 * scancode:	2 to13  16to27  30to40  41  44to53
 */

#define KEYHIT	(usb_kbd_keycode[kbd->new[i]])
#define IS_IT_ASCII             (KEYHIT > 1 &&                  \
                                KEYHIT <= 53 &&                 \
                                KEYHIT != 14 && KEYHIT != 15 && KEYHIT != 28    \
                                && KEYHIT != 42 && KEYHIT != 43)


/*
 * Scancode to kernel keycode table, see linux/input.h
 * for all Linux keycodes
 */

static const unsigned char usb_kbd_keycode[256] = {
          0,  0,  0,  0, 30, 48, 46, 32, 18, 33, 34, 35, 23, 36, 37, 38,
         50, 49, 24, 25, 16, 19, 31, 20, 22, 47, 17, 45, 21, 44,  2,  3,
          4,  5,  6,  7,  8,  9, 10, 11, 28,  1, 14, 15, 57, 12, 13, 26,
         27, 43, 43, 39, 40, 41, 51, 52, 53, 58, 59, 60, 61, 62, 63, 64,
         65, 66, 67, 68, 87, 88, 99, 70,119,110,102,104,111,107,109,106,
        105,108,103, 69, 98, 55, 74, 78, 96, 79, 80, 81, 75, 76, 77, 71,
         72, 73, 82, 83, 86,127,116,117,183,184,185,186,187,188,189,190,
        191,192,193,194,134,138,130,132,128,129,131,137,133,135,136,113,
        115,114,  0,  0,  0,121,  0, 89, 93,124, 92, 94, 95,  0,  0,  0,
        122,123, 90, 91, 85,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         29, 42, 56,125, 97, 54,100,126,164,166,165,163,161,115,114,113,
        150,158,159,128,136,177,178,176,142,152,173,140
};

char ascii_key[] = "  1234567890-=  qwertyuiop[]  asdfghjkl;'`  zxcvbnm,./";
DECLARE_COMPLETION(compl);
unsigned char scancode;

/**
 * struct usb_kbd - state of each attached keyboard
 * @usbdev:	usb device associated with this keyboard
 * @irq:	URB for receiving a list of keys that are pressed when a
 *		new key is pressed or a key that was pressed is released.
 * @new:	Buffer for the @irq URB
 * @new_dma:	DMA address for @irq URB
 */
struct usb_kbd {
	struct usb_device *usbdev;
	struct urb *irq;
	unsigned char *new;
	dma_addr_t new_dma;
};

/*
 * usb_kbd_irq: We have submited Interrupt URB in the usb_kbd_open(), once
 * the URB has been processed this call back is called. We will submit the 
 * URB again.
 */

static void usb_kbd_irq(struct urb *urb)
{
	/*
	 * Get our private object, stored in URB context with 
	 * usb_fill_int_urb() in usb_kbd_probe().
	 */
	struct usb_kbd *kbd = urb->context;
	int i;
//        pr_info("%s: Invoked\n",__func__);

	switch (urb->status) {
	case 0:			/* success */
		break;
	case -ECONNRESET:	/* unlink */
	case -ENOENT:
	case -ESHUTDOWN:
		return;
		/* -EPIPE:  should clear the halt */
	default:		/* error */
		goto resubmit;
	}

	/*
	 * Request was success. Device returns 8 bytes of data
	 * in an array. This is called INPUT report. As the
	 * report descriptor defines, the INPUT report is formatted
	 * as follows;
	 * one byte of modifier byte and 6 bytes keycode array.
	 *
	 byte
	 0     Modifier byte
	 1     reserved
	 2     keycode array (0)
	 3     keycode array (1)
	 4     keycode array (2)
	 5     keycode array (3)
	 6     keycode array (4)
	 7     keycode array (5)

	 * The bitmap of modifier byte is defined like this

	 bit
	 0     LEFT CTRL
	 1     LEFT SHIFT
	 2     LEFT ALT
	 3     LEFT GUI
	 4     RIGHT CTRL
	 5     RIGHT SHIFT
	 6     RIGHT ALT
	 7     RIGHT GUI

	 * The keycode array can hold up to 6 keys which are
	 * simultaneously pushed. The order of keycode in the array is arbitrary.
	 */

	/* Now send up the keycode */
	for (i = 2; i < 8; i++) {
		/*
		 * Check if the new key is in the old keys list, if not send key pressed 
		 * signal to the input subsystem
		 */
		if (usb_kbd_keycode[kbd->new[i]]) {
			if (IS_IT_ASCII)
				pr_info
				    ("%s: scancode: %d - key '%c' has been hitted.\n",
				     __func__, scancode=KEYHIT, ascii_key[KEYHIT]);
			else
				pr_info
				    ("%s: scancode: %d - 'Special' key has been hitted.\n",
				     __func__, scancode=KEYHIT);
			complete(&compl);
		}
	}

 resubmit:
	/*Now resubmit the URB */
	i = usb_submit_urb(urb, GFP_ATOMIC);
	if (i)
		pr_info("can't resubmit intr, %s-%s/input0, status %d\n",
			kbd->usbdev->bus->bus_name, kbd->usbdev->devpath, i);

}

static int kbd_open(struct inode *inode,struct file  *file)
{
        pr_info("open operation success \n");
        return SUCCESS;

}

static int kbd_release(struct inode *inode, struct file *file)
{
        pr_info("release operation success \n");
        return SUCCESS;
}

static ssize_t kbd_read(struct file *file,char *buf,size_t lbuf,loff_t *ppos)
{
//        pr_info("%s: Read function\n",__func__);
	if(lbuf <1)
		return -1;
        wait_for_completion_interruptible(&compl);
        copy_to_user(buf,ascii_key+scancode,1 );
        return 0;
}



static struct file_operations kbd_fops = {
        .owner   =   THIS_MODULE,
        .read    =   kbd_read,
        .open    =   kbd_open,
        .release =   kbd_release
};


/*
 * usb class driver info in order to get a minor number from the usb core,
 * and to have the device registered with the driver core
 */
static struct usb_class_driver usbkbd_class = {
        .name =         CDEV_NAME,
        .fops =         &kbd_fops,           // char drivers file_ops object 
        .minor_base =   USB_SKEL_MINOR_BASE,
};

/*
 * usb_kbd_probe: Called by core when the usb keyboard is plugged in.
 * Inputs:      iface   - usb interface object we are interested in.
 *              id      - Table of devices that match our request.
 *
 * Step1: Get All end points we are interested in.
 * Step2: Allocate All required urbs and memory
 * Step3: Register with Input subsystem
 */
static int usb_kbd_probe(struct usb_interface *iface,
			 const struct usb_device_id *id)
{
	/*
	 * Get usb_device object where this interface is on.
	 */
	struct usb_device *dev = interface_to_usbdev(iface);
	struct usb_host_interface *interface;
	struct usb_endpoint_descriptor *endpoint;
	struct usb_kbd *kbd;	// our private structure.
	int pipe, maxp;
	int error = -ENOMEM;
	pr_info("%s: Invoked\n", __func__);

	interface = iface->cur_altsetting;

	/*
	 * We dont support more than one endpoint. We support interrupt In 
	 * endpoint along with default controll endpoint.
	 */
	if (interface->desc.bNumEndpoints != 1)
		return -ENODEV;
	endpoint = &interface->endpoint[0].desc;
	if (!usb_endpoint_is_int_in(endpoint))
		return -ENODEV;

	/*
	 * Allocate memory for our private structure and initialize with zero.
	 */
	kbd = kzalloc(sizeof(struct usb_kbd), GFP_KERNEL);
	/*
         * Allocate URB for Interrupt IN
         */
        if (!(kbd->irq = usb_alloc_urb(0, GFP_KERNEL)))
                goto fail2;
        /*
         * Allcate buffer to store read data
         */
        if (!(kbd->new = usb_alloc_coherent(dev, 8, GFP_ATOMIC, &kbd->new_dma)))
		goto fail2;
	/*      
	 * Store ref to usb_dev and input_dev in the private object
	 */
	kbd->usbdev = dev;
	
	/*
	 * Get interrupt pipe. A pipe is combination of usb_device, interface
	 * and endpoint.  
	 */
	pipe = usb_rcvintpipe(dev, endpoint->bEndpointAddress);
	/*
	 * Get the max packet size that we can deal with this endpoint. returns
	 * wMaxPacketSize field of endpoint interface descriptor.
	 */
	maxp = usb_maxpacket(dev, pipe, usb_pipeout(pipe));

	/*
	 * Fill in the Interrupt URB. Submit it to the usb core in the
	 * usb_kbd_open() and interrupt call back usb_kbd_irq(). In URB 
	 * context we store our private object so that we can access it in
	 * the usb_kbd_irq().
	 */
	usb_fill_int_urb(kbd->irq, dev, pipe,
			 kbd->new, (maxp > 8 ? 8 : maxp),
			 usb_kbd_irq, kbd, endpoint->bInterval);
	/*
	 * transfer_dma, where received data is kept
	 */
	kbd->irq->transfer_dma = kbd->new_dma;
	kbd->irq->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	/*Storing data */
	usb_set_intfdata(iface, kbd);

	/*tell the user we are ready */
	pr_info("%s: My USB Keyboard is up\n", __func__);
	kbd->irq->dev = kbd->usbdev;
	if (usb_submit_urb(kbd->irq, GFP_KERNEL))
		return -EIO;

	/* we can register the device now, as it is ready */
        if (usb_register_dev(iface, &usbkbd_class)){
                /* something prevented us from registering this driver */
                dev_err(&iface->dev,
                        "Not able to get a minor for this device.\n");
                usb_set_intfdata(iface, NULL);
                goto fail2;
        }

        /* let the user know what node this device is now attached to */
        dev_info(&iface->dev,
                 "USB Skeleton device now attached to USBSkel-%d",
                 iface->minor);

	return 0;

 fail2:
	
	usb_free_urb(kbd->irq);
	usb_free_coherent(dev, 8, kbd->new, kbd->new_dma);
	kfree(kbd);
	return error;
}

/*
 * usb_kbd_disconnect: Called by USB Core when our keyboard is unplugged or
 * our module is removed.
 */
static void usb_kbd_disconnect(struct usb_interface *intf)
{
	struct usb_device *dev=interface_to_usbdev(intf);
	/*
	 * Get our driver private structure stored in interface object using 
	 * usb_set_intfdata() in usb_kbd_probe().
	 */
	struct usb_kbd *kbd = usb_get_intfdata(intf);
	pr_info("%s: Invoked\n", __func__);

	/* give back our minor */
        usb_deregister_dev(intf, &usbkbd_class);

        dev_info(&intf->dev, "USB Skeleton now disconnected");

	usb_set_intfdata(intf, NULL);
	/*
	 * If our usb_kbd_probe() probe function had been called, we need
	 * to free the resources allocated. 
	 *
	 */
	if (kbd) {
		/*Kill the urb if already submitted */
		usb_kill_urb(kbd->irq);
		/*Free the memory we have allocated */
		usb_free_urb(kbd->irq);
		usb_free_coherent(dev, 8, kbd->new, kbd->new_dma);
		/*Free our private data */
		kfree(kbd);
	}
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
	if (ret == 0){
		pr_info("usbkbd: Registered with USB Core\n");
		}
	else
		pr_err("%s: usb_register failed\n", __func__);
	
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
