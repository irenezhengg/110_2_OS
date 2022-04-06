/*
Team members:
資工三 方文昊 108590048
資工三 鄭琳玲 108590056
資工三 黃聖耀 108590061
電資三 李以謙 108820021
*/

#include <linux/init.h>
#include <linux/sched/signal.h>

#include <linux/kernel.h>
#include <linux/module.h>

static int linearlyList_init(void) {

  struct task_struct *task;
  
  printk(KERN_INFO "Listing all of the current tasks linearly\n");
  
  for_each_process(task) {
  
    printk(KERN_INFO "Task name: %s, State: %ld, pid: %d\n", task->comm, task->state, task->pid);
    
  }
  
  printk(KERN_INFO "All of the current tasks are listed linearly\n");
  
  return 0;
}

static void linearlyList_Exit(void) {

  printk(KERN_INFO "Goodbye\n");
  
}

module_init(linearlyList_init);

module_exit(linearlyList_Exit);

MODULE_LICENSE("GPL");
