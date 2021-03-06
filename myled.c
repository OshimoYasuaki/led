#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/delay.h>

MODULE_AUTHOR("Yasuaki Oshimo");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;  //アドレスをマッピングするための配列をグローバルで定義

void tika1(int sleep_count){
	gpio_base[7] = 1 << 25;
	ssleep(sleep_count);
	gpio_base[10] = 1<< 25;
	ssleep(sleep_count);
}

void tika2(int sleep_count){
	gpio_base[7] = 1 << 25;
	ssleep(sleep_count * 2);
	gpio_base[10] = 1 << 25;
	ssleep(sleep_count * 2);
}

static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos)
{
	char c;   //読み込んだ字を入れる変数
	int time = 1;
	if(copy_from_user(&c,buf,sizeof(char)))
		return -EFAULT;

	if(c == '0') {
		tika1(time);
		tika1(time);
		tika1(time);
		tika1(time);
	}
	else if(c == '1'){
		tika2(time);
		tika2(time);
		tika2(time);
		tika2(time);
	}
	else if(c == '2'){
		tika1(time);
		tika2(time);
		tika1(time);
		tika2(time);

	}
	return 1;
}

static struct file_operations led_fops = {
        .owner = THIS_MODULE,
        .write = led_write
};

static int __init init_mod(void)  //カーネルモジュールの初期化
{
	int retval;

	gpio_base = ioremap_nocache(0x3f200000, 0xA0); //0x3f..:base address, 0xA0: region to map

	const u32 led = 25;
	const u32 index = led/10;//GPFSEL2
	const u32 shift = (led%10)*3;//15bit
	const u32 mask = ~(0x7 << shift);//11111111111111000111111111111111
	gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift);//001: output flag
	//11111111111111001111111111111111

	retval =  alloc_chrdev_region(&dev, 0, 1, "myled");
	if(retval < 0){
		printk(KERN_ERR "alloc_chrdev_region failed.\n");
		return retval;
	}
	printk(KERN_INFO "%s is loaded. major:%d\n",__FILE__,MAJOR(dev));

        cdev_init(&cdv, &led_fops);
        retval = cdev_add(&cdv, dev, 1);
        if(retval < 0){
                printk(KERN_ERR "cdev_add failed. major:%d, minor:%d",MAJOR(dev),MINOR(dev));
                return retval;
        }
	cls = class_create(THIS_MODULE,"myled");   //ここから追加
        if(IS_ERR(cls)){
                printk(KERN_ERR "class_create failed.");
                return PTR_ERR(cls);
        }
	device_create(cls, NULL, dev, NULL, "myled%d",MINOR(dev));
	return 0;
}

static void __exit cleanup_mod(void)  //後始末
{
	cdev_del(&cdv);
	device_destroy(cls, dev);
	class_destroy(cls);
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "%s is unloaded. major:%d\n",__FILE__,MAJOR(dev));
}

module_init(init_mod);  //マクロで関数を登録
module_exit(cleanup_mod);  //同上
