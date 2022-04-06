#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
struct Bdaydate {
	char* name;
	int year;
	int month;
	int day;
	struct list_head list;
};

static LIST_HEAD(Bdaydate_list);

static int Bdaydate_init(void){
	struct Bdaydate* birthPtr;
	int i;
	char* name[5] = {"Starvian", "Irene", "Matti", "Ken", "Harvey"};
	int month[5] = {1, 2, 3, 4, 5};
	int day[5] = {6, 7, 8, 9, 10};
	int year[5] = {2001, 2001, 2002, 2003, 2004};
	printk(KERN_INFO "Creating birthday list\n");
	for(i = 0; i < 5; i++) {
		birthPtr = kmalloc(sizeof(*birthPtr), GFP_KERNEL);
		birthPtr->name = name[i];
		birthPtr->month = month[i];
		birthPtr->day = day[i];
		birthPtr->year = year[i];
		INIT_LIST_HEAD(&(birthPtr->list));
		list_add_tail(&(birthPtr->list), &Bdaydate_list);
	}
	list_for_each_entry(birthPtr, &Bdaydate_list, list) {
		printk(KERN_INFO "Adding %s's birthday which is %d/%d/%d\n",
			birthPtr->name,
			birthPtr->month,
			birthPtr->day,
			birthPtr->year);
	}
	return 0;
}

static void Bdaydate_exit(void){
	struct Bdaydate *birthPtr = NULL, *next = NULL;
	printk(KERN_INFO "Removing birthday list\n");
	list_for_each_entry_safe(birthPtr, next, &Bdaydate_list, list){
		printk(KERN_INFO "Removing %s's birthday which is %d/%d/%d\n",
			birthPtr->name,
			birthPtr->month,
			birthPtr->day,
			birthPtr->year);
		list_del(&(birthPtr->list));
		kfree(birthPtr);
	}
}

module_init(Bdaydate_init);
module_exit(Bdaydate_exit);
