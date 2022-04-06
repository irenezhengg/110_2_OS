/*
Team members:
資工三 方文昊 108590048
資工三 鄭琳玲 108590056
資工三 黃聖耀 108590061
電資三 李以謙 108820021
*/

#include <linux/sched/signal.h>
#include <linux/init.h>

#include <linux/kernel.h>
#include <linux/module.h>

void dfsTree(struct task_struct *task) {

  struct task_struct *task_next;
  struct list_head *list;
  
  list_for_each(list, &task->children) {
  
    task_next = list_entry(list, struct task_struct, sibling);
    
    printk(KERN_INFO "task name: %s, state: %ld, pid: %d\n", task_next->comm, task_next->state, task_next->pid);
    dfsTree(task_next);
    
  }
  
}

static int dfsTree_init(void) {

  printk(KERN_INFO "Listing all of the current tasks using a depth-first search(DFS) tree\n");
  dfsTree(&init_task);
  
  printk(KERN_INFO "All of the current tasks are listed using a depth-first search(DFS) tree\n");
  return 0;
  
}

static void dfsTree_exit(void) {

  printk(KERN_INFO "Goodbye\n");
  
}


module_init(dfsTree_init);

module_exit(dfsTree_exit);

MODULE_LICENSE("GPL");

