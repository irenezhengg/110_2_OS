/*
Team members:
資工三 方文昊 108590048
資工三 鄭琳玲 108590056
資工三 黃聖耀 108590061
電資三 李以謙 108820021
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

int __init modl_init(void){

  printk(KERN_INFO "Hi, loading the module\n");
  return 0;
  
}

void __exit modl_exit(void){

  printk(KERN_INFO "Goodbye, removing the module\n");
  
}

module_init(modl_init);

module_exit(modl_exit);

MODULE_LICENSE("GPL");


