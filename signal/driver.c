#include<linux/module.h>
#include<linux/init.h>
#include<linux/cdev.h>
#include<linux/kernel.h>
#include<linux/slab.h>
#include<linux/fs.h>
#include<asm/uaccess.h>
//#include<sys/types.h>
//#include<signal.h>
#include"ioctl.h"
#include<asm/siginfo.h>
#include<linux/sched/signal.h>

MODULE_LICENSE("GPL");
struct cdev _cdev;
dev_t devnum;
static int pid;
struct task_struct* p;
struct pid* pp;

int m_open(struct inode* inode,struct file* fp)
{
        printk("open\n");
	//pid = task_pid_nr(current);
        return 0;
}

ssize_t m_read (struct file *filep , char __user *ubuff, size_t count , loff_t *off) {

	printk("File read Succesfully\n");
	return 0;
}

long m_ioctl(struct file *fp,unsigned int cmd,unsigned long args)
{
	switch(cmd){
	
	case IOCTL_CMD:
		printk(KERN_ALERT"IOCTL_CMD");
		break;
	case IOCTL_SEND_SIG:
	if(args==1)
	{
		printk(KERN_ALERT"sending signal\n");
		pid = task_pid_nr(current);
		pp=find_vpid(pid);
		p = pid_task(pp,PIDTYPE_PID);
		send_sig(SIGUSR2,p,0);
	}
	else
	printk(KERN_ALERT"unable to get pid\n");
	break;
	default:
	printk(KERN_ALERT"Illegal ioctl command\n");
	break;}
	return 0;
}

int m_close(struct inode* inode,struct file* fp)
{
        printk("close\n");
        return 0;
}

struct file_operations fops={
        .open=m_open,
	.read=m_read,
        .release=m_close,
        .unlocked_ioctl=m_ioctl,
};

static __init int test_init(void)
{
        int ret;
        printk("init\n");
        devnum=MKDEV(14,0);
        ret=register_chrdev_region(devnum,1,"example");
        if(ret)
        {
                printk("error in registering\n");
                return ret;
        }
        cdev_init(&_cdev,&fops);
        ret=cdev_add(&_cdev,devnum,1);
        if(ret)
        {
                printk("error in adding\n");
                cdev_del(&_cdev);
                unregister_chrdev_region(devnum,1);
                return -1;
        }
        return 0;
}

static __exit void test_exit(void)
{
        printk("exit\n");
        cdev_del(&_cdev);
        unregister_chrdev_region(devnum,1);
}

module_init(test_init);
module_exit(test_exit);
	
		
	
	
