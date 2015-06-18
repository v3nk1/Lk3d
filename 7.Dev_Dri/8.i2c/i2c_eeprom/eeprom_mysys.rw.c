/**
  * This program deals with sysfs interface for eeprom device.
  * It creates 2 files in /sys/atc_eeprom/at24_hex,at24_hex_char
  * both supports read aswell as write to eeprom device.
  * writing data to those files could be either vi or echo.
  * at24_hex: only deals with/ment for hex I/O.
  * at24_hex_char: Reading is like a layout of 256 char 16x16 layout.
		   each has its equivalent char respectively.
  		   But writing is taken only form char equalent.
  * And it also supports char driver through misc interface. /dev/eeprom_dev.
  FIXME: If you skip any bytes in b/w written bytes by seeking HOLES will
	 be got created. HOLE is represent as ^@
	 And that is also treated as data.
  FIXME: If you didn't return correct num of bytes ie., how much you wrote then
	 sysfs is will write how many bytes you returned.
	 Even though you write all bytes if you ain't return correct num, you 
	 cannot exact return bytes but not written.
 **/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/sysfs.h>
#include <linux/mod_devicetable.h>
#include <linux/log2.h>
#include <linux/bitops.h>
#include <linux/jiffies.h>
#include <linux/i2c.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/delay.h>

#define SUCCESS 0
#define SZ_EEPROM 256
#define SIZE SZ_EEPROM+1 /* i2c read container (including nul byte)*/
#define COUNT 17
#define DEV_NAME "eeprom_dev"

#define EEPROM_DBUG_RD 0
#define EEPROM_DBUG_WR 0

void print_chars(const char *buf,int iter){
	int i;
	for(i=0;i<iter;i++)
		printk("%c",buf[i]);
	printk("\n");
}

void hex_ascii_pattern(const char *buf,const char *func){

	int ret;
        pr_info("\n============================> %s <===============================\n",func);
        for(ret=0;ret<SZ_EEPROM;ret++){
                if(!((ret+1) % 16)){
                        int c=0;
                        printk("%02x  ",buf[ret]);
                        for(c=0;c<16;c++){
                                printk("%c ",buf[c+(ret/16)*16]);
                                }
                        printk("\n");
                        }else{
                        printk("%02x ",buf[ret]);
                }
        }
        pr_info("============================> %s <===============================\n",func);

}

int at24_hex_char(char *dest,const char *buf){
//00 11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff | a b c d e f g h i j k l m n o p\n

	int ret,i;
        for(ret=0;ret<16;ret++){
		for(i=0;i<16;i++)
			sprintf(dest+3*i,"%02x ",buf[i+ret*16]);
		sprintf(dest+3*i,"| ");
		for(i=0;i<16;i++)
			sprintf(dest+50+i*2,"%c ",buf[i+ret*16]);
		sprintf(dest+82-1,"\n");
				//-1 is for removing extra space written at last of each line.
		dest=dest+83-1;
	}	

	return 82*16;
}

void at24_hexdel_keepchar(const char *src,char *dest){

	int i,j,k;
	for(k=0;k<16;k++){
		for(i=0,j=0;j<16;i=i+2,j++){
			dest[j+k*16]=src[50+(k*82)+i];	
		//	printk("%02x ",dest[j+k*16]);
			}
	printk("\n");
	}
}

struct eeprom_private {
	struct i2c_client *client;
	int inuse;
};
struct eeprom_private info;

ssize_t eeprom_read(struct file *file,char __user *ubuf, size_t lbuf, loff_t * offset)
{ 	
	char off = 0x0, buf[SIZE];
	int ret;
	if(lbuf > 256)
		return -1;
	ret = i2c_master_send(info.client,&off,1);
	if(ret != 1)
	{
		pr_info("%s: ret=%d : i2c_master_send error\n",__func__,ret);
		return -1;
	}
	ret = i2c_master_recv(info.client,buf,lbuf);
	if(ret != lbuf)
	{
        	pr_info("%s: ret=%d : i2c_master_recv error\n", __func__,ret);
		return -1;
	}
	buf[lbuf] = '\0';

	ret = lbuf - copy_to_user(ubuf, buf, lbuf);
	return ret;
}

