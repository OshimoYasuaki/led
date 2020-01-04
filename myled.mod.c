#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x6624a028, "module_layout" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x3cf24f26, "class_destroy" },
	{ 0x7dedd3d1, "device_destroy" },
	{ 0x6ad547bc, "cdev_del" },
	{ 0xd1c9b6e4, "device_create" },
	{ 0xfbde855f, "__class_create" },
	{ 0xa90cd52c, "cdev_add" },
	{ 0xcc29ee9e, "cdev_init" },
	{ 0x7c32d0f0, "printk" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xe97c4103, "ioremap" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xdb7305a1, "__stack_chk_fail" },
	{ 0x28cc25db, "arm_copy_from_user" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "3FBFF6979D76BE25DC2D65B");
