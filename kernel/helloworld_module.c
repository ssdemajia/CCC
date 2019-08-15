#include <linux/module.h>
#include <linux/kernel.h>

int init(void) {
  printk("<ss>Hello ss!\n");
  return 0;
}

void clean(void) {
  printk(KERN_ALERT "GoodBye\n");
  exit()
}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("a test kernel module");
module_exit(clean);
module_init(init);