ssize_t eeprom_write(struct file *file, const char __user *ubuf, size_t lbuf, loff_t * offset)
{
	char buf[COUNT], *kbuf;
	static char off=0x00;
	int ret=0;
	
	int i,cnt;

	kbuf = kzalloc(lbuf, GFP_KERNEL);
	if(!kbuf)
		return -1;

	copy_from_user(kbuf, ubuf, lbuf);

	/* Calculate number of 16 bytes data to write */
	if(lbuf%16)
		cnt = lbuf/0x10 + 1; 	/* more than multiples of 16 */
	else	
		cnt = lbuf/0x10;	/*exact multiple of 16 */
	
	for(i=0; i<cnt; i++) {
		/* Store the offset in first byte followed by data */
		buf[0]=off;
		strncpy(buf+1, kbuf+off, COUNT-1);
	
		ret = i2c_master_send(info.client,buf,COUNT);
		if(ret!=COUNT)
		{
			pr_info("in %s: ret=%d i2c_master_send error\n",__func__,ret);
			return -1;
		}

		mdelay(10);

		/* Update offset by number of bytes writen */
		off=off+(ret-1);
			/*Bcoz ret is the value including written offset.*/
	}
	kfree(kbuf);
	return ret;
}

static ssize_t at24_read(struct kobject *kobj, struct kobj_attribute *attr,
                        char *sbuf){

	char off = 0x0, buf[SIZE];
        int ret;
	
	/*Reading data from eeprom device*/
        ret = i2c_master_send(info.client,&off,1);
        if(ret != 1)
        {
                pr_info("%s: ret=%d : i2c_master_send error\n",__func__,ret);
                return -1;
        }
        ret = i2c_master_recv(info.client,buf,SZ_EEPROM);
        if(ret != SZ_EEPROM)
        {
                pr_info("%s: ret=%d : i2c_master_recv error\n", __func__,ret);
                return -1;
        }
        buf[ret] = '\0'; /* Obviously here ret=SZ_EEPROM */
        
        //return sprintf(sbuf,"%s\n",buf); //For as it is char print to sysfs file. 

#if EEPROM_DBUG_RD
	//Printing in dmesg(sanity checks)
	hex_ascii_pattern(buf,__func__);
#endif

	/*Wrting into sysfs file*/
	if(!strcmp(attr->attr.name,"at24_hex_char")){
		return at24_hex_char(sbuf,buf);
	}else
	for(ret=0;ret<256;ret++){
		if(!((ret+1) % 16)){
				sprintf(sbuf+ret*5,"0x%02x\n",buf[ret]);
						 /* Here multiple 5 is "0x%02x\n" */
			}else{
			sprintf(sbuf+ret*5,"0x%02x ",buf[ret]);
						 /* Here multiple 5 is "0x%02x " */
		}
	}
	return ret*5;	// if you return 256 then it will write that much of char to sys file.
	
}

