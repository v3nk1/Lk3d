#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x9412fa01, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xde98c647, __VMLINUX_SYMBOL_STR(kobject_put) },
	{ 0xb2711b8f, __VMLINUX_SYMBOL_STR(sysfs_create_group) },
	{ 0x256a10b2, __VMLINUX_SYMBOL_STR(kobject_create_and_add) },
	{ 0xd57a9d2e, __VMLINUX_SYMBOL_STR(rtc_kobj) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=rtc_sysfs";


MODULE_INFO(srcversion, "97DA9B8BCBECF581E1EBDB0");
