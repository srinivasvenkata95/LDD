#include<linux/init.h>
#include<linux/module.h>
#include<linux/cdev.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/types.h>
#include<asm/uaccess.h>
#include<linux/uaccess.h>
#include<linux/slab.h>
dev_t devnum;
int count = 0;


EXPORT_SYMBOL(count);

int m_open(struct inode *inode,struct file* filep)
{
	printk("in open \n");
		return 0;
}
int m_close(struct inode *inode,struct file* filep)
{
	printk("on close\n");
	return 0;
}
ssize_t m_write(struct file *filep,const char __user *ubuff,size_t cnt,loff_t *off)
{
	printk("TS_write: \n");
	return 0;
}
ssize_t m_read(struct file *filep, char __user *ubuff,size_t cnt,loff_t *off)
{
	printk("TS_read: \n");
	return 0;
}


struct file_operations fops=
{
	.open= m_open,
	.release=m_close,
	.write= m_write,
	.read= m_read,
};
static int __init TS_init(void)
{
	int ret;
	devnum=MKDEV(42,0);
	ret=register_chrdev_region(devnum,1,"device1");
	if(ret)
	{
		printk("unable to register device no \n");
		return ret;
	}
	printk(KERN_INFO "Hello World\n");
	count++;
	return 0;
}

static void __exit TS_exit(void)
{
	unregister_chrdev_region(devnum,1);
	printk(KERN_INFO "exit\n");
}

module_init(TS_init);
module_exit(TS_exit);