ssize_t at24_write(struct kobject *kobj, struct kobj_attribute *attr,
                         const char *sbuf, size_t count){

	// max count 1280 bytes in the file. 256*4+256 = 1280
	// each char is written to sys file as 4char( like 0x35); 256*4 +
	// and 15(spaces) + 1(\n)=16 like 16 lines; 16*16=256.	
	// Or 256*5=1280

        char buf[COUNT], *kbuf;

        static char off=0x00;
        int ret=0;
        int i,cnt;
#if EEPROM_DBUG_WR
	printk("drv_dbg: In %s: Data:(%u) %s\n",__func__,count,sbuf);
#endif
        kbuf = kzalloc(SZ_EEPROM, GFP_KERNEL);
        if(!kbuf)
                return -1;

	// Calculate number of 16 bytes data to write
        if(count%(16*5))
                cnt = count/(0x10*5) + 1;    // more than multiples of 16
        else
                cnt = count/(0x10*5);        // exact multiple of 16

	/*Reading from sysfs file*/
	if(!strcmp(attr->attr.name,"at24_hex_char")){
		at24_hexdel_keepchar(sbuf,kbuf);
	}else
        for(ret=0;ret<SZ_EEPROM;ret++){
                if(!((ret+1) % 16)){
                        sscanf(sbuf+ret*5,"0x%02x\n",(u32 *)(kbuf+ret));
					// Here multiple 5 is "0x%02x\n" //
                        }else{
                        sscanf(sbuf+ret*5,"0x%02x ",(u32 *)(kbuf+ret));
					 // Here multiple 5 is "0x%02x " //
                }
        }

#if EEPROM_DBUG_WR
	//Printing in dmesg (sanity checks)
//	print_chars(kbuf,SZ_EEPROM);
	hex_ascii_pattern(kbuf,__func__);
#endif

	/*Writing into eeprom device*/
        for(i=0; i<cnt; i++) {
                // Store the offset in first byte followed by data //
                buf[0]=off;
                strncpy(buf+1, kbuf+off, COUNT-1);

                ret = i2c_master_send(info.client,buf,COUNT);
                if(ret!=COUNT)
                {
                        pr_info("in %s: ret=%d i2c_master_send error\n",__func__,ret);
                        return -1;
                }

                mdelay(10);

                // Update offset by number of bytes writen //
                off=off+(ret-1);
                        //Bcoz ret is the value including written offset.//
        }

        kzfree(kbuf);
	     
   return count;  // Or ret*5; if you return 256 it will loop itself.
}

static int char_dev_open(struct inode *inode, struct file *file)
{
        if (info.inuse) {
                pr_err("Device busy %s\n", DEV_NAME);
                return -EBUSY;
        }
        info.inuse = 1;
        pr_info("Open operation invoked\n");
        return SUCCESS;

}

static int char_dev_release(struct inode *inode, struct file *file)
{
        pr_info("%s: Invoked\n",__func__);
        info.inuse = 0;
        return SUCCESS;
}

static struct file_operations char_dev_fops = {
        .owner = THIS_MODULE,
        .open = char_dev_open,
        .release = char_dev_release,
        .write = eeprom_write,
        .read = eeprom_read,
};

static struct miscdevice eeprom_misc = {
        .minor = MISC_DYNAMIC_MINOR,    /* allocate misc minor */
        .name = DEV_NAME,
        .fops = &char_dev_fops,         /* drivers fops instance */
};

static struct kobject *kobj;
static struct kobj_attribute at24_attr = __ATTR(at24_hex, 0666, at24_read, at24_write),
	at24_attr1 = __ATTR(at24_hex_char, 0666, at24_read,at24_write);

static int eeprom_probe(struct i2c_client *client,
                        const struct i2c_device_id *id)
{
	int ret;
	pr_info("%s\n",__func__);
	info.client = client;
	ret = misc_register(&eeprom_misc);
        if (ret < 0) {
                pr_err("failed registering with minor %d\n", eeprom_misc.minor);
                return ret;
        }

	/* Create a struct kobject abd register with sysfs */
        kobj = kobject_create_and_add("atc_eeprom", NULL);
        if(!kobj)
                return -ENOMEM;

        ret = sysfs_create_file(kobj, &at24_attr.attr)||sysfs_create_file(kobj, &at24_attr1.attr);
        if(ret)
                kobject_put(kobj);

	pr_info("In probe client add is %p\n",client);
	return 0;	

}

static int eeprom_remove(struct i2c_client *client)
{
	misc_deregister(&eeprom_misc);
        kobject_put(kobj);
	pr_info("driver removed\n");
	return 0;
}

static struct i2c_device_id eeprom_ids[] = {
        { "24c08",0x50 },  
	{ } // end of the list
};


static struct i2c_driver eeprom_driver = {
	.driver = {
		.name = "24c08",
		.owner = THIS_MODULE,
	},
	.probe = eeprom_probe,
	.remove = eeprom_remove,
	.id_table = eeprom_ids,
};

module_i2c_driver(eeprom_driver);

MODULE_DESCRIPTION("Driver for I2C EEPROM");
MODULE_LICENSE("GPL");